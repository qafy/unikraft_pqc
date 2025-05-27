#!/usr/bin/env python3

# import docker
# import docker.errors
import socket
import time
import subprocess
import argparse
import json
import os
from datetime import datetime
# import signal
import matplotlib.pyplot as plt
import numpy as np


UNIKRAFT = "172.44.0.1", "172.44.0.2"
DOCKER = "host.docker.internal", "localhost"

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

    if args.newcert or not os.path.exists(os.path.join(SCRIPT_DIR, "../pki")):
        os.makedirs(os.path.join(SCRIPT_DIR, "../pki"), exist_ok=True)
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
                print("")
                prc1.wait()
                prc0.kill()

            elif args.mode == "client":
                prc0 = run_s_server("native")
                if not check_server(get_host("client", args.virt), 1):
                    print("Cannot connect to server")
                    return
                prc1 = run_s_client(args.virt)
                print("")
                prc1.wait()
                prc0.kill()

        else:
            prc0 = prc1 = None
            if args.mode == "server":
                prc0 = run_s_server(args.virt)
                prc1 = run_s_time("native")

            elif args.mode == "client":
                prc0 = run_s_server("native")
                prc1 = run_s_time(args.virt)

            print("")

            out, _ = prc1.communicate()
            lines = out.decode().splitlines()
            lines2 = out.decode().split("\n\n")[1].splitlines()[:2]
            lines3 = out.decode().split("\n\n")[2].splitlines()[1]
            print(lines[0])
            print("\n".join(lines2))
            print(lines3)
            print("\n".join(lines[-2:]))

            prc1.wait()
            prc0.kill()

            write_results(out)

    except KeyboardInterrupt:
        pass

    if args.virt == "docker":
        subprocess.run(["docker", "kill", "alpine_bench_" + os.environ.get("USER")])

    subprocess.run(["pkill", "openssl"])
    subprocess.run(["pkill", "qemu"])


def run_s_server(virt):
    openssl_version = get_openssl_bin(virt)
    cmd = [
        openssl_version,
        "s_server",
        "-key",
        "pki/server_dil.key",
        "-cert",
        "pki/server_dil.crt",
        "-accept",
        "443",
        "-www",
    ]
    print(" ".join(cmd))
    return subprocess.Popen(
        cmd,
        start_new_session=True,
        stdout=subprocess.PIPE,
    )


def run_s_client(virt):
    openssl_version = get_openssl_bin(virt)
    host = get_host("client", virt)
    cmd = [
        openssl_version,
        "s_client",
        "-connect",
        host + ":443",
        "-verifyCAfile",
        "pki/CA_dil.crt",
        "-ign_eof",
        "-nocommands",
    ]
    print(" ".join(cmd))
    return subprocess.Popen(
        cmd,
        start_new_session=True,
        stdout=subprocess.PIPE,
    )


def run_s_time(virt):
    openssl_version = get_openssl_bin(virt)
    host = get_host("client", virt)
    cmd = [
        openssl_version,
        "s_time",
        "-connect",
        host + ":443",
        "-www",
        "/",
        "-CAfile",
        "pki/CA_dil.crt",
        "-time",
        "3",
    ]
    print(" ".join(cmd))
    return subprocess.Popen(
        cmd,
        start_new_session=True,
        stdout=subprocess.PIPE,
    )


def setup_certificates(cypher):
    print("Setting up certificates")
    cmd = [
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
    print(" ".join(cmd))
    subprocess.run(cmd, stdout=subprocess.PIPE)

    cmd = [
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
    print(" ".join(cmd))
    subprocess.run(cmd, stdout=subprocess.PIPE)

    cmd = [
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
    print(" ".join(cmd))
    subprocess.run(cmd, stdout=subprocess.PIPE)
    print("Done")
    print("")


def get_host(target, virt):
    configs = {
        "native": {
            "client": "localhost",
            "server": "localhost",
        },
        "docker": {
            "client": DOCKER[0],
            "server": DOCKER[1],
        },
        "unikraft": {
            "client": UNIKRAFT[0],
            "server": UNIKRAFT[1],
        },
    }

    return configs[virt][target]


def get_openssl_bin(virt):
    return {
        "native": "Native/openssl",
        "unikraft": "Unikraft/openssl",
        "docker": "Container/openssl",
    }[virt]


def write_results(out):
    line1 = strout.lines()[0]
    line2 = "\n".join(strout.split("\n\n")[1].splitlines()[:2])
    lines3 = strout.split("\n\n")[2].splitlines()[1]

    # 
    # print(line1)
    # print(line2)
    # print(lines3)
    # print("\n".join(lines[-2:]))
    
    results_template = {
        "time": 0,
        "initial": {
            "user": {
                "connections": 0,
                "time": 0,
                "conn_p_user_sec": 0,
                "bytes_read": 0,
            },
            "real": {
                "connections": 0,
                "time": 0,
                "bytes_read": 0,
            },
        },
        "session_reuse": {
            "user": {
                "connections": 0,
                "time": 0,
                "conn_p_user_sec": 0,
                "bytes_read": 0,
            },
            "real": {
                "connections": 0,
                "time": 0,
                "bytes_read": 0,
            },
        },
    }

    with open(os.path.join(SCRIPT_DIR, "results_" + datetime.today().strftime("%Y-%m-%d_%H-%M-%S") + ".json"), "w") as f:
        json.dump(results_template, f)

    return results_template

def plot():
    # Common settings for two-column format
    FIG_WIDTH = 6.8  # inches (adjusted for two plots)
    FIG_HEIGHT = 2.5  # inches
    DPI = 300

    # Create a figure with two subplots
    fig, axs = plt.subplots(1, 2, figsize=(FIG_WIDTH, FIG_HEIGHT), dpi=DPI)

    # Example 7: Error Bars
    x = np.arange(5)
    means = np.random.rand(5) * 10
    stds = np.random.rand(5)

    # Plotting error bars
    axs[0].errorbar(x, means, yerr=stds, fmt="o-", capsize=4, color="tab:red")
    axs[0].set_xticks(x)
    axs[0].set_xticklabels(["A", "B", "C", "D", "E"])
    axs[0].set_xlabel("Category")
    axs[0].set_ylabel("Mean ± SD")
    axs[0].set_title("Error Bar Plot")

    # Define the data points for the first line
    x1 = [0, 1, 2, 3, 4, 5]
    y1 = [0, 1, 0, 1, 0, 1]

    # Define the data points for the second line
    x2 = [0, 1, 2, 3, 4, 5]
    y2 = [1, 0, 1, 0, 1, 0]

    # Create the piecewise linear graph for the first line
    axs[1].plot(x1, y1, marker="o", linestyle="-", color="b", label="Line 1")

    # Create the piecewise linear graph for the second line
    axs[1].plot(x2, y2, marker="o", linestyle="-", color="r", label="Line 2")

    # Add labels and title for the second subplot
    axs[1].set_title("Piecewise Linear Graph")
    axs[1].set_xlabel("X-axis")
    axs[1].set_ylabel("Y-axis")

    # Show grid for the second subplot
    axs[1].grid()

    # Add a legend for the second subplot
    axs[1].legend()

    # Adjust layout to prevent overlap
    plt.tight_layout()

    # Display the plot
    plt.show()
    fig.savefig("figure.pdf", bbox_inches="tight")


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


def check_server(host, timeout):
    for i in range(timeout):
        try:
            time.sleep(1)
            with socket.create_connection((host, 443), timeout=5):
                return True
        except (socket.timeout, ConnectionRefusedError):
            return False


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
