// adapted from:
// https://github.com/nguyenchiemminhvu/LinuxNetworkProgramming/blob/main/01_networking_libraries/openssl/src/https_client.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <poll.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/opensslv.h>
#include <openssl/crypto.h>
#include <openssl/provider.h>
#include <openssl/safestack.h>
#include <openssl/core_names.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#include <oqs/common.h>

#include "certificate.h"

#define TCP_PROTOCOL_NAME "tcp"
#define REQUEST_SIZE 1024
#define RESPONSE_SIZE 4096

DEFINE_STACK_OF(EVP_KEM)

#define IS_FETCHABLE(type, TYPE)                                \
    static int is_ ## type ## _fetchable(const TYPE *alg)       \
    {                                                           \
        TYPE *impl;                                             \
        const char *propq = 0;                                  \
        OSSL_LIB_CTX *libctx = 0;                               \
        const char *name = TYPE ## _get0_name(alg);             \
                                                                \
        ERR_set_mark();                                         \
        impl = TYPE ## _fetch(libctx, name, propq);             \
        ERR_pop_to_mark();                                      \
        if (impl == NULL)                                       \
            return 0;                                           \
        TYPE ## _free(impl);                                    \
        return 1;                                               \
    }


IS_FETCHABLE(kem, EVP_KEM)

void print_usage(const char *program_name)
{
    fprintf(stderr, "Usage: %s <hostname> <port>\n", program_name);
}

void report_error(const char* message)
{
    fprintf(stderr, "Error: %s; Errno: %d\n", message, errno);
}

void print_sockaddr_info(struct sockaddr *sa)
{
    char ip[INET6_ADDRSTRLEN];
    memset(ip, 0, INET6_ADDRSTRLEN);

    void *addr;
    int port;

    if (sa->sa_family == AF_INET)
    {
        struct sockaddr_in *sin = (struct sockaddr_in *)sa;
        addr = &(sin->sin_addr);
        port = ntohs(sin->sin_port);
    }
    else if (sa->sa_family == AF_INET6)
    {
        struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)sa;
        addr = &(sin6->sin6_addr);
        port = ntohs(sin6->sin6_port);
    }
    else
    {
        report_error("Unknown address family");
        return;
    }

    if (inet_ntop(sa->sa_family, addr, ip, sizeof(ip)) == NULL)
    {
        report_error("inet_ntop() failed");
        return;
    }

    printf("Connecting to: %s:%d\n\n", ip, port);
}

