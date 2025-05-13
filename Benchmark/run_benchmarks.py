#!/usr/bin/env python3

# import docker
# import docker.errors
import socket
import time
import subprocess
import argparse
import json
import os
import signal 

UNIKRAFT = "172.44.0.1", "172.44.0.2"
DOCKER = None
SCRIPT_PATH = __file__
SCRIPT_DIR = os.path.dirname(SCRIPT_PATH)

def main():
    parser = argparse.ArgumentParser(
        description="Run the target as client or server, default: server"
    )
    parser.add_argument(
        "--mode",
        choices=["server", "client"],
        default="server",
        required=False,
        help="Specify whether to run as a server or client.",
    )

    parser.add_argument(
        "--virt",
        choices=["native", "docker", "unikraft"],
        required=False,
        default="native",
        help="Specify a virtualization method, default is nativ.",
    )

    parser.add_argument(
        "--algcert",
        required=False,
        default="dilithium5",
        help="Specify the used method for certificate generation",
    )

    parser.add_argument(
        "--newcert", action="store_true", help="Force generation of certificates"
    )

    parser.add_argument(
        "--test", action="store_true", help="Test connection with s_client"
    )

    args = parser.parse_args()

    if args.newcert or not os.path.exists(SCRIPT_DIR + "../pki"):
        setup_certificates(args.algcert)
    
    if args.virt == "docker":
        DOCKER = get_container_ip()
    
    try:
        if args.test:
            if args.mode == "server":
                prc0 = run_s_server(args.virt)
                if not check_server(get_host("client", args.virt), 1):
                    print("Cannot connect to server")
                    return
                prc1 = run_s_client("native")
                prc1.wait()
                prc0.kill()

            elif args.mode == "client":
                prc0 = run_s_server("native")
                if not check_server(get_host("client", args.virt), 1):
                    print("Cannot connect to server")
                    return
                prc1 = run_s_client(args.virt)
                prc1.wait()
                prc0.kill()

        else:
            if args.mode == "server":
                prc0 = run_s_server(args.virt)
                prc1 = run_s_time("native")
                prc1.wait()
                prc0.kill()

            elif args.mode == "client":
                prc0 = run_s_server("native")
                prc1 = run_s_time(args.virt)
                prc1.wait()
                prc0.kill()

    except KeyboardInterrupt:
        pass
    
    subprocess.run(["pkill", "openssl"])
    subprocess.run(["pkill", "docker"])
    subprocess.run(["pkill", "qemu"])
        

def run_s_server(virt):
    openssl_version = get_openssl_bin(virt)

    return subprocess.Popen(
        [
            openssl_version,
            "s_server",
            "-key",
            "pki/server_dil.key",
            "-cert",
            "pki/server_dil.crt",
            "-accept",
            "443",
            "-www",
        ],
        start_new_session=True,
        stdout=subprocess.DEVNULL,
    )


def run_s_client(virt):
    openssl_version = get_openssl_bin(virt)
    host = get_host("client", virt)

    return subprocess.Popen(
        [
            openssl_version,
            "s_client",
            "-connect",
            host + ":443",
            "-verifyCAfile",
            "pki/CA_dil.crt",
            "-ign_eof",
            "-nocommands",
        ],
        start_new_session=True,
        stdout=subprocess.DEVNULL,
    )


def run_s_time(virt):
    openssl_version = get_openssl_bin(virt)
    host = get_host("client", virt)

    return subprocess.Popen(
        [
            openssl_version,
            "s_time",
            "-connect",
            host + ":443",
            "-www",
            "/",
            "-CAfile",
            "pki/CA_dil.crt",
        ],
        start_new_session=True,
        stdout=None,
    )


def check_server(host, timeout):
    for i in range(timeout):
        try:
            time.sleep(1)
            with socket.create_connection((host, 443), timeout=5):
                return True
        except (socket.timeout, ConnectionRefusedError):
            return False


def setup_certificates(cypher):

    subprocess.run(
        [
            "Native/openssl",
            "req",
            "-x509",
            "-new",
            "-newkey",
            cypher,
            "-keyout",
            "pki/CA_dil.key",
            "-out",
            "pki/CA_dil.crt",
            "-nodes",
            "-subj",
            "/CN=Test CA",
            "-days",
            "365",
        ]
    )

    subprocess.run(
        [
            "Native/openssl",
            "req",
            "-new",
            "-newkey",
            cypher,
            "-keyout",
            "pki/server_dil.key",
            "-out",
            "pki/server_dil.csr",
            "-nodes",
            "-subj",
            "/CN=testserver",
        ]
    )

    subprocess.run(
        [
            "Native/openssl",
            "x509",
            "-req",
            "-in",
            "pki/server_dil.csr",
            "-out",
            "pki/server_dil.crt",
            "-CA",
            "pki/CA_dil.crt",
            "-CAkey",
            "pki/CA_dil.key",
            "-CAcreateserial",
            "-days",
            "365",
        ]
    )


def get_host(target, virt):

    if virt == "native":
        return "localhost"
    elif virt == "docker":
        if target == "client":
            return DOCKER[0]
        elif target == "server":
            return DOCKER[1]
    elif virt == "unikraft":
        if target == "client":
            return UNIKRAFT[0]
        elif target == "server":
            return UNIKRAFT[1]

    raise Exception("Virt method not supported")

def get_openssl_bin(virt):
    return {
        "native": "Native/openssl",
        "unikraft": "Unikraft/openssl",
        "docker": "Container/openssl",
    }[virt]

def get_container_ip():
    prc = subprocess.run(
        ["docker", "network", "inspect", "alpine-bench-net"], capture_output=True
    )
    network_config_str = prc.stdout.decode()
    network_config = json.loads(network_config_str)
    host_address = network_config[0]["IPAM"]["Config"][0]["Gateway"]

    prc = subprocess.run(
        [
            "docker",
            "run",
            "--network=alpine-bench-net",
            "-it",
            "alpine-bench",
            "ifconfig",
        ],
        capture_output=True,
    )
    target_config_str = prc.stdout.decode()
    target_address = target_config_str.split("inet addr:")[1].split(" ")[0]

    return host_address, target_address


# def setup_docker(client, cypher):
#     client.container.run(
#         "pqcdocker",
#         "\
#         openssl req -x509 -new -newkey "
#         + cypher
#         + ' -keyout CA.key -out pki/CA.crt -nodes -subj "/CN=Test CA" -days 365 -config /etc/ssl/openssl.cnf && \
#         openssl req -new -newkey '
#         + cypher
#         + ' -keyout pki/server.key -out pki/server.csr -nodes -subj "/CN=testserver" -config /etc/ssl/openssl.cnf && \
#         openssl x509 -req -in pki/server.csr -out pki/server.crt -CA pki/CA.crt -CAkey CA.key -CAcreateserial -days 365 && \
#         openssl s_server -accept 443 -cert pki/server.crt -key pki/server.key -www',
#     )


# def time_docker():
#     subprocess.run(["openssl", "s_time", "-connect", HOST + ":443"])


# def test_docker():
#     # Check if the image exits
#     client = docker.from_env()
#     try:
#         client.images.get("pqcdocker")
#     except docker.errors.ImageNotFound:
#         raise docker.errors.ImageNotFound(f"Image pqcdocker does not exist.")
#     setup_docker(client, "dilithium3")


if __name__ == "__main__":
    main()
