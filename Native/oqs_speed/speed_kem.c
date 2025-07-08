// SPDX-License-Identifier: MIT

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <oqs/oqs.h>

#if defined(OQS_USE_RASPBERRY_PI)
#define _OQS_RASPBERRY_PI
#endif
#if defined(OQS_SPEED_USE_ARM_PMU)
#define SPEED_USE_ARM_PMU
#endif
#include "ds_benchmark.h"
// #include "system_info.c"

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>

static void fullcycletest(OQS_KEM *kem, uint8_t *public_key, uint8_t *secret_key, uint8_t *ciphertext, uint8_t *shared_secret_e, uint8_t *shared_secret_d)
{
	if (OQS_KEM_keypair(kem, public_key, secret_key) != OQS_SUCCESS)
	{
		printf("Error creating KEM key. Exiting.\n");
		exit(-1);
	}
	if (OQS_KEM_encaps(kem, ciphertext, shared_secret_e, public_key) != OQS_SUCCESS)
	{
		printf("Error during KEM encaps. Exiting.\n");
		exit(-1);
	}
	if (OQS_KEM_decaps(kem, shared_secret_d, ciphertext, secret_key) != OQS_SUCCESS)
	{
		printf("Error during KEM decaps. Exiting.\n");
		exit(-1);
	}
}