void perform_https_request(char* hostname, char* port)
{
  
    // printf("Certificate: \n %s\n", ca_certificate);
    BIO *mem = BIO_new_mem_buf((void *) ca_certificate, 8096);
    if (NULL == mem)
    {
        report_error("BIO_new_mem_buf() failed");
        ERR_print_errors_fp(stderr);
        return;
    }
    // char buf[512];
    // BIO_gets(mem, buf, 255);
    // printf("Certificate: %s\n", buf);
    // BIO_gets(mem, buf, 255);
    // printf("Certificate: %s\n", buf);

    X509 *x_509 = PEM_read_bio_X509(mem, NULL, 0, NULL);
    if (NULL == x_509)
    {
        report_error("PEM_read_bio_X509() failed");
        ERR_print_errors_fp(stderr);
        return;
    }

    int rc;
    struct protoent* tcp_proto = getprotobyname(TCP_PROTOCOL_NAME);
    if (tcp_proto == NULL)
    {
        report_error("TCP protocol is not supported");
        return;
    }

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = tcp_proto->p_proto;
    struct addrinfo* addr_server;
    rc = getaddrinfo(hostname, port, &hints, &addr_server);
    if (rc != 0)
    {
        report_error("Resolve address failed");
        return;
    }

    int sock_client = socket(addr_server->ai_family, addr_server->ai_socktype, addr_server->ai_protocol);
    if (sock_client < 0)
    {
        report_error("socket() failed");
        return;
    }
    for (struct addrinfo* p_server = addr_server; p_server != NULL; p_server = p_server->ai_next)
    {
        print_sockaddr_info(p_server->ai_addr);
        rc = connect(sock_client, p_server->ai_addr, p_server->ai_addrlen);
        if (rc == 0)
        {
            break;
        }
    }

    if (rc != 0)
    {
        report_error("connect() failed");
        return;
    }
    
    SSL_load_error_strings();
    SSL_library_init();

    const SSL_METHOD* ssl_method = TLS_client_method();

    SSL_CTX* ssl_context = SSL_CTX_new(ssl_method);
    if (ssl_context == NULL)
    {
        report_error("Unable to create SSL context");
        ERR_print_errors_fp(stderr);
        freeaddrinfo(addr_server);
        close(sock_client);
        return;
    }
    
    SSL* ssl = SSL_new(ssl_context);
    if (ssl == NULL)
    {
        report_error("SSL_new() failed");
        freeaddrinfo(addr_server);
        close(sock_client);
        SSL_CTX_free(ssl_context);
        return;
    }

    rc = SSL_add1_to_CA_list(ssl, x_509);
    if (rc <= 0)
    {
        report_error("SSL_add1_to_CA_list() failed");
        ERR_print_errors_fp(stderr);
        freeaddrinfo(addr_server);
        close(sock_client);
        SSL_CTX_free(ssl_context);
        SSL_shutdown(ssl);
        SSL_free(ssl);
        return;
    }

    SSL_set_verify(ssl, SSL_VERIFY_PEER, NULL);

    rc = SSL_set1_groups_list(ssl, "kyber768:kyber1024");
    if (rc <= 0)
    {
        report_error("SSL_set1_groups_list() failed");
        ERR_print_errors_fp(stderr);
        freeaddrinfo(addr_server);
        close(sock_client);
        SSL_CTX_free(ssl_context);
        SSL_shutdown(ssl);
        SSL_free(ssl);
        return;
    }

    // printf("Supported ciphers: \n");
    // STACK_OF(SSL_CIPHER) * ciphers = SSL_CTX_get_ciphers(ssl_context);
    // for (int i = sk_SSL_CIPHER_num(ciphers); i > 0; i--)
    // {
    //     printf("%s, ", SSL_CIPHER_get_name(sk_SSL_CIPHER_pop(ciphers)));
    // }
    // printf("\n");
    
    SSL_set_fd(ssl, sock_client);
    rc = SSL_connect(ssl);

    if (X509_V_OK != SSL_get_verify_result(ssl))
    {
        report_error("SSL_get_verify_result() failed");
        ERR_print_errors_fp(stderr);
    }

    if (rc <= 0)
    {
        report_error("SSL_connect() failed");
        ERR_print_errors_fp(stderr);
        freeaddrinfo(addr_server);
        close(sock_client);
        SSL_CTX_free(ssl_context);
        SSL_shutdown(ssl);
        SSL_free(ssl);
        return;
    }

    printf("SSL connection is done with cipher suite %s\n", SSL_get_cipher(ssl));

    char http_request[REQUEST_SIZE];
    memset(http_request, 0, REQUEST_SIZE);
    sprintf(http_request, "GET /test.html HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", hostname);

    rc = SSL_write(ssl, http_request, strlen(http_request));

    if (rc <= 0)
    {
        report_error("SSL_write() failed");
        ERR_print_errors_fp(stderr);
        freeaddrinfo(addr_server);
        close(sock_client);
        SSL_CTX_free(ssl_context);
        SSL_shutdown(ssl);
        SSL_free(ssl);
        return;
    }

    char http_response[RESPONSE_SIZE + 1];
    memset(http_response, 0, RESPONSE_SIZE);
    int received_bytes = 0;
    int total_received_bytes = 0;
    do
    {   

        received_bytes = SSL_read(ssl, http_response + total_received_bytes, RESPONSE_SIZE - total_received_bytes);

        if (received_bytes > 0)
        {
            printf("Received %d bytes:\n\n", received_bytes);
            total_received_bytes += received_bytes;
        }
    } while (received_bytes > 0);

    http_response[total_received_bytes] = 0;
    printf("%s\n", http_response);

    freeaddrinfo(addr_server);
    close(sock_client);
    SSL_CTX_free(ssl_context);
    SSL_shutdown(ssl);
    SSL_free(ssl);
}

/** \brief The initialization function of oqsprovider. */
extern OSSL_provider_init_fn oqs_provider_init;

/** \brief Name of the oqsprovider. */
static const char *kOQSProviderName = "oqsprovider";

/** \brief Tries to load the oqsprovider named "oqsprovider".
 *
 * \param libctx Context of the OpenSSL library in which to load the
 * oqsprovider.
 *
 * \returns 0 if success, else -1. */
static int load_oqs_provider(OSSL_LIB_CTX *libctx)
{
    OSSL_PROVIDER *provider;
    int ret;

    ret = OSSL_PROVIDER_available(libctx, kOQSProviderName);
    if (ret != 0) {
        fprintf(stderr,
                "`OSSL_PROVIDER_available` returned %i, but 0 was expected\n",
                ret);
        return -1;
    }

    ret = OSSL_PROVIDER_add_builtin(libctx, kOQSProviderName,
                                    oqs_provider_init);
    if (ret != 1) {
        fprintf(stderr,
                "`OSSL_PROVIDER_add_builtin` failed with returned code %i\n",
                ret);
        return -1;
    }

    provider = OSSL_PROVIDER_load(libctx, kOQSProviderName);
    if (provider == NULL) {
        fputs("`OSSL_PROVIDER_load` failed\n", stderr);
        return -1;
    }

    ret = OSSL_PROVIDER_available(libctx, kOQSProviderName);
    if (ret != 1) {
        fprintf(stderr,
                "`OSSL_PROVIDER_available` returned %i, but 0 was expected\n",
                ret);
        return -1;
    }

    ret = OSSL_PROVIDER_self_test(provider);
    if (ret != 1) {
        fprintf(stderr,
                "`OSSL_PROVIDER_self_test` failed with returned code %i\n",
                ret);
        return -1;
    }

    printf("Loaded provider: %s\n", OSSL_PROVIDER_get0_name(provider));

    return 0;
}

