#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main() {
    const char *string = "this is a test";
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    SHA256((unsigned char*)string, strlen(string), hash);
    
    printf("SHA256(\"%s\") = ", string);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    
    return 0;
}