static OQS_STATUS kem_ossl_speed_wrapper(const char *kem_name, uint64_t duration, bool printInfo, bool doFullCycle, bool noKeyGen, bool noEncaps, bool noDecaps)
{
	OSSL_LIB_CTX *app_libctx = NULL;
	static const char *app_propq = NULL;
	EVP_PKEY *pkey = NULL;
	EVP_PKEY_CTX *kem_gen_ctx = NULL;
	EVP_PKEY_CTX *kem_encaps_ctx = NULL;
	EVP_PKEY_CTX *kem_decaps_ctx = NULL;
	size_t send_secret_len, out_len;
	size_t rcv_secret_len;
	char *name;
	unsigned char *out = NULL, *send_secret = NULL, *rcv_secret;
	unsigned int bits;
	char sfx[100];
	OSSL_PARAM params[] = {OSSL_PARAM_END, OSSL_PARAM_END};
	int use_params = 0;
	enum kem_type_t
	{
		KEM_RSA = 1,
		KEM_EC,
		KEM_X25519,
		KEM_X448
	} kem_type;

	/* no string after rsa<bitcnt> permitted: */
	if (strlen(kem_name) < 100 + 4 /* rsa+digit */
		&& sscanf(kem_name, "rsa%u%s", &bits, sfx) == 1)
		kem_type = KEM_RSA;
	else if (strncmp(kem_name, "EC", 2) == 0)
		kem_type = KEM_EC;
	else if (strcmp(kem_name, "X25519") == 0)
		kem_type = KEM_X25519;
	else if (strcmp(kem_name, "X448") == 0)
		kem_type = KEM_X448;
	else 
		kem_type = 0;

	if (ERR_peek_error())
	{
		fprintf(stderr,
				"WARNING: the error queue contains previous unhandled errors.\n");
		return 1;
	}

	if (kem_type == KEM_RSA)
	{
		params[0] = OSSL_PARAM_construct_uint("bits",
											  &bits);
		use_params = 1;
	}
	else if (kem_type == KEM_EC) {
		name = (char *)(kem_name + 2);
		params[0] = OSSL_PARAM_construct_utf8_string("group",
											name, 0);
		use_params = 1;
	}
	kem_gen_ctx = EVP_PKEY_CTX_new_from_name(app_libctx, "EC", app_propq);

	if ((!kem_gen_ctx || EVP_PKEY_keygen_init(kem_gen_ctx) <= 0) || (use_params && EVP_PKEY_CTX_set_params(kem_gen_ctx, params) <= 0))
	{
		fprintf(stderr, "Error initializing keygen ctx for %s.\n",
				kem_name);
		return 1;
	}
	if (EVP_PKEY_keygen(kem_gen_ctx, &pkey) <= 0)
	{
		fprintf(stderr, "Error while generating KEM EVP_PKEY.\n");
		ERR_print_errors_fp(stderr);
		return 1;
	}
	/* Now prepare encaps data structs */
	kem_encaps_ctx = EVP_PKEY_CTX_new_from_pkey(app_libctx,
												pkey,
												app_propq);
	if (kem_encaps_ctx == NULL) {
		fprintf(stderr, "kem_encaps_ctx == NULL\n");
		return 1;
	}
	if (EVP_PKEY_encapsulate_init(kem_encaps_ctx, NULL) <= 0) {
		fprintf(stderr, "EVP_PKEY_encapsulate_init failed\n");
		ERR_print_errors_fp(stderr);
		return 1;
	}
	if (kem_type == KEM_RSA && EVP_PKEY_CTX_set_kem_op(kem_encaps_ctx, "RSASVE") <= 0) {
		fprintf(stderr, "EVP_PKEY_CTX_set_kem_op failed, should only happen with RSA\n");
		return 1;
	}
	if (kem_type == KEM_EC || kem_type == KEM_X25519 || kem_type == KEM_X448) {
		if (EVP_PKEY_CTX_set_kem_op(kem_encaps_ctx, "DHKEM") <= 0) {
			fprintf(stderr, "EVP_PKEY_CTX_set_kem_op failed\n");
			return 1;
		}
	}

	if (EVP_PKEY_encapsulate(kem_encaps_ctx, NULL, &out_len, NULL, &send_secret_len) <= 0)
	{
		fprintf(stderr,
				"Error while initializing encaps data structs for %s.\n",
				kem_name);
		return 1;
	}
	out = malloc(out_len);
	send_secret = malloc(send_secret_len);
	if (out == NULL || send_secret == NULL)
	{
		fprintf(stderr, "MemAlloc error in encaps for %s.\n", kem_name);
		return 1;
	}
	if (EVP_PKEY_encapsulate(kem_encaps_ctx, out, &out_len,
							 send_secret, &send_secret_len) <= 0)
	{
		fprintf(stderr, "Encaps error for %s.\n", kem_name);
		return 1;
	}
	/* Now prepare decaps data structs */
	kem_decaps_ctx = EVP_PKEY_CTX_new_from_pkey(app_libctx,
												pkey,
												app_propq);
	if (kem_decaps_ctx == NULL || EVP_PKEY_decapsulate_init(kem_decaps_ctx, NULL) <= 0 || (kem_type == KEM_RSA && EVP_PKEY_CTX_set_kem_op(kem_decaps_ctx, "RSASVE") <= 0) || ((kem_type == KEM_EC || kem_type == KEM_X25519 || kem_type == KEM_X448) && EVP_PKEY_CTX_set_kem_op(kem_decaps_ctx, "DHKEM") <= 0) || EVP_PKEY_decapsulate(kem_decaps_ctx, NULL, &rcv_secret_len, out, out_len) <= 0)
	{
		fprintf(stderr,
				"Error while initializing decaps data structs for %s.\n",
				kem_name);
		return 1;
	}
	rcv_secret = malloc(rcv_secret_len);
	if (rcv_secret == NULL)
	{
		fprintf(stderr, "MemAlloc failure in decaps for %s.\n",
				kem_name);
		return 1;
	}
	if (EVP_PKEY_decapsulate(kem_decaps_ctx, rcv_secret,
							 &rcv_secret_len, out, out_len) <= 0 ||
		rcv_secret_len != send_secret_len || memcmp(send_secret, rcv_secret, send_secret_len))
	{
		fprintf(stderr, "Decaps error for %s.\n", kem_name);
		return 1;
	}
	// To test if the OSSL implementation is working without errors uncomment this code block

	//printf("Doing %s %s ops for %ds: \n", kem_name, "keygen", duration);

	EVP_PKEY_CTX *ctx = kem_gen_ctx;
	int count;

	for (count = 0; count < 10; count++) {
	    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
			fprintf(stderr, "keygen failed\n");
			return OQS_ERROR;
		}
	    /*
	     * runtime defined to quite some degree by randomness,
	     * so performance overhead of _free doesn't impact
	     * results significantly. In any case this test is
	     * meant to permit relative algorithm performance
	     * comparison.
	     */
	    EVP_PKEY_free(pkey);
	    pkey = NULL;
	}

	ctx = kem_encaps_ctx;

	for (count = 0; count < 10; count++) {
	    if (EVP_PKEY_encapsulate(ctx, out, &out_len, send_secret, &send_secret_len) <= 0) {
			fprintf(stderr, "encaps failed\n");
			return OQS_ERROR;
		}
	}

	//printf("Doing %s %s ops for %ds: \n", kem_name, "decaps", duration);

	ctx = kem_decaps_ctx;

	for (count = 0; count < 10; count++) {
	    if (EVP_PKEY_decapsulate(ctx, send_secret, &send_secret_len, out, out_len) <= 0)
	        return OQS_ERROR;
	}

	printf("%-36s | %10s | %14s | %15s | %10s | %25s | %10s\n", kem_name, "", "", "", "", "", "");
	if (!doFullCycle)
	{
		if (!noKeyGen)
			TIME_OPERATION_SECONDS(EVP_PKEY_keygen(kem_gen_ctx, &pkey), "keygen", duration)
		if (!noEncaps)
			TIME_OPERATION_SECONDS(EVP_PKEY_encapsulate(kem_encaps_ctx, out, &out_len, send_secret, &send_secret_len), "encaps", duration)
		if (!noDecaps)
			TIME_OPERATION_SECONDS(EVP_PKEY_decapsulate(kem_decaps_ctx, send_secret, &send_secret_len, out, out_len), "decaps", duration)
	}
	else
	{
		fprintf(stderr, "Not implemented\n");
		return OQS_ERROR;
	}

	if (printInfo)
	{
		fprintf(stderr, "Not implemented\n");
		return OQS_ERROR;
	}
	return OQS_SUCCESS;
}

