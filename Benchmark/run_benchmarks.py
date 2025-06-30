#!/usr/bin/env python3

# import docker
# import docker.errors
# import socket
import time
import subprocess
import argparse
import json
import os
from datetime import datetime

VIRT_METHODS = ["native", "docker", "unikraft"]
SIG_ALGORITHMS = [
    "SPHINCS+-SHA2-128s-simple",
    "SPHINCS+-SHA2-128f-simple",
    "Falcon-512",
    "Dilithium2",
    "Dilithium3",
    "Falcon-1024",
    "ECDSA",
    "RSA-2048",
]
KEM_ALGORITHMS = [
    "Kyber512",
    "BIKE-L1",
    "HQC-128",
    "FrodoKEM-640-AES",
    "FrodoKEM-640-SHAKE",
    "Kyber768",
    "Kyber1024",
    "ECDHE",
]
STAGES = [
    "primitives",
    "primitives_power",
    "primitives_memory",
    "tls",
    "tls_power",
    "tls_memory",
]

UNIKRAFT = "172.44.0.1", "172.44.0.2"
DOCKER = "host.docker.internal", "localhost"

SCRIPT_PATH = __file__
SCRIPT_DIR = os.path.dirname(SCRIPT_PATH)


def main():

    parser = argparse.ArgumentParser(
        description="Run benchmark suite to test oqs primitives, by default all benchmarks are executed"
    )

    parse_virt = lambda arg: parse_list(arg, VIRT_METHODS)
    parser.add_argument(
        "--virt",
        type=parse_virt,
        required=False,
        default=VIRT_METHODS,
        help=f"Specify a virtualization methods comma-separated, options: { ','.join(VIRT_METHODS) }",
    )

    parse_sig = lambda arg: parse_list(arg, SIG_ALGORITHMS)
    parser.add_argument(
        "--sig",
        type=parse_sig,
        required=False,
        default=SIG_ALGORITHMS,
        help=f"Specify a signature algorithms comma-separated, options: { ','.join(SIG_ALGORITHMS) }",
    )

    parse_kem = lambda arg: parse_list(arg, KEM_ALGORITHMS)
    parser.add_argument(
        "--kem",
        type=parse_kem,
        required=False,
        default=KEM_ALGORITHMS,
        help=f"Specify KEM algorithms comma-separated, options: {','.join(KEM_ALGORITHMS)}",
    )

    parse_stages = lambda arg: parse_list(arg, STAGES)
    parser.add_argument(
        "--stages",
        type=parse_stages,
        required=False,
        default=STAGES,
        help=f"Specify what benchmark stages run, options: {','.join(STAGES)}",
    )

    parser.add_argument(
        "--primitives_time",
        type=int,
        required=False,
        default=5,
        help="Specify the amount of time to run a primitive operation",
    )

    parser.add_argument(
        "--tls_time",
        type=int,
        required=False,
        default=30,
        help="Specify the amount of time to openssl s_speed",
    )

    args = parser.parse_args()
    global_res = {}

    try:
        if "primitives" in args.stages:
            print("Evaluating speed of primitive operations of liboqs algorithms:")

            for virt in args.virt:
                print(f"Running with virtualization method: {virt}")
                for sig in args.sig:
                    prc = run_primitive(virt, "sig", sig, args.primitives_time)
                    ret = prc.wait()
                    if ret != 0:
                        raise Exception(f"primitive sig failed with return code: {ret}")
                    res = eval_res_primitive(prc, virt, "sig", sig)
                    global_res = merge_dicts(res, global_res)

                for kem in args.kem:
                    prc = run_primitive(virt, "kem", kem, args.primitives_time)
                    ret = prc.wait()
                    if ret != 0:
                        raise Exception(f"primitive kem failed with return code: {ret}")
                    res = eval_res_primitive(prc, virt, "kem", kem)
                    global_res = merge_dicts(res, global_res)

        if "tls" in args.stages:
            print("Evaluating speed of tls handshake with liboqs algorithms:")
            pki_path = os.path.join(SCRIPT_DIR, "pki")
            os.makedirs(pki_path, exist_ok=True)

            for virt in args.virt:
                print(f"Running with virtualization method: {virt}")
                print("")
                for sig in args.sig:
                    for kem in args.kem:
                        setup_certificates(get_sig(sig))
                        print("")

                        prc0 = run_s_server("native", get_sig(sig), get_group(kem))
                        time.sleep(0.1)  # Wait for s_server to start
                        prc1 = run_s_time(virt, args.tls_time, get_sig(sig), kem)

                        ret = prc1.wait()
                        prc0.kill()

                        if ret != 0:
                            raise Exception(f"s_speed failed with return code: {ret}")

                        res = eval_res_tls(prc1, virt, sig, kem)
                        global_res = merge_dicts(res, global_res)

        if "primitives_memory" in args.stages:
            print("Evaluating memory consumption of primitive operations:")
            for virt in args.virt:
                print(f"Running with virtualization method: {virt}")
                for sig in args.sig:
                    prc = run_primitive(virt, "sig", sig, args.primitives_time)
                    time.sleep(0.1) # wait for benchmark to start
                    prc2 = run_top(prc.pid)
                    ret = prc.wait()

                    if ret != 0:
                        raise Exception(f"primitive sig failed with return code: {ret}")
                    prc2.kill()

                    res = eval_res_primitives_top(prc2, virt, "sig", sig)
                    global_res = merge_dicts(res, global_res)

                for kem in args.kem:
                    prc = run_primitive(virt, "kem", kem, args.primitives_time)
                    time.sleep(0.1) # wait for benchmark to start
                    prc2 = run_top(prc.pid)
                    ret = prc.wait()

                    if ret != 0:
                        raise Exception(f"primitive sig failed with return code: {ret}")
                    prc2.kill()

                    res = eval_res_primitives_top(prc2, virt, "kem", kem)
                    global_res = merge_dicts(res, global_res)

        if "tls_memory" in args.stages:
            print("Evaluating memory consumption of tls operations:")
            pki_path = os.path.join(SCRIPT_DIR, "pki")
            os.makedirs(pki_path, exist_ok=True)

            for virt in args.virt:
                print(f"Running with virtualization method: {virt}")
                print("")
                for sig in args.sig:
                    for kem in args.kem:
                        setup_certificates(get_sig(sig))
                        print("")

                        prc0 = run_s_server("native", get_sig(sig), get_group(kem))
                        time.sleep(0.1)  # Wait for s_server to start
                        prc1 = run_s_time(virt, args.tls_time, get_sig(sig), kem)
                        time.sleep(0.1)
                        prc2 = run_top(prc1.pid)

                        ret = prc1.wait()
                        prc0.kill()
                        prc2.kill()
                        if ret != 0:
                            raise Exception(f"s_speed failed with return code: {ret}")

                        res = eval_res_tls_top(prc2, virt, sig, kem)
                        global_res = merge_dicts(res, global_res)
                        
        if "primitives_power" in args.stages:
            print("Executing primitives for manual evaluation of power consumption:")
            for virt in args.virt:
                print(f"Running with virtualization method: {virt}")
                for sig in args.sig:
                    print("Waiting to establish baseline")
                    time.sleep(5)
                    print(f"Running {sig} keygen for {args.primitives_time} seconds")
                    prc = run_primitive(
                        virt, "sig", sig, args.primitives_time, "keygen"
                    )
                    prc.wait()
                    print("Finished")

                    print("Waiting to establish baseline")
                    time.sleep(5)
                    print(f"Running {sig} sign for {args.primitives_time} seconds")
                    prc = run_primitive(virt, "sig", sig, args.primitives_time, "sign")
                    prc.wait()
                    print("Finished")

                    print("Waiting to establish baseline")
                    time.sleep(5)
                    print(f"Running {sig} verify for {args.primitives_time} seconds")
                    prc = run_primitive(
                        virt, "sig", sig, args.primitives_time, "verify"
                    )
                    prc.wait()
                    print("Finished")

                for kem in args.kem:
                    print("Waiting to establish baseline")
                    time.sleep(5)
                    print(f"Running {kem} keygen for {args.primitives_time} seconds")
                    prc = run_primitive(
                        virt, "kem", kem, args.primitives_time, "keygen"
                    )
                    prc.wait()
                    print("Finished")

                    print("Waiting to establish baseline")
                    time.sleep(5)
                    print(f"Running {kem} encaps for {args.primitives_time} seconds")
                    prc = run_primitive(
                        virt, "kem", kem, args.primitives_time, "encaps"
                    )
                    prc.wait()
                    print("Finished")

                    print("Waiting to establish baseline")
                    time.sleep(5)
                    print(f"Running {kem} decaps for {args.primitives_time} seconds")
                    prc = run_primitive(
                        virt, "kem", kem, args.primitives_time, "decaps"
                    )
                    prc.wait()
                    print("Finished")

        if "tls_power" in args.stages:
            print("Executing primitives for manual evaluation of power consumption:")
            pki_path = os.path.join(SCRIPT_DIR, "pki")
            os.makedirs(pki_path, exist_ok=True)

            for virt in args.virt:
                print(f"Running with virtualization method: {virt}")
                print("")
                for sig in args.sig:
                    for kem in args.kem:
                        setup_certificates(get_sig(sig))
                        print("")

                        print("Waiting to establish baseline")
                        time.sleep(5)

                        print(
                            f"Running TLS handshakes with {kem}+{sig} for {args.tls_time} seconds"
                        )
                        prc0 = run_s_server("native", get_sig(sig), get_group(kem))
                        time.sleep(0.1)  # Wait for s_server to start
                        prc1 = run_s_time(virt, args.tls_time, get_sig(sig), kem)

                        ret = prc1.wait()
                        prc0.kill()

                        if ret != 0:
                            raise Exception(f"s_speed failed with return code: {ret}")

                        print("")

    except KeyboardInterrupt:
        pass
    except Exception as e:
        print(e)
    finally:
        if "docker" in args.virt:
            try:
                subprocess.run(
                    [
                        "docker",
                        "kill",
                        "alpine_bench_" + (os.environ.get("USER") or "user"),
                    ]
                )
            except Exception:
                pass

        subprocess.run(["pkill", "openssl"])
        subprocess.run(["pkill", "qemu"])

        with open(
            os.path.join(
                SCRIPT_DIR,
                "results_" + datetime.today().strftime("%Y-%m-%d_%H-%M-%S") + ".json",
            ),
            "w",
        ) as f:
            json.dump(global_res, f)