static int list_provider_tls_sigalgs(const OSSL_PARAM params[], void *data)
{
    const OSSL_PARAM *p;

    /* Get registered IANA name */
    p = OSSL_PARAM_locate_const(params, OSSL_CAPABILITY_TLS_SIGALG_IANA_NAME);
    if (p != NULL && p->data_type == OSSL_PARAM_UTF8_STRING) {
        if (*((int *)data) > 0)
            printf(":");
        printf("%s", (char *)(p->data));
        /* mark presence of a provider-based sigalg */
        *((int *)data) = 2;
    }
    /* As built-in providers don't have this capability, never error */
    return 1;
}

static int list_tls_sigalg_caps(OSSL_PROVIDER *provider, void *cbdata)
{
    OSSL_PROVIDER_get_capabilities(provider, "TLS-SIGALG",
                                   list_provider_tls_sigalgs,
                                   cbdata);
    /* As built-in providers don't have this capability, never error */
    return 1;
}

int name_cmp(const char * const *a, const char * const *b)
{
    return OPENSSL_strcasecmp(*a, *b);
}

static void collect_kem(EVP_KEM *kem, void *stack)
{
    STACK_OF(EVP_KEM) *kem_stack = stack;

    if (is_kem_fetchable(kem)
            && sk_EVP_KEM_push(kem_stack, kem) > 0)
        EVP_KEM_up_ref(kem);
}


static int kem_cmp(const EVP_KEM * const *a,
                   const EVP_KEM * const *b)
{
    return strcmp(OSSL_PROVIDER_get0_name(EVP_KEM_get0_provider(*a)),
                  OSSL_PROVIDER_get0_name(EVP_KEM_get0_provider(*b)));
}

void print_names(STACK_OF(OPENSSL_CSTRING) *names)
{
    int i = sk_OPENSSL_CSTRING_num(names);
    int j;

    sk_OPENSSL_CSTRING_sort(names);
    if (i > 1)
        printf("{ ");
    for (j = 0; j < i; j++) {
        const char *name = sk_OPENSSL_CSTRING_value(names, j);

        if (j > 0)
            printf(", ");
        printf("%s", name);
    }
    if (i > 1)
        printf(" }");
}

void collect_names(const char *name, void *vdata)
{
    STACK_OF(OPENSSL_CSTRING) *names = vdata;

    sk_OPENSSL_CSTRING_push(names, name);
}

static void list_kems(OSSL_LIB_CTX *libctx)
{
    int i, count = 0;
    STACK_OF(EVP_KEM) *kem_stack = sk_EVP_KEM_new(kem_cmp);

    EVP_KEM_do_all_provided(libctx, collect_kem, kem_stack);
    sk_EVP_KEM_sort(kem_stack);

    for (i = 0; i < sk_EVP_KEM_num(kem_stack); i++) {
        EVP_KEM *k = sk_EVP_KEM_value(kem_stack, i);
        STACK_OF(OPENSSL_CSTRING) *names = NULL;

        names = sk_OPENSSL_CSTRING_new(name_cmp);
        if (names != NULL && EVP_KEM_names_do_all(k, collect_names, names)) {
            count++;
            printf("  ");
            print_names(names);

            printf(" @ %s\n",
                       OSSL_PROVIDER_get0_name(EVP_KEM_get0_provider(k)));

        }
        sk_OPENSSL_CSTRING_free(names);
    }
    sk_EVP_KEM_pop_free(kem_stack, EVP_KEM_free);
    if (count == 0)
        printf(" -\n");
}


int main(int argc, char** argv)
{
    
    printf("\n");
    printf("OpenSSL version: %s\n", OpenSSL_version(OPENSSL_VERSION));
    printf("LibOQS version: %s\n", OQS_version());
    
    OSSL_LIB_CTX *libctx;
    int ret;

    libctx = OSSL_LIB_CTX_get0_global_default();
    if (libctx == NULL) {
        fputs("`OSSL_LIB_CTX_new` failed. Cannot initialize OpenSSL.\n",
              stderr);
        return 1;
    }

    ret = load_oqs_provider(libctx);
    if (ret != 0) {
        fputs("`load_oqs_provider` failed. Dumping OpenSSL error queue.\n",
              stderr);
        ERR_print_errors_fp(stderr);
        return 2;
    }
    printf("\n");

    printf("Available Key encapsulation mechanisms: \n");
    list_kems(libctx);
    
    printf("\n");
    char *builtin_sigalgs = SSL_get1_builtin_sigalgs(libctx);
    printf("Available Signatures schemes: %s", builtin_sigalgs);
    int tls_sigalg_listed = 0;
    OSSL_PROVIDER_do_all(NULL, list_tls_sigalg_caps, &tls_sigalg_listed);
    if (tls_sigalg_listed < 2)
        printf("\nNo TLS sig algs registered by currently active providers");
    
    printf("\n\n");

    const char *string = "this is a test";

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)string, strlen(string), hash);
    printf("SHA256(\"%s\") = ", string);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    
    printf("\n\n");
    
    perform_https_request("172.44.0.1", "443");
    
    return 0;
}