static OQS_STATUS kem_speed_wrapper(const char *method_name, uint64_t duration, bool printInfo, bool doFullCycle, bool noKeyGen, bool noEncaps, bool noDecaps)
{

	OQS_KEM *kem = NULL;
	uint8_t *public_key = NULL;
	uint8_t *secret_key = NULL;
	uint8_t *ciphertext = NULL;
	uint8_t *shared_secret_e = NULL;
	uint8_t *shared_secret_d = NULL;
	OQS_STATUS ret = OQS_ERROR;

	kem = OQS_KEM_new(method_name);
	if (kem == NULL)
	{
		return OQS_SUCCESS;
	}

	public_key = OQS_MEM_malloc(kem->length_public_key);
	secret_key = OQS_MEM_malloc(kem->length_secret_key);
	ciphertext = OQS_MEM_malloc(kem->length_ciphertext);
	shared_secret_e = OQS_MEM_malloc(kem->length_shared_secret);
	shared_secret_d = OQS_MEM_malloc(kem->length_shared_secret);

	if ((public_key == NULL) || (secret_key == NULL) || (ciphertext == NULL) || (shared_secret_e == NULL) || (shared_secret_d == NULL))
	{
		fprintf(stderr, "ERROR: OQS_MEM_malloc failed\n");
		goto err;
	}

	printf("%-36s | %10s | %14s | %15s | %10s | %25s | %10s\n", kem->method_name, "", "", "", "", "", "");
	if (!doFullCycle)
	{
		if (!noKeyGen)
			TIME_OPERATION_SECONDS(OQS_KEM_keypair(kem, public_key, secret_key), "keygen", duration)
		if (!noEncaps)
			TIME_OPERATION_SECONDS(OQS_KEM_encaps(kem, ciphertext, shared_secret_e, public_key), "encaps", duration)
		if (!noDecaps)
			TIME_OPERATION_SECONDS(OQS_KEM_decaps(kem, shared_secret_d, ciphertext, secret_key), "decaps", duration)
	}
	else
	{
		TIME_OPERATION_SECONDS(fullcycletest(kem, public_key, secret_key, ciphertext, shared_secret_e, shared_secret_d), "fullcycletest", duration)
	}

	if (printInfo)
	{
		printf("public key bytes: %zu, ciphertext bytes: %zu, secret key bytes: %zu, shared secret key bytes: %zu, NIST level: %d, IND-CCA: %s\n", kem->length_public_key, kem->length_ciphertext, kem->length_secret_key, kem->length_shared_secret, kem->claimed_nist_level, kem->ind_cca ? "Y" : "N");
	}

	ret = OQS_SUCCESS;
	goto cleanup;

err:
	ret = OQS_ERROR;

cleanup:
	if (kem != NULL)
	{
		OQS_MEM_secure_free(secret_key, kem->length_secret_key);
		OQS_MEM_secure_free(shared_secret_e, kem->length_shared_secret);
		OQS_MEM_secure_free(shared_secret_d, kem->length_shared_secret);
	}
	OQS_MEM_insecure_free(public_key);
	OQS_MEM_insecure_free(ciphertext);
	OQS_KEM_free(kem);

	return ret;
}

static OQS_STATUS printAlgs(void)
{
	for (size_t i = 0; i < OQS_KEM_algs_length; i++)
	{
		OQS_KEM *kem = OQS_KEM_new(OQS_KEM_alg_identifier(i));
		if (kem == NULL)
		{
			printf("%s (disabled)\n", OQS_KEM_alg_identifier(i));
		}
		else
		{
			printf("%s\n", OQS_KEM_alg_identifier(i));
		}
		OQS_KEM_free(kem);
	}
	return OQS_SUCCESS;
}

