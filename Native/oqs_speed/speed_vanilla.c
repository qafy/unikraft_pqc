#include <openssl/evp.h>
#include <openssl/ec.h>
#include <stdbool.h>
#include <oqs/oqs.h>
#include <stdio.h>
#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/objects.h>
#include <openssl/core_names.h>
#include <openssl/async.h>
#include <openssl/provider.h>
#include <openssl/dsa.h>
#include <openssl/rsa.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/bn.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>
#include "ds_benchmark.h"



struct derivedKey
{
	char *secret;
	size_t length;
};

typedef struct derivedKey derivedKey;

void handleErrors()
{
	ERR_print_errors_fp(stderr);
	abort();
}

void handleDerivationErrors(int x)
{
	printf("\n\nDerivation Failed...");
	printf("%d", x);
}

EVP_PKEY *generateKey()
{
	EVP_PKEY_CTX *paramGenCtx = NULL, *keyGenCtx = NULL;
	EVP_PKEY *params = NULL, *keyPair = NULL;

	paramGenCtx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);

	if (!EVP_PKEY_paramgen_init(paramGenCtx))
		handleErrors();

	EVP_PKEY_CTX_set_ec_paramgen_curve_nid(paramGenCtx, NID_X9_62_prime256v1);

	EVP_PKEY_paramgen(paramGenCtx, &params);

	keyGenCtx = EVP_PKEY_CTX_new(params, NULL);

	if (!EVP_PKEY_keygen_init(keyGenCtx))
		handleErrors();

	if (!EVP_PKEY_keygen(keyGenCtx, &keyPair))
		handleErrors();

	EC_KEY *ecKey = EVP_PKEY_get1_EC_KEY(keyPair);

	BIGNUM *privKey = EC_KEY_get0_private_key(ecKey);

	EC_POINT *pubPoint = EC_KEY_get0_public_key(ecKey);

	BIGNUM *x = BN_new();

	BIGNUM *y = BN_new();

	EC_POINT_get_affine_coordinates_GFp(EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1), pubPoint, x, y, NULL);

	// printf("\nprivate : ");

	// BN_print_fp(stdout, privKey);

	// printf("\npubX : ");

	// BN_print_fp(stdout, x);

	// printf("\npubY : ");

	// BN_print_fp(stdout, y);

	EVP_PKEY_CTX_free(paramGenCtx);
	EVP_PKEY_CTX_free(keyGenCtx);

	return keyPair;
}

/**
	Takes in a private key and extracts the public key from it.
*/
EVP_PKEY *extractPublicKey(EVP_PKEY *privateKey)
{
	EC_KEY *ecKey = EVP_PKEY_get1_EC_KEY(privateKey);
	EC_POINT *ecPoint = EC_KEY_get0_public_key(ecKey);

	EVP_PKEY *publicKey = EVP_PKEY_new();

	EC_KEY *pubEcKey = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);

	EC_KEY_set_public_key(pubEcKey, ecPoint);

	EVP_PKEY_set1_EC_KEY(publicKey, pubEcKey);

	EC_KEY_free(ecKey);
	EC_POINT_free(ecPoint);

	return publicKey;
}

/**
	Takes in the private key and peer public key and spits out the derived shared secret.
*/
derivedKey *deriveShared(EVP_PKEY *publicKey, EVP_PKEY *privateKey)
{

	derivedKey *dk = (derivedKey *)malloc(sizeof(derivedKey));
	EVP_PKEY_CTX *derivationCtx = NULL;
	derivationCtx = EVP_PKEY_CTX_new(privateKey, NULL);
	EVP_PKEY_derive_init(derivationCtx);
	EVP_PKEY_derive_set_peer(derivationCtx, publicKey);
	if (1 != EVP_PKEY_derive(derivationCtx, NULL, &dk->length))
		handleDerivationErrors(0);
	if (NULL == (dk->secret = OPENSSL_malloc(dk->length)))
		handleDerivationErrors(1);
	if (1 != (EVP_PKEY_derive(derivationCtx, dk->secret, &dk->length)))
		handleDerivationErrors(2);
	EVP_PKEY_CTX_free(derivationCtx);
	return dk;
}

void deriveBenchmark(EVP_PKEY_CTX *derivationCtx, EVP_PKEY *keyPairPub, derivedKey *dk)
{
	EVP_PKEY_derive_init(derivationCtx);
	EVP_PKEY_derive_set_peer(derivationCtx, keyPairPub);
	if (1 != EVP_PKEY_derive(derivationCtx, NULL, &dk->length))
		handleDerivationErrors(0);
	if (NULL == (dk->secret = OPENSSL_malloc(dk->length)))
		handleDerivationErrors(1);
	if (1 != (EVP_PKEY_derive(derivationCtx, dk->secret, &dk->length)))
		handleDerivationErrors(2);
	
	OPENSSL_free(dk->secret);
}

