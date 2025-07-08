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

#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/objects.h>
#include <openssl/evp.h>
#include <openssl/core_names.h>
#include <openssl/async.h>
#include <openssl/provider.h>
#include <openssl/dsa.h>
#include <openssl/rsa.h>

static void fullcycle(OQS_SIG *sig, uint8_t *public_key, uint8_t *secret_key, uint8_t *signature, size_t signature_len, uint8_t *message, size_t message_len)
{
	if (OQS_SIG_keypair(sig, public_key, secret_key) != OQS_SUCCESS)
	{
		printf("keygen error. Exiting.\n");
		exit(-1);
	}
	if (OQS_SIG_sign(sig, signature, &signature_len, message, message_len, secret_key) != OQS_SUCCESS)
	{
		printf("sign error. Exiting.\n");
		exit(-1);
	}
	if (OQS_SIG_verify(sig, message, message_len, signature, signature_len, public_key) != OQS_SUCCESS)
	{
		printf("verify error. Exiting.\n");
		exit(-1);
	}
}
static OQS_STATUS sig_speed_ossl_wrapper(const char *sig_name, uint64_t duration, bool printInfo, bool doFullCycle, bool noKeygen, bool noSign, bool noVerify)
{
	OSSL_LIB_CTX *app_libctx = NULL;
	char *propq = NULL;
	EVP_PKEY *pkey = NULL;
	EVP_PKEY_CTX *ctx_params = NULL;
	EVP_PKEY *pkey_params = NULL;
	EVP_PKEY_CTX *sig_gen_ctx = NULL;
	EVP_PKEY_CTX *sig_sign_ctx = NULL;
	EVP_PKEY_CTX *sig_verify_ctx = NULL;
	unsigned char md[32];
	unsigned char *sig;
	char sfx[100];
	size_t md_len = 32;
	size_t max_sig_len, sig_len;
	unsigned int bits;
	OSSL_PARAM params[] = {OSSL_PARAM_END, OSSL_PARAM_END};
	int use_params = 0;

	/* only sign little data to avoid measuring digest performance */
	memset(md, 0, 32);

	/* no string after rsa<bitcnt> permitted: */
	if (strlen(sig_name) < 100 + 4 /* rsa+digit */
		&& sscanf(sig_name, "rsa%u%s", &bits, sfx) == 1)
	{
		params[0] = OSSL_PARAM_construct_uint("bits",
											  &bits);
		use_params = 1;
	}

	if (strncmp(sig_name, "dsa", 3) == 0)
	{
		ctx_params = EVP_PKEY_CTX_new_id(EVP_PKEY_DSA, NULL);
		if (ctx_params == NULL || EVP_PKEY_paramgen_init(ctx_params) <= 0 || EVP_PKEY_CTX_set_dsa_paramgen_bits(ctx_params, atoi(sig_name + 3)) <= 0 || EVP_PKEY_paramgen(ctx_params, &pkey_params) <= 0 || (sig_gen_ctx = EVP_PKEY_CTX_new(pkey_params, NULL)) == NULL || EVP_PKEY_keygen_init(sig_gen_ctx) <= 0)
		{
			fprintf(stderr, "Error initializing classic keygen ctx for %s.\n",
					sig_name);
			return OQS_ERROR;
		}
	}

	if (sig_gen_ctx == NULL)
		sig_gen_ctx = EVP_PKEY_CTX_new_from_name(app_libctx,
												 use_params == 1 ? "RSA" : sig_name,
												 propq);

	if (!sig_gen_ctx || EVP_PKEY_keygen_init(sig_gen_ctx) <= 0 || (use_params && EVP_PKEY_CTX_set_params(sig_gen_ctx, params) <= 0))
	{
		fprintf(stderr, "Error initializing keygen ctx for %s.\n",
				sig_name);
		return OQS_ERROR;
	}
	if (EVP_PKEY_keygen(sig_gen_ctx, &pkey) <= 0)
	{
		fprintf(stderr,
				"Error while generating signature EVP_PKEY for %s.\n",
				sig_name);
		return OQS_ERROR;
	}
	/* Now prepare signature data structs */
	sig_sign_ctx = EVP_PKEY_CTX_new_from_pkey(app_libctx,
											  pkey,
											  propq);
	if (sig_sign_ctx == NULL || EVP_PKEY_sign_init(sig_sign_ctx) <= 0 || (use_params == 1 && (EVP_PKEY_CTX_set_rsa_padding(sig_sign_ctx, 1) <= 0)) || EVP_PKEY_sign(sig_sign_ctx, NULL, &max_sig_len, md, md_len) <= 0)
	{
		fprintf(stderr,
				"Error while initializing signing data structs for %s.\n",
				sig_name);
		return OQS_ERROR;
	}
	sig = malloc(sig_len = max_sig_len);
	if (sig == NULL)
	{
		fprintf(stderr, "MemAlloc error in sign for %s.\n", sig_name);
		return OQS_ERROR;
	}
	if (EVP_PKEY_sign(sig_sign_ctx, sig, &sig_len, md, md_len) <= 0)
	{
		fprintf(stderr, "Signing error for %s.\n", sig_name);
		return OQS_ERROR;
	}
	/* Now prepare verify data structs */
	memset(md, 0, 32);
	sig_verify_ctx = EVP_PKEY_CTX_new_from_pkey(app_libctx,
												pkey,
												propq);
	if (sig_verify_ctx == NULL || EVP_PKEY_verify_init(sig_verify_ctx) <= 0 || (use_params == 1 && (EVP_PKEY_CTX_set_rsa_padding(sig_verify_ctx, 1) <= 0)))
	{
		fprintf(stderr,
				"Error while initializing verify data structs for %s.\n",
				sig_name);
		return OQS_ERROR;
	}
	if (EVP_PKEY_verify(sig_verify_ctx, sig, sig_len, md, md_len) <= 0)
	{
		fprintf(stderr, "Verify error for %s.\n", sig_name);
		return OQS_ERROR;
	}
	if (EVP_PKEY_verify(sig_verify_ctx, sig, sig_len, md, md_len) <= 0)
	{
		fprintf(stderr, "Verify 2 error for %s.\n", sig_name);
		return OQS_ERROR;
	}
	printf("%-36s | %10s | %14s | %15s | %10s | %25s | %10s\n", sig_name, "", "", "", "", "", "");

	
	if (!doFullCycle)
	{
		if (!noKeygen)
			TIME_OPERATION_SECONDS(EVP_PKEY_keygen(sig_gen_ctx, &pkey), "keygen", duration)
		if (!noSign)
			TIME_OPERATION_SECONDS(EVP_PKEY_sign(sig_sign_ctx, sig, &sig_len, md, md_len), "sign", duration)
		if (!noVerify)
			TIME_OPERATION_SECONDS(EVP_PKEY_verify(sig_verify_ctx, sig, sig_len, md, md_len), "verify", duration)
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

	// for (count = 0; COND(kems_c[testnum][0]); count++) {
	//     EVP_PKEY_keygen(ctx, &pkey);
	//     /* TBD: How much does free influence runtime? */
	//     EVP_PKEY_free(pkey);
	//     pkey = NULL;
	// }
	return OQS_SUCCESS;
}

static OQS_STATUS sig_speed_wrapper(const char *method_name, uint64_t duration, bool printInfo, bool doFullCycle, bool noKeygen, bool noSign, bool noVerify)
{

	OQS_SIG *sig = NULL;
	uint8_t *public_key = NULL;
	uint8_t *secret_key = NULL;
	uint8_t *message = NULL;
	uint8_t *signature = NULL;
	size_t message_len = 50;
	size_t signature_len = 0;
	OQS_STATUS ret = OQS_ERROR;

	sig = OQS_SIG_new(method_name);
	if (sig == NULL)
	{
		return OQS_SUCCESS;
	}

	public_key = OQS_MEM_malloc(sig->length_public_key);
	secret_key = OQS_MEM_malloc(sig->length_secret_key);
	message = OQS_MEM_malloc(message_len);
	signature = OQS_MEM_malloc(sig->length_signature);

	if ((public_key == NULL) || (secret_key == NULL) || (message == NULL) || (signature == NULL))
	{
		fprintf(stderr, "ERROR: OQS_MEM_malloc failed\n");
		goto err;
	}

	OQS_randombytes(message, message_len);

	printf("%-36s | %10s | %14s | %15s | %10s | %25s | %10s\n", sig->method_name, "", "", "", "", "", "");
	if (!doFullCycle)
	{
		if (!noKeygen)
			TIME_OPERATION_SECONDS(OQS_SIG_keypair(sig, public_key, secret_key), "keypair", duration)
		if (!noSign)
			TIME_OPERATION_SECONDS(OQS_SIG_sign(sig, signature, &signature_len, message, message_len, secret_key), "sign", duration)
		if (!noVerify)
			TIME_OPERATION_SECONDS(OQS_SIG_verify(sig, message, message_len, signature, signature_len, public_key), "verify", duration)
	}
	else
	{
		TIME_OPERATION_SECONDS(fullcycle(sig, public_key, secret_key, signature, signature_len, message, message_len), "fullcycle", duration)
	}

	if (printInfo)
	{
		printf("public key bytes: %zu, secret key bytes: %zu, signature bytes: %zu\n", sig->length_public_key, sig->length_secret_key, sig->length_signature);
		if (signature_len != sig->length_signature)
		{
			printf("   Actual signature length returned (%zu) less than declared maximum signature length (%zu)\n", signature_len, sig->length_signature);
		}
	}

	ret = OQS_SUCCESS;
	goto cleanup;

err:
	ret = OQS_ERROR;

cleanup:
	if (sig != NULL)
	{
		OQS_MEM_secure_free(secret_key, sig->length_secret_key);
	}
	OQS_MEM_insecure_free(public_key);
	OQS_MEM_insecure_free(signature);
	OQS_MEM_insecure_free(message);
	OQS_SIG_free(sig);

	return ret;
}

static OQS_STATUS printAlgs(void)
{
	for (size_t i = 0; i < OQS_SIG_algs_length; i++)
	{
		OQS_SIG *sig = OQS_SIG_new(OQS_SIG_alg_identifier(i));
		if (sig == NULL)
		{
			printf("%s (disabled)\n", OQS_SIG_alg_identifier(i));
		}
		else
		{
			printf("%s\n", OQS_SIG_alg_identifier(i));
		}
		OQS_SIG_free(sig);
	}
	return OQS_SUCCESS;
}

int main_speed_sig(int argc, char **argv)
{

	int ret = EXIT_SUCCESS;
	OQS_STATUS rc;

	bool printUsage = false;
	uint64_t duration = 3;
	bool printSigInfo = false;
	bool doFullCycle = false;

	bool noKeygen = false;
	bool noVerify = false;
	bool noSign = false;

	bool noOQS = false;
	OQS_SIG *single_sig = NULL;
	const char *non_oqs_name = NULL;

	OQS_init();
	OQS_randombytes_switch_algorithm(OQS_RAND_alg_openssl);

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
			printSigInfo = true;
			continue;
		}
		else if ((strcmp(argv[i], "--fullcycle") == 0) || (strcmp(argv[i], "-f") == 0))
		{
			doFullCycle = true;
			continue;
		}
		else if ((strcmp(argv[i], "--no_keygen") == 0))
		{
			noKeygen = true;
			continue;
		}
		else if ((strcmp(argv[i], "--no_sign") == 0))
		{
			noSign = true;
			continue;
		}
		else if ((strcmp(argv[i], "--no_verify") == 0))
		{
			noVerify = true;
			continue;
		}
		else if ((strcmp(argv[i], "RSA") == 0))
		{
			non_oqs_name = "rsa2048";
			noOQS = true;
			single_sig = (OQS_SIG *) 1;
			break;
		}
		else if ((strcmp(argv[i], "DSA") == 0))
		{
			non_oqs_name = "dsa2048";
			noOQS = true;
			single_sig = (OQS_SIG *) 1;
			break;
		}
		else
		{
			single_sig = OQS_SIG_new(argv[i]);
			if (single_sig == NULL)
			{
				printUsage = true;
				break;
			}
		}
	}

	if (printUsage)
	{
		fprintf(stderr, "Usage: speed_sig <options> <alg>\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "<options>\n");
		fprintf(stderr, "--algs             Print supported algorithms and terminate\n");
		fprintf(stderr, "--duration n\n");
		fprintf(stderr, " -d n              Run each speed test for approximately n seconds, default n=3\n");
		fprintf(stderr, "--help\n");
		fprintf(stderr, " -h                Print usage\n");
		fprintf(stderr, "--info\n");
		fprintf(stderr, " -i                Print info (sizes, security level) about each SIG\n");
		fprintf(stderr, "--fullcycle\n");
		fprintf(stderr, " -f                Test full keygen-sign-verify cycle of each SIG\n");
		fprintf(stderr, "\n");
		fprintf(stderr, "<alg>              Only run the specified SIG method; must be one of the algorithms output by --algs\n");
		OQS_destroy();
		return EXIT_FAILURE;
	}

	// print_system_info();

	printf("Signature Speed test\n");
	printf("==========\n");

	PRINT_TIMER_HEADER
	if (single_sig != NULL)
	{
		if (noOQS)
		{	
			rc = sig_speed_ossl_wrapper(non_oqs_name, duration, printSigInfo, doFullCycle, noKeygen, noSign, noVerify);
		}
		else
		{
			rc = sig_speed_wrapper(single_sig->method_name, duration, printSigInfo, doFullCycle, noKeygen, noSign, noVerify);
		}
		if (rc != OQS_SUCCESS)
		{
			ret = EXIT_FAILURE;
		}
		//OQS_SIG_free(single_sig);
	}
	else
	{
		for (size_t i = 0; i < OQS_SIG_algs_length; i++)
		{
			rc = sig_speed_wrapper(OQS_SIG_alg_identifier(i), duration, printSigInfo, doFullCycle, noKeygen, noSign, noVerify);
			if (rc != OQS_SUCCESS)
			{
				ret = EXIT_FAILURE;
			}
		}
		if (noOQS)
		{
			rc = sig_speed_ossl_wrapper(single_sig->method_name, duration, printSigInfo, doFullCycle, noKeygen, noSign, noVerify);
		}
	}
	PRINT_TIMER_FOOTER
	OQS_destroy();

	return ret;
}