#include <openssl/core_dispatch.h>
#include <openssl/core_names.h>

int main_speed_kem(int argc, char **argv)
{

	int ret = EXIT_SUCCESS;
	OQS_STATUS rc;

	bool printUsage = false;
	uint64_t duration = 3;
	bool printKemInfo = false;
	bool doFullCycle = false;
	bool noKeyGen = false;
	bool noEncaps = false;
	bool noDecaps = false;
	OQS_KEM *single_kem = NULL;

	bool ecdhe = false;

	OQS_randombytes_switch_algorithm(OQS_RAND_alg_openssl);

	OQS_init();
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--algs") == 0)
		{
			rc = printAlgs();
			if (rc == OQS_SUCCESS)
			{
				OQS_destroy();
				return EXIT_SUCCESS;
			}
			else
			{
				OQS_destroy();
				return EXIT_FAILURE;
			}
		}
		else if ((strcmp(argv[i], "--duration") == 0) || (strcmp(argv[i], "-d") == 0))
		{
			if (i < argc - 1)
			{
				duration = (uint64_t)strtol(argv[i + 1], NULL, 10);
				if (duration > 0)
				{
					i += 1;
					continue;
				}
			}
		}
		else if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0))
		{
			printUsage = true;
			break;
		}
		else if ((strcmp(argv[i], "--info") == 0) || (strcmp(argv[i], "-i") == 0))
		{
			printKemInfo = true;
			continue;
		}
		else if ((strcmp(argv[i], "--fullcycle") == 0) || (strcmp(argv[i], "-f") == 0))
		{
			doFullCycle = true;
			continue;
		}
		else if ((strcmp(argv[i], "--no_keygen") == 0))
		{
			noKeyGen = true;
			continue;
		}
		else if ((strcmp(argv[i], "--no_encaps") == 0))
		{
			noEncaps = true;
			continue;
		}
		else if ((strcmp(argv[i], "--no_decaps") == 0))
		{
			noDecaps = true;
			continue;
		}
		else
		{
			if (!strcmp(argv[i], "RSA"))
			{
				ecdhe = true;
				break;
			}
			single_kem = OQS_KEM_new(argv[i]);
			if (single_kem == NULL)
			{
				printUsage = true;
				break;
			}
		}
	}

	if (printUsage)
	{
		fprintf(stderr, "Usage: speed_kem <options> <alg>\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "<options>\n");
		fprintf(stderr, "--algs             Print supported algorithms and terminate\n");
		fprintf(stderr, "--duration n\n");
		fprintf(stderr, " -d n              Run each speed test for approximately n seconds, default n=3\n");
		fprintf(stderr, "--help\n");
		fprintf(stderr, " -h                Print usage\n");
		fprintf(stderr, "--info\n");
		fprintf(stderr, " -i                Print info (sizes, security level) about each KEM\n");
		fprintf(stderr, "--fullcycle\n");
		fprintf(stderr, " -f                Do full keygen-encaps-decaps cycle for each KEM\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "<alg>              Only run the specified KEM method; must be one of the algorithms output by --algs\n");
		return EXIT_FAILURE;
	}

	// print_system_info();

	printf("KEM Speed test\n");
	printf("==========\n");

	PRINT_TIMER_HEADER
	//ECP-256
	//rsa2048
	if (single_kem != NULL || ecdhe)
	{
		;
		if (ecdhe)
		{
			rc = kem_ossl_speed_wrapper("rsa2048", duration, printKemInfo, doFullCycle, noKeyGen, noEncaps, noDecaps);
		}
		else
		{
			rc = kem_speed_wrapper(single_kem->method_name, duration, printKemInfo, doFullCycle, noKeyGen, noEncaps, noDecaps);
		}

		if (rc != OQS_SUCCESS)
		{
			ret = EXIT_FAILURE;
		}
		// OQS_KEM_free(single_kem);
	}
	else
	{
		for (size_t i = 0; i < OQS_KEM_algs_length; i++)
		{
			rc = kem_speed_wrapper(OQS_KEM_alg_identifier(i), duration, printKemInfo, doFullCycle, noKeyGen, noEncaps, noDecaps);
			if (rc != OQS_SUCCESS)
			{
				ret = EXIT_FAILURE;
			}
		}
		rc = kem_ossl_speed_wrapper("rsa2048", duration, printKemInfo, doFullCycle, noKeyGen, noEncaps, noDecaps);
		if (rc != OQS_SUCCESS)
		{
			ret = EXIT_FAILURE;
		}
	}
	PRINT_TIMER_FOOTER
	OQS_destroy();

	return ret;
}