def run_primitive(virt, sig_kem, cipher, duration=1, limit_operation=None):
    additional_args = []
    if limit_operation is not None:
        additional_args += {
            "kem": {
                "keygen": ["--no_encaps", "--no_decaps"],
                "encaps": ["--no_keygen", "--no_decaps"],
                "decaps": ["--no_keygen", "--no_encaps"],
            },
            "sig": {
                "keygen": ["--no_sign", "--no_verify"],
                "sign": ["--no_keygen", "--no_verify"],
                "verify": ["--no_keygen", "--no_sign"],
            },
        }[sig_kem][limit_operation]

    test_version = get_virt_bin(virt, "benchmark")
    cmd = (
        [
            test_version,
            sig_kem,
        ]
        + additional_args
        + [
            "-d",
            str(duration),
            cipher,
        ]
    )
    print(" ".join(cmd))
    prc = subprocess.Popen(
        cmd,
        start_new_session=True,
        stdout=subprocess.PIPE,
    )
    return prc


def run_s_server(virt, sig, kem):
    openssl_version = get_virt_bin(virt, "openssl")
    if virt == "unikraft":
        dir_key = f"Benchmark/pki/server_{sig}.key"
        dir_crt = f"Benchmark/pki/server_{sig}.crt"
    else:
        dir_key = os.path.join(SCRIPT_DIR, f"pki/server_{sig}.key")
        dir_crt = os.path.join(SCRIPT_DIR, f"pki/server_{sig}.crt")
    cmd = [
        openssl_version,
        "s_server",
        "-key",
        dir_key,
        "-cert",
        dir_crt,
        "-groups",
        kem,
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


def run_s_client(virt, sig, kem):
    openssl_version = get_virt_bin(virt, "openssl")
    host = get_host("client", virt)
    if virt == "unikraft":
        ca_crt = f"Benchmark/pki/CA_{sig}.crt"
    else:
        ca_crt = os.path.join(SCRIPT_DIR, f"pki/CA_{sig}.crt")
    cmd = [
        openssl_version,
        "s_client",
        "-connect",
        host + ":443",
        "-groups",
        kem,
        "-verifyCAfile",
        ca_crt,
        "-ign_eof",
        "-nocommands",
    ]
    print(" ".join(cmd))
    return subprocess.Popen(
        cmd,
        start_new_session=True,
        stdout=subprocess.PIPE,
    )


def run_s_time(virt, time, sig, kem):
    openssl_version = get_virt_bin(virt, "openssl")
    host = get_host("client", virt)
    if virt == "unikraft":
        ca_crt = f"Benchmark/pki/CA_{sig}.crt"
    else:
        ca_crt = os.path.join(SCRIPT_DIR, f"pki/CA_{sig}.crt")
    cmd = [
        openssl_version,
        "s_time",
        "-connect",
        host + ":443",
        "-www",
        "/",
        "-CAfile",
        ca_crt,
        "-time",
        str(time),
    ]
    print(" ".join(cmd))
    return subprocess.Popen(
        cmd,
        start_new_session=True,
        stdout=subprocess.PIPE,
    )


def run_top(pid):
    cmd = [
        "top",
        "-b",
        "-p",
        str(pid),
        "-d",
        "0.5",
    ]
    print(" ".join(cmd))
    return subprocess.Popen(
        cmd,
        start_new_session=True,
        stdout=subprocess.PIPE,
    )


def setup_certificates(sig):
    print(f"Setting up certificates for signature algorithm {sig}")
    ca_key = os.path.join(SCRIPT_DIR, f"pki/CA_{sig}.key")
    ca_crt = os.path.join(SCRIPT_DIR, f"pki/CA_{sig}.crt")
    dir_key = os.path.join(SCRIPT_DIR, f"pki/server_{sig}.key")
    dir_crt = os.path.join(SCRIPT_DIR, f"pki/server_{sig}.crt")
    dir_crs = os.path.join(SCRIPT_DIR, f"pki/server_{sig}.crs")

    ca_key_src = []
    dir_key_src = []
    if sig == "RSA-2048":
        cmd = [get_virt_bin("native", "openssl"), "genrsa", "-out", ca_key, "2048"]
        print(" ".join(cmd))
        prc = subprocess.run(cmd, stdout=subprocess.PIPE)
        if prc.returncode != 0:
            raise Exception(f"genrsa failed with return code: {prc.returncode}")

        cmd = [get_virt_bin("native", "openssl"), "genrsa", "-out", dir_key, "2048"]
        print(" ".join(cmd))
        prc = subprocess.run(cmd, stdout=subprocess.PIPE)
        if prc.returncode != 0:
            raise Exception(f"genrsa failed with return code: {prc.returncode}")

        ca_key_src = ["-key", ca_key]
        dir_key_src = ["-key", dir_key]

    elif sig == "ECDSA":
        cmd = [
            get_virt_bin("native", "openssl"),
            "ecparam",
            "-genkey",
            "-name",
            "secp256r1",
            "-out",
            ca_key,
        ]
        print(" ".join(cmd))
        prc = subprocess.run(cmd, stdout=subprocess.PIPE)
        if prc.returncode != 0:
            raise Exception(f"ecparam failed with return code: {prc.returncode}")

        cmd = [
            get_virt_bin("native", "openssl"),
            "ecparam",
            "-genkey",
            "-name",
            "secp256r1",
            "-out",
            dir_key,
        ]
        print(" ".join(cmd))
        prc = subprocess.run(cmd, stdout=subprocess.PIPE)
        if prc.returncode != 0:
            raise Exception(f"ecparam failed with return code: {prc.returncode}")

        ca_key_src = ["-key", ca_key]
        dir_key_src = ["-key", dir_key]

    else:
        ca_key_src = [
            "-newkey",
            sig,
            "-keyout",
            ca_key,
        ]

        dir_key_src = [
            "-newkey",
            sig,
            "-keyout",
            dir_key,
        ]

    cmd = [
        get_virt_bin("native", "openssl"),
        "req",
        "-x509",
        "-new",
        "-out",
        ca_crt,
        "-nodes",
        "-subj",
        "/CN=Test CA",
        "-days",
        "365",
    ] + ca_key_src
    print(" ".join(cmd))
    prc = subprocess.run(cmd, stdout=subprocess.PIPE)
    if prc.returncode != 0:
        raise Exception(f"req failed with return code: {prc.returncode}")

    cmd = [
        get_virt_bin("native", "openssl"),
        "req",
        "-new",
        "-out",
        dir_crs,
        "-nodes",
        "-subj",
        "/CN=testserver",
    ] + dir_key_src
    print(" ".join(cmd))
    prc = subprocess.run(cmd, stdout=subprocess.PIPE)
    if prc.returncode != 0:
        raise Exception(f"req failed with return code: {prc.returncode}")

    cmd = [
        get_virt_bin("native", "openssl"),
        "x509",
        "-req",
        "-in",
        dir_crs,
        "-out",
        dir_crt,
        "-CA",
        ca_crt,
        "-CAkey",
        ca_key,
        "-CAcreateserial",
        "-days",
        "365",
    ]
    print(" ".join(cmd))
    prc = subprocess.run(cmd, stdout=subprocess.PIPE)
    if prc.returncode != 0:
        raise Exception(f"x509 failed with return code: {prc.returncode}")


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


def get_group(kem):
    # https://github.com/open-quantum-safe/oqs-provider/blob/main/ALGORITHMS.md
    return {
        "Kyber512": "kyber512",
        "BIKE-L1": "bikel1",
        "HQC-128": "hqc128",
        "FrodoKEM-640-AES": "frodo640aes",
        "FrodoKEM-640-SHAKE": "frodo640shake",
        "Kyber768": "kyber768",
        "Kyber1024": "kyber1024",
        "ECDHE": "secp256r1",
    }[kem]


def get_sig(sig):
    return {
        "SPHINCS+-SHA2-128s-simple": "sphincssha2128ssimple",
        "SPHINCS+-SHA2-128f-simple": "sphincssha2128fsimple",
        "Falcon-512": "falcon512",
        "Dilithium2": "Dilithium2",
        "Dilithium3": "Dilithium3",
        "Falcon-1024": "falcon1024",
        "RSA-2048": "RSA-2048",
        "ECDSA": "ECDSA",
    }[sig]


def get_virt_bin(virt, app):
    return {
        "native": os.path.join(SCRIPT_DIR, "..", "Native", app),
        "unikraft": os.path.join(SCRIPT_DIR, "..", "Unikraft", app),
        "docker": os.path.join(SCRIPT_DIR, "..", "Container", app),
    }[virt]


def eval_res_primitive(prc, virt, sig_kem, cipher):
    out, _ = prc.communicate()
    print(out.decode())

    lines = out.decode().splitlines()
    res = {
        "primitive": {
            virt: {
                sig_kem: {
                    cipher: {
                        "keygen": {
                            "iterations": float(lines[6].split("|")[1].strip()),
                            "total_time": float(lines[6].split("|")[2].strip()),
                            "mean_us": float(lines[6].split("|")[3].strip()),
                            "stddev_us": float(lines[6].split("|")[4].strip()),
                            "mean_ns": float(lines[6].split("|")[5].strip()),
                            "stddev_ns": float(lines[6].split("|")[6].strip()),
                        },
                        "encaps": {
                            "iterations": float(lines[7].split("|")[1].strip()),
                            "total_time": float(lines[7].split("|")[2].strip()),
                            "mean_us": float(lines[7].split("|")[3].strip()),
                            "stddev_us": float(lines[7].split("|")[4].strip()),
                            "mean_ns": float(lines[7].split("|")[5].strip()),
                            "stddev_ns": float(lines[7].split("|")[6].strip()),
                        },
                        "decaps": {
                            "iterations": float(lines[8].split("|")[1].strip()),
                            "total_time": float(lines[8].split("|")[2].strip()),
                            "mean_us": float(lines[8].split("|")[3].strip()),
                            "stddev_us": float(lines[8].split("|")[4].strip()),
                            "mean_ns": float(lines[8].split("|")[5].strip()),
                            "stddev_ns": float(lines[8].split("|")[6].strip()),
                        },
                    }
                }
            }
        }
    }
    return res


def eval_res_tls(prc, virt, sig, kem):
    out, _ = prc.communicate()

    out_str = out.decode().replace("\r\n", "\n")
    lines = out_str.splitlines()
    segments = out_str.split("\n\n")

    print(lines[0])
    print("\n".join(segments[1].splitlines()[:2]))
    print(segments[2].splitlines()[1])
    print("\n".join(lines[-2:]))

    line1 = lines[0]
    line2 = segments[1].splitlines()[0]
    line3 = segments[1].splitlines()[1]
    line4 = lines[-2]
    line5 = lines[-1]

    res = {
        "tls": {
            virt: {
                f"{sig}+{kem}": {
                    "time": float(line1.split(" ")[4]),
                    "initial": {
                        "user": {
                            "connections": float(line2.split(" ")[0]),
                            "time": float(line2.split(" ")[3][:-2]),
                            "conn_p_user_sec": float(line2.split(" ")[4]),
                            "bytes_read": float(line2.split(" ")[9]),
                        },
                        "real": {
                            "connections": float(line3.split(" ")[0]),
                            "time": float(line3.split(" ")[3]),
                            "bytes_read": float(line3.split(" ")[6]),
                        },
                    },
                    "session_reuse": {
                        "user": {
                            "connections": float(line4.split(" ")[0]),
                            "time": float(line4.split(" ")[3][:-2]),
                            "conn_p_user_sec": float(line4.split(" ")[4]),
                            "bytes_read": float(line4.split(" ")[9]),
                        },
                        "real": {
                            "connections": float(line5.split(" ")[0]),
                            "time": float(line5.split(" ")[3]),
                            "bytes_read": float(line5.split(" ")[6]),
                        },
                    },
                }
            }
        }
    }
    return res


def eval_res_primitives_top(prc, virt, sig_kem, cipher):
    res_obj = eval_res_top(prc)
    print(res_obj)
    return {"primitive": {virt: {sig_kem: {cipher: {"memory": res_obj}}}}}


def eval_res_tls_top(prc, virt, sig, kem):
    res_obj = eval_res_top(prc)
    print(res_obj)
    return {"tls": {virt: {f"{sig}+{kem}": {"memory": res_obj}}}}


def eval_res_top(prc):
    def second(list):
        res = []
        i = 0
        for l in list:
            if i % 2 == 0:
                res.append(l)
            i += 1
        return res

    out, _ = prc.communicate()
    out_str = out.decode()
    segments = second(out_str.split("\n\n"))
    total_memory = (
        segments[0]
        .splitlines()[3]
        .split(",")[0]
        .split(":")[1]
        .strip()
        .split(" ")[0]
        .strip()
    )

    return {
        "total_mib": total_memory,
        "free_mib": [
            x.splitlines()[3].split(",")[1].strip().split(" ")[0].strip()
            for x in segments
        ],
        "used_mib": [
            x.splitlines()[3].split(",")[2].strip().split(" ")[0].strip()
            for x in segments
        ],
    }


def parse_list(arglist, constraint):
    # Split the string by commas
    args = arglist.split(",")
    # Check if each drive is in the valid choices
    for arg in args:
        if arg not in constraint:
            raise argparse.ArgumentTypeError(
                f"Invalid drive: {arg}. Must be one of {constraint}."
            )
    return args


def merge_dicts(dictl, dictr):
    for key, value in dictl.items():
        if key in dictr and isinstance(dictr[key], dict) and isinstance(value, dict):
            merge_dicts(value, dictr[key])
        else:
            dictr[key] = value
    return dictr


# def get_container_ip():
#     prc = subprocess.run(
#         ["docker", "network", "inspect", "alpine-bench-net"], capture_output=True
#     )
#     network_config_str = prc.stdout.decode()
#     network_config = json.loads(network_config_str)
#     host_address = network_config[0]["IPAM"]["Config"][0]["Gateway"]
#
#     prc = subprocess.run(
#         [
#             "docker",
#             "run",
#             "--network=alpine-bench-net",
#             "-it",
#             "alpine-bench",
#             "ifconfig",
#         ],
#         capture_output=True,
#     )
#     target_config_str = prc.stdout.decode()
#     target_address = target_config_str.split("inet addr:")[1].split(" ")[0]
#
#     return host_address, target_address


# def check_server(host, timeout):
#     for i in range(timeout):
#         try:
#             time.sleep(1)
#             with socket.create_connection((host, 443), timeout=5):
#                 return True
#         except (socket.timeout, ConnectionRefusedError):
#             return False


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
