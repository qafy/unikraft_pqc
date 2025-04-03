#include <stdio.h>
#include <string.h>
#include <openssl/crypto.h>
#include <openssl/sha.h>

int main() {

    printf("Hello");
    printf("\n");

    const char *string = "this is a test";
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)string, strlen(string), hash);
    printf("SHA256(\"%s\") = ", string);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }

    // int res = math(5);
    // printf("Res: %d\n", res);

    printf("Hello");
    printf("\n");

    return 0;
}

// #include <stdio.h>
// #include <openssl/opensslv.h>
// #include <openssl/crypto.h>

// int main() {
//     // Get the OpenSSL version
//     const char *version = OpenSSL_version(OPENSSL_VERSION);

//     // Print the version
//     printf("OpenSSL version: %s\n", version);

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <unistd.h>
// #include <time.h>
// #include <openssl/opensslv.h>
// #include <openssl/crypto.h>
// // Signal handler function
// void handle_sigusr1(int sig)
// {
//     printf("Caught signal %d (SIGUSR1). Performing action...\n", sig);
// }

// int main()
// {
//     // Register the signal handler for SIGUSR1
//     signal(SIGUSR1, handle_sigusr1);

//     printf("The program will send SIGUSR1 to itself in 5 seconds...\n");

//     // Sleep for 5 seconds
//     sleep(5);
//     char *ls = OpenSSL_version(OPENSSL_VERSION);
//     printf("Current OPENSSL Version: %s\n", ls);
//     // Send SIGUSR1 to the current process
//     kill(getpid(), SIGUSR1);

//     // Continue running to allow the signal to be caught
//     printf("Waiting for the signal...\n");
//     while (1)
//     {
//         sleep(1); // Sleep for 1 second
//     }

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <setjmp.h>
// #include <unistd.h>

// // Declare a jump buffer
// jmp_buf jump_buffer;

// // Signal handler function
// void handle_sigusr1(int sig) {
//     printf("Caught signal %d (SIGUSR1). Jumping back to safe point...\n", sig);
//     longjmp(jump_buffer, 1); // Jump back to the point saved by setjmp
// }

// int main() {
//     // Register the signal handler for SIGUSR1
//     signal(SIGUSR1, handle_sigusr1);
//     math();
//     // Set a jump point
//     if (setjmp(jump_buffer) == 0) {
//         // This block runs first
//         printf("Running... (Waiting for SIGUSR1 to be sent automatically)\n");

//         // Sleep for 5 seconds before sending the signal
//         sleep(5);

//         // Send SIGUSR1 to the current process
//         kill(getpid(), SIGUSR1);

//         // Continue running to allow the signal to be caught
//         printf("Waiting for the signal...\n");
//         while (1) {
//             printf("Working...\n");
//             sleep(1); // Sleep for 1 second
//         }
//     } else {
//         // This block runs after longjmp is called
//         printf("Returned to safe point after handling SIGUSR1.\n");
//     }

//     return 0;
// }
