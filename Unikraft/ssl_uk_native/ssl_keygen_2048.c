#include <stdio.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

void print_key(RSA *rsa) {
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bio, rsa);

    char *public_key = NULL;
    long public_key_len = BIO_get_mem_data(bio, &public_key);
    printf("Public Key:\n%s\n", public_key);

    BIO_free(bio);

    bio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);

    char *private_key = NULL;
    long private_key_len = BIO_get_mem_data(bio, &private_key);
    printf("Private Key:\n%s\n", private_key);

    BIO_free(bio);
}

int main() {
    int keysize = 2048;
    RSA *rsa = NULL;
    BIGNUM *bn = NULL;

    // Initialize BIGNUM for RSA
    bn = BN_new();
    if (!BN_set_word(bn, RSA_F4)) {
        fprintf(stderr, "Error setting BIGNUM.\n");
        return 1;
    }

    // Generate RSA key
    rsa = RSA_new();
    if (!RSA_generate_key_ex(rsa, keysize, bn, NULL)) {
        fprintf(stderr, "Error generating RSA key.\n");
        return 1;
    }

    // Print the keys
    print_key(rsa);

    // Clean up
    RSA_free(rsa);
    BN_free(bn);

    return 0;

}