OQS_STATUS kem_vanilla(uint64_t duration, bool noKeygen, bool noSign, bool noVerify)
{

	printf("%-36s | %10s | %14s | %15s | %10s | %25s | %10s\n", "ecdhe", "", "", "", "", "", "");

	EVP_PKEY_CTX *paramGenCtx = NULL, *keyGenCtx = NULL;
	EVP_PKEY *params = NULL, *keyPair = NULL;

	paramGenCtx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL);
	if (!EVP_PKEY_paramgen_init(paramGenCtx))
		handleErrors();
	EVP_PKEY_CTX_set_ec_paramgen_curve_nid(paramGenCtx, NID_X9_62_prime256v1);
	EVP_PKEY_paramgen(paramGenCtx, &params);

	keyGenCtx = EVP_PKEY_CTX_new(params, NULL);
	if (!EVP_PKEY_keygen_init(keyGenCtx))
		handleErrors();

	if (!EVP_PKEY_keygen(keyGenCtx, &keyPair))
		handleErrors();

	if (!noKeygen)
		TIME_OPERATION_SECONDS(EVP_PKEY_keygen(keyGenCtx, &keyPair), "keygen", duration);

	// print results
	EC_KEY *ecKey = EVP_PKEY_get1_EC_KEY(keyPair);
	BIGNUM *privKey = EC_KEY_get0_private_key(ecKey);
	EC_POINT *pubPoint = EC_KEY_get0_public_key(ecKey);

	BIGNUM *x = BN_new();
	BIGNUM *y = BN_new();
	// prime256v1 == secp256r1
	EC_POINT_get_affine_coordinates_GFp(EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1), pubPoint, x, y, NULL);

	EVP_PKEY_CTX_free(paramGenCtx);
	EVP_PKEY_CTX_free(keyGenCtx);

	// derive second keypair
	EVP_PKEY *secondKeyPair = generateKey();

	EVP_PKEY *keyPairPub = extractPublicKey(keyPair);

	// derive shared secret
	derivedKey *dk = (derivedKey *)malloc(sizeof(derivedKey));
	EVP_PKEY_CTX *derivationCtx = NULL;
	derivationCtx = EVP_PKEY_CTX_new(secondKeyPair, NULL);

	EVP_PKEY_derive_init(derivationCtx);
	EVP_PKEY_derive_set_peer(derivationCtx, keyPairPub);
	if (1 != EVP_PKEY_derive(derivationCtx, NULL, &dk->length))
		handleDerivationErrors(0);
	if (NULL == (dk->secret = OPENSSL_malloc(dk->length)))
		handleDerivationErrors(1);
	if (1 != (EVP_PKEY_derive(derivationCtx, dk->secret, &dk->length)))
		handleDerivationErrors(2);

	if (!noSign)
		TIME_OPERATION_SECONDS(deriveBenchmark(derivationCtx, keyPairPub, dk), "derive", duration);

	EVP_PKEY *secondKeyPairPub = extractPublicKey(secondKeyPair);

	derivedKey *secretBob = deriveShared(secondKeyPairPub, keyPair);

	BIGNUM *secretAliceBN = BN_new();

	BIGNUM *secretBobBN = BN_new();

	// printf("\nprivate : ");
	// BN_print_fp(stdout, privKey);
	// printf("\npubX : ");
	// BN_print_fp(stdout, x);
	// printf("\npubY : ");
	// BN_print_fp(stdout, y);

	// BN_bin2bn(dk->secret, dk->length, secretAliceBN);

	// BN_bin2bn(secretBob->secret, secretBob->length, secretBobBN);

	// printf("\n\nSecret computed by Alice :\n");

	// BN_print_fp(stdout, secretAliceBN);

	// printf("\nSecret computed by Bob : \n");

	// BN_print_fp(stdout, secretBobBN);

	// if(BN_cmp(secretAliceBN, secretBobBN) == 0){
	//     printf("\n\nSecrets computed were equal! Magic of ECDH\n\n");
	// }
	if (!noVerify)
		printf("%-36s | %10s | %14s | %15s | %10s | %25s | %10s\n", "-", "0.0", "0.0", "0.0", "0.0", "0.0", "0.0");
	return OQS_SUCCESS;
}

OQS_STATUS sig_vanilla_rsa2048(uint64_t duration, bool noKeygen, bool noSign, bool noVerify)
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

	char *sig_name = "rsa2048";
	memset(md, 0, 32);

	/* no string after rsa<bitcnt> permitted: */
	if (strlen(sig_name) < 100 + 4 /* rsa+digit */
		&& sscanf(sig_name, "rsa%u%s", &bits, sfx) == 1)
	{
		params[0] = OSSL_PARAM_construct_uint("bits",
											  &bits);
		use_params = 1;
	}

	if (sig_gen_ctx == NULL)
		if (!(sig_gen_ctx = EVP_PKEY_CTX_new_from_name(app_libctx, "RSA", propq)))
			handleErrors();

	if (EVP_PKEY_keygen_init(sig_gen_ctx) <= 0 || (use_params && EVP_PKEY_CTX_set_params(sig_gen_ctx, params) <= 0))
		handleErrors();
	if (EVP_PKEY_keygen(sig_gen_ctx, &pkey) <= 0)
		handleErrors();
	if (!(sig_sign_ctx = EVP_PKEY_CTX_new_from_pkey(app_libctx, pkey, propq)))
		handleErrors();

	if (EVP_PKEY_sign_init(sig_sign_ctx) <= 0 || (use_params == 1 && (EVP_PKEY_CTX_set_rsa_padding(sig_sign_ctx, 1) <= 0)) || EVP_PKEY_sign(sig_sign_ctx, NULL, &max_sig_len, md, md_len) <= 0)
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
	if (!noKeygen)
		TIME_OPERATION_SECONDS(EVP_PKEY_keygen(sig_gen_ctx, &pkey), "keygen", duration)
	if (!noSign)
		TIME_OPERATION_SECONDS(EVP_PKEY_sign(sig_sign_ctx, sig, &sig_len, md, md_len), "sign", duration)
	if (!noVerify)
		TIME_OPERATION_SECONDS(EVP_PKEY_verify(sig_verify_ctx, sig, sig_len, md, md_len), "verify", duration)

	return OQS_SUCCESS;
}

