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
#include <oqs/common.h>

#define TCP_PROTOCOL_NAME "tcp"
#define REQUEST_SIZE 1024
#define RESPONSE_SIZE 4096

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

    printf("Connecting to: %s:%d\n", ip, port);
}

void perform_https_request(char* hostname, char* port, OSSL_LIB_CTX *libctx)
{
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
    errno = 0;
    SSL_CTX* ssl_context = SSL_CTX_new_ex(libctx, "", ssl_method);

    if (ssl_context == NULL)
    {
        report_error("Unable to create SSL context");
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

    SSL_set_fd(ssl, sock_client);
    rc = SSL_connect(ssl);

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

int main(int argc, char** argv)
{
    // if (argc != 3)
    // {
    //     print_usage(argv[0]);
    //     return -1;
    // }
    
    // perform_https_request(argv[1], argv[2]);
    const char *version = OpenSSL_version(OPENSSL_VERSION);
    printf("OpenSSL version: %s\n", version);
    printf("LibOQS version: %s\n", OQS_version());
    
    OSSL_LIB_CTX *libctx;
    int ret;

    libctx = OSSL_LIB_CTX_new();
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

    perform_https_request("172.44.0.1", "443", libctx);
    
    OSSL_LIB_CTX_free(libctx);
    return 0;
}