OQS_STATUS sig_vanilla_ecdsa(uint64_t duration, bool noKeygen, bool noSign, bool noVerify)
{
	printf("%-36s | %10s | %14s | %15s | %10s | %25s | %10s\n", "ecdsa", "", "", "", "", "", "");

	unsigned char md[32];
	size_t md_len = 32;
	memset(md, 0, 32);

	EC_KEY *key_pair_obj = 0;
	int ret_error;
	BIGNUM *priv_key;
	EC_POINT *pub_key;
	EC_GROUP *secp256r1_group;
	char *pub_key_char, *priv_key_char;

	unsigned char buffer_digest[SHA256_DIGEST_LENGTH];
	uint8_t *digest;
	uint8_t *signature;
	uint32_t signature_len;
	int verification;

	BIGNUM *bn;
	EC_KEY *imported_key_pair = 0;
	EC_GROUP *curve_group;
	EC_POINT *public_point;
	int char_read;

	// Generate secp256k1 key pair
	key_pair_obj = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
	ret_error = EC_KEY_generate_key(key_pair_obj);

	if (!noKeygen)
		TIME_OPERATION_SECONDS(EC_KEY_generate_key(key_pair_obj), "keygen", duration)

	// Get private key
	priv_key = (BIGNUM *)EC_KEY_get0_private_key(key_pair_obj);
	priv_key_char = BN_bn2hex(priv_key);

	// Get public key
	pub_key = (EC_POINT *)EC_KEY_get0_public_key(key_pair_obj);
	secp256r1_group = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
	pub_key_char = EC_POINT_point2hex(secp256r1_group, pub_key, POINT_CONVERSION_COMPRESSED, 0);
	EC_GROUP_free(secp256r1_group);

	// printf("Pivate key: %s\n", priv_key_char);
	// printf("Public key: %s\n", pub_key_char);

	// Sign message
	signature_len = ECDSA_size(key_pair_obj); // the signature size depends on the key
	signature = (uint8_t *)OPENSSL_malloc(signature_len);
	ret_error = ECDSA_sign(0, (const uint8_t *)md, md_len, signature, &signature_len, key_pair_obj);

	if (!noSign)
		TIME_OPERATION_SECONDS(ECDSA_sign(0, (const uint8_t *)md, md_len, signature, &signature_len, key_pair_obj), "sign", duration)

	// printf("Message SHA256: ");
	// for (uint32_t i = 0; i < md_len; i++)
	// 	printf("%02x", md[i]);
	// printf("\n");
	// printf("Signature     : ");
	// for (uint32_t i = 0; i < signature_len; i++)
	// 	printf("%02x", signature[i]);
	// printf("\n");

	// Verify the signature
	verification = ECDSA_verify(0, md, md_len, signature, signature_len, key_pair_obj);
	// if (verification == 1)
	// 	printf("Verification    successful\n");
	// else
	// 	printf("Verification    NOT successful\n");

	if (!noVerify)
		TIME_OPERATION_SECONDS(ECDSA_verify(0, md, md_len, signature, signature_len, key_pair_obj), "verify", duration)

	// Double check process for correctness
	imported_key_pair = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
	curve_group = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
	public_point = EC_POINT_new(curve_group);
	public_point = EC_POINT_hex2point(curve_group, pub_key_char, public_point, 0);
	ret_error = EC_KEY_set_public_key(imported_key_pair, public_point);
	EC_GROUP_free(curve_group);
	EC_POINT_free(public_point);
	free(pub_key_char);

	bn = BN_new();
	char_read = BN_hex2bn(&bn, priv_key_char);
	ret_error = EC_KEY_set_private_key(imported_key_pair, bn);
	BN_clear_free(bn);
	free(priv_key_char);

	verification = ECDSA_verify(0, md, md_len, signature, signature_len, imported_key_pair);
	// if (verification == 1)
	// 	printf("Re-Verification successful\n");
	// else
	// 	printf("Re-Verification NOT successful\n");
	// EC_KEY_free(imported_key_pair);

	//OPENSSL_free(signature);

	return OQS_SUCCESS;

}