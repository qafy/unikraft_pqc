#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import os
import json
import matplotlib
from matplotlib.gridspec import GridSpec

SCRIPT_PATH = __file__
SCRIPT_DIR = os.path.dirname(SCRIPT_PATH)


def main():
    # plot_table_primitives()
    # plot_table_tls()
    # plot_bar_tls_speed()
    # plot_bar_tls_power()
    # plot_bar_tls_energy()
    plot_bar_primitives_speed()



def plot_table_primitives():

    sigs = [
    "SPHINCS+-SHA2-128s-simple",
    "SPHINCS+-SHA2-128f-simple",
    "Falcon-512",
    "Dilithium2",
    "Dilithium3",
    "Falcon-1024",
    "ECDSA",
    "RSA-2048",
    ]
    kems = [
        "Kyber512",
        "BIKE-L1",
        "HQC-128",
        "FrodoKEM-640-AES",
        "FrodoKEM-640-SHAKE",
        "Kyber768",
        "Kyber1024",
        "ECDHE",
    ]

    # Time
    with open(os.path.join(SCRIPT_DIR, "results/primitives_speed.json"), "r") as f:
        data = json.load(f)["primitive"]
    
    fig = plt.figure(figsize=(12, 6))
    height = len(sigs) + len(kems) + 2
    gs = GridSpec(height, 12, figure=fig, wspace=0.0, hspace=0.0, height_ratios=[1 for _ in range(height - 1)]+ [4])

    ax_cipher = fig.add_subplot(gs[1, 0:3])
    ax_cipher.text(0.5, 0.5, "KEMs", va="center", ha="center")
    ax_time = fig.add_subplot(gs[0, 3:6])
    ax_time.text(0.5, 0.5, "Keygen (us)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[0, 6:9])
    ax_power.text(0.5, 0.5, "Encapsulate (us)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[0, 9:12])
    ax_energy.text(0.5, 0.5, "Decapsulate (us)", va="center", ha="center")

    ax_cipher = fig.add_subplot(gs[len(kems) + 3, 0:3])
    ax_cipher.text(0.5, 0.5, "SIGs", va="center", ha="center")
    ax_time = fig.add_subplot(gs[len(kems) + 2, 3:6])
    ax_time.text(0.5, 0.5, "Keygen (us)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[len(kems) + 2, 6:9])
    ax_power.text(0.5, 0.5, "Sign (us)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[len(kems) + 2, 9:12])
    ax_energy.text(0.5, 0.5, "Verify (us)", va="center", ha="center")
    
    ax_nt1 = fig.add_subplot(gs[1, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[1, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[1, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    ax_nt1 = fig.add_subplot(gs[len(kems) + 3, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[len(kems) + 3, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[len(kems) + 3, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    ax_uk1 = fig.add_subplot(gs[1, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[1, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[1, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    ax_uk1 = fig.add_subplot(gs[len(kems) + 3, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[len(kems) + 3, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[len(kems) + 3, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    ax_cnt1 = fig.add_subplot(gs[1, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[1, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[1, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    ax_cnt1 = fig.add_subplot(gs[len(kems) + 3, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[len(kems) + 3, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[len(kems) + 3, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    categories_table = [[x] for x in kems]
    ax_cipher = fig.add_subplot(gs[2:len(kems) + 2, 0:3])
    ax_cipher.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])
    
    categories_table = [[x] for x in sigs]
    ax_cipher = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 0:3])
    
    
    ax_cipher.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])

    nt_times = [[data["native"]["kem"][x]["keygen"]["mean_us"]] for x in kems]
    ax1_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 3])
    ax1_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["kem"][x]["encaps"]["mean_us"]] for x in kems]
    ax2_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 6])
    ax2_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["kem"][x]["decaps"]["mean_us"]] if x != "ECDHE" else "-" for x in kems]
    ax3_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 9])
    ax3_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["sig"][x]["keygen"]["mean_us"]] for x in sigs]
    ax1_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 3])
    ax1_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["sig"][x]["encaps"]["mean_us"]] for x in sigs]
    ax2_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 6])
    ax2_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["sig"][x]["decaps"]["mean_us"]] for x in sigs]
    ax3_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 9])
    ax3_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["kem"][x]["keygen"]["mean_us"]] for x in kems]
    ax1_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 4])
    ax1_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["kem"][x]["encaps"]["mean_us"]] for x in kems]
    ax2_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 7])
    ax2_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["kem"][x]["decaps"]["mean_us"]] if x != "ECDHE" else "-" for x in kems]
    ax3_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 10])
    ax3_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["sig"][x]["keygen"]["mean_us"]] for x in sigs]
    ax1_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 4])
    ax1_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["sig"][x]["encaps"]["mean_us"]] for x in sigs]
    ax2_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 7])
    ax2_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["sig"][x]["decaps"]["mean_us"]] for x in sigs]
    ax3_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 10])
    ax3_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["kem"][x]["keygen"]["mean_us"]] for x in kems]
    ax1_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 5])
    ax1_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["kem"][x]["encaps"]["mean_us"]] for x in kems]
    ax2_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 8])
    ax2_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["kem"][x]["decaps"]["mean_us"]] if x != "ECDHE" else "-" for x in kems]
    ax3_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 11])
    ax3_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["sig"][x]["keygen"]["mean_us"]] for x in sigs]
    ax1_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 5])
    ax1_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["sig"][x]["encaps"]["mean_us"]] for x in sigs]
    ax2_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 8])
    ax2_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["sig"][x]["decaps"]["mean_us"]] for x in sigs]
    ax3_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 11])
    ax3_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    format_axes(fig)
    #fig.text(0.5, 0.01, 'Table 1: Time (us) of Traditional and Post-quantum Primitives.', ha='center')
    plt.savefig("table_primitives_speed.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()

    # Memory
    with open(os.path.join(SCRIPT_DIR, "results/primitives_memory.json"), "r") as f:
        data_mem = json.load(f)["primitive"]
        
    fig = plt.figure(figsize=(12, 6))
    height = len(sigs) + len(kems) + 2
    gs = GridSpec(height, 12, figure=fig, wspace=0.0, hspace=0.0, height_ratios=[1 for _ in range(height - 1)]+ [4])

    ax_cipher = fig.add_subplot(gs[1, 0:3])
    ax_cipher.text(0.5, 0.5, "KEMs", va="center", ha="center")
    ax_time = fig.add_subplot(gs[0, 3:6])
    ax_time.text(0.5, 0.5, "Keygen (KiB)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[0, 6:9])
    ax_power.text(0.5, 0.5, "Encapsulate (KiB)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[0, 9:12])
    ax_energy.text(0.5, 0.5, "Decapsulate (KiB)", va="center", ha="center")

    ax_cipher = fig.add_subplot(gs[len(kems) + 3, 0:3])
    ax_cipher.text(0.5, 0.5, "SIGs", va="center", ha="center")
    ax_time = fig.add_subplot(gs[len(kems) + 2, 3:6])
    ax_time.text(0.5, 0.5, "Keygen (KiB)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[len(kems) + 2, 6:9])
    ax_power.text(0.5, 0.5, "Sign (KiB)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[len(kems) + 2, 9:12])
    ax_energy.text(0.5, 0.5, "Verify (KiB)", va="center", ha="center")
    
    ax_nt1 = fig.add_subplot(gs[1, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[1, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[1, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    ax_nt1 = fig.add_subplot(gs[len(kems) + 3, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[len(kems) + 3, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[len(kems) + 3, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    ax_uk1 = fig.add_subplot(gs[1, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[1, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[1, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    ax_uk1 = fig.add_subplot(gs[len(kems) + 3, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[len(kems) + 3, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[len(kems) + 3, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    ax_cnt1 = fig.add_subplot(gs[1, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[1, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[1, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    ax_cnt1 = fig.add_subplot(gs[len(kems) + 3, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[len(kems) + 3, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[len(kems) + 3, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    categories_table = [[x] for x in kems]
    ax_cipher = fig.add_subplot(gs[2:len(kems) + 2, 0:3])
    ax_cipher.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])
    
    categories_table = [[x] for x in sigs]
    ax_cipher = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 0:3])
    
    ax_cipher.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])

    array_list = [[float(x)for x in data_mem["native"]["kem"][x]["keygen"]["memory"]["res_used_kib"]] for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax1_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 3])
    ax1_nt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["native"]["kem"][x]["encaps"]["memory"]["res_used_kib"]] for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax2_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 6])
    ax2_nt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x) for x in data_mem["native"]["kem"][x]["decaps"]["memory"]["res_used_kib"]] if x != "ECDHE" else "-" for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] if x != "-" else "-" for x in array_list]
    ax3_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 9])
    ax3_nt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["native"]["sig"][x]["keygen"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax1_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 3])
    ax1_nt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["native"]["sig"][x]["encaps"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax2_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 6])
    ax2_nt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["native"]["sig"][x]["decaps"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax3_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 9])
    ax3_nt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["unikraft"]["kem"][x]["keygen"]["memory"]["res_used_kib"]] for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax1_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 4])
    ax1_uk_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["unikraft"]["kem"][x]["encaps"]["memory"]["res_used_kib"]] for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax2_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 7])
    ax2_uk_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["unikraft"]["kem"][x]["decaps"]["memory"]["res_used_kib"]] if x != "ECDHE" else "-" for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] if x != "-" else "-" for x in array_list]
    ax3_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 10])
    ax3_uk_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["unikraft"]["sig"][x]["keygen"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax1_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 4])
    ax1_uk_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["unikraft"]["sig"][x]["encaps"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax2_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 7])
    ax2_uk_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["unikraft"]["sig"][x]["decaps"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax3_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 10])
    ax3_uk_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["docker"]["kem"][x]["keygen"]["memory"]["res_used_kib"]] for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax1_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 5])
    ax1_cnt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["docker"]["kem"][x]["encaps"]["memory"]["res_used_kib"]] for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax2_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 8])
    ax2_cnt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["docker"]["kem"][x]["decaps"]["memory"]["res_used_kib"]] if x != "ECDHE" else "-" for x in kems]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] if x != "-" else "-"  for x in array_list]
    ax3_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 11])
    ax3_cnt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["docker"]["sig"][x]["keygen"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax1_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 5])
    ax1_cnt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["docker"]["sig"][x]["encaps"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax2_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 8])
    ax2_cnt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["docker"]["sig"][x]["decaps"]["memory"]["res_used_kib"]] for x in sigs]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax3_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 11])
    ax3_cnt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    format_axes(fig)
    #fig.text(0.5, 0.01, 'Table 2: Memory (KiB) of Traditional and Post-quantum Primitives.', ha='center')
    plt.savefig("table_primitives_memory.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()
    
    
    # Power
    with open(os.path.join(SCRIPT_DIR, "results/primitives_power.json"), "r") as f:
        data = json.load(f)

    
    fig = plt.figure(figsize=(12, 6))
    height = len(sigs) + len(kems) + 2
    gs = GridSpec(height, 12, figure=fig, wspace=0.0, hspace=0.0, height_ratios=[1 for _ in range(height - 1)]+ [4])

    ax_cipher = fig.add_subplot(gs[1, 0:3])
    ax_cipher.text(0.5, 0.5, "KEMs", va="center", ha="center")
    ax_time = fig.add_subplot(gs[0, 3:6])
    ax_time.text(0.5, 0.5, "Keygen (mW)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[0, 6:9])
    ax_power.text(0.5, 0.5, "Encapsulate (mW)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[0, 9:12])
    ax_energy.text(0.5, 0.5, "Decapsulate (mW)", va="center", ha="center")

    ax_cipher = fig.add_subplot(gs[len(kems) + 3, 0:3])
    ax_cipher.text(0.5, 0.5, "SIGs", va="center", ha="center")
    ax_time = fig.add_subplot(gs[len(kems) + 2, 3:6])
    ax_time.text(0.5, 0.5, "Keygen (mW)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[len(kems) + 2, 6:9])
    ax_power.text(0.5, 0.5, "Sign (mW)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[len(kems) + 2, 9:12])
    ax_energy.text(0.5, 0.5, "Verify (mW)", va="center", ha="center")
    
    ax_nt1 = fig.add_subplot(gs[1, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[1, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[1, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    ax_nt1 = fig.add_subplot(gs[len(kems) + 3, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[len(kems) + 3, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[len(kems) + 3, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    ax_uk1 = fig.add_subplot(gs[1, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[1, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[1, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    ax_uk1 = fig.add_subplot(gs[len(kems) + 3, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[len(kems) + 3, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[len(kems) + 3, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    ax_cnt1 = fig.add_subplot(gs[1, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[1, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[1, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    ax_cnt1 = fig.add_subplot(gs[len(kems) + 3, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[len(kems) + 3, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[len(kems) + 3, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    categories_table = [[x] for x in kems]
    ax_cipher = fig.add_subplot(gs[2:len(kems) + 2, 0:3])
    ax_cipher.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])
    
    categories_table = [[x] for x in sigs]
    ax_cipher = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 0:3])
    
    
    ax_cipher.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])

    nt_times = [[data["native"]["kem"][x]["keygen"]["mean_mw"]] for x in kems]
    ax1_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 3])
    ax1_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["kem"][x]["encaps"]["mean_mw"]] for x in kems]
    ax2_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 6])
    ax2_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["kem"][x]["decaps"]["mean_mw"]] if x != "ECDHE" else "-" for x in kems]
    ax3_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 9])
    ax3_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["sig"][x]["keygen"]["mean_mw"]] for x in sigs]
    ax1_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 3])
    ax1_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["sig"][x]["encaps"]["mean_mw"]] for x in sigs]
    ax2_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 6])
    ax2_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[data["native"]["sig"][x]["decaps"]["mean_mw"]] for x in sigs]
    ax3_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 9])
    ax3_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["kem"][x]["keygen"]["mean_mw"]] for x in kems]
    ax1_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 4])
    ax1_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["kem"][x]["encaps"]["mean_mw"]] for x in kems]
    ax2_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 7])
    ax2_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["kem"][x]["decaps"]["mean_mw"]] if x != "ECDHE" else "-" for x in kems]
    ax3_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 10])
    ax3_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["sig"][x]["keygen"]["mean_mw"]] for x in sigs]
    ax1_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 4])
    ax1_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["sig"][x]["encaps"]["mean_mw"]] for x in sigs]
    ax2_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 7])
    ax2_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[data["unikraft"]["sig"][x]["decaps"]["mean_mw"]] for x in sigs]
    ax3_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 10])
    ax3_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["kem"][x]["keygen"]["mean_mw"]] for x in kems]
    ax1_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 5])
    ax1_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["kem"][x]["encaps"]["mean_mw"]] for x in kems]
    ax2_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 8])
    ax2_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["kem"][x]["decaps"]["mean_mw"]] if x != "ECDHE" else "-" for x in kems]
    ax3_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 11])
    ax3_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["sig"][x]["keygen"]["mean_mw"]] for x in sigs]
    ax1_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 5])
    ax1_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["sig"][x]["encaps"]["mean_mw"]] for x in sigs]
    ax2_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 8])
    ax2_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[data["docker"]["sig"][x]["decaps"]["mean_mw"]] for x in sigs]
    ax3_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 11])
    ax3_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    format_axes(fig)
    #fig.text(0.5, 0.01, 'Table 3: Power Consumption (mW) of Traditional and Post-quantum Primitives.', ha='center')
    plt.savefig("table_primitives_power.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()
    
    # Energy
    fig = plt.figure(figsize=(12, 6))
    height = len(sigs) + len(kems) + 2
    gs = GridSpec(height, 12, figure=fig, wspace=0.0, hspace=0.0, height_ratios=[1 for _ in range(height - 1)]+ [4])

    ax_cipher = fig.add_subplot(gs[1, 0:3])
    ax_cipher.text(0.5, 0.5, "KEMs", va="center", ha="center")
    ax_time = fig.add_subplot(gs[0, 3:6])
    ax_time.text(0.5, 0.5, "Keygen (J)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[0, 6:9])
    ax_power.text(0.5, 0.5, "Encapsulate (J)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[0, 9:12])
    ax_energy.text(0.5, 0.5, "Decapsulate (J)", va="center", ha="center")

    ax_cipher = fig.add_subplot(gs[len(kems) + 3, 0:3])
    ax_cipher.text(0.5, 0.5, "SIGs", va="center", ha="center")
    ax_time = fig.add_subplot(gs[len(kems) + 2, 3:6])
    ax_time.text(0.5, 0.5, "Keygen (J)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[len(kems) + 2, 6:9])
    ax_power.text(0.5, 0.5, "Sign (J)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[len(kems) + 2, 9:12])
    ax_energy.text(0.5, 0.5, "Verify (mW)", va="center", ha="center")
    
    ax_nt1 = fig.add_subplot(gs[1, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[1, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[1, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    ax_nt1 = fig.add_subplot(gs[len(kems) + 3, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[len(kems) + 3, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[len(kems) + 3, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    ax_uk1 = fig.add_subplot(gs[1, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[1, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[1, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    ax_uk1 = fig.add_subplot(gs[len(kems) + 3, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[len(kems) + 3, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[len(kems) + 3, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    ax_cnt1 = fig.add_subplot(gs[1, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[1, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[1, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    ax_cnt1 = fig.add_subplot(gs[len(kems) + 3, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[len(kems) + 3, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[len(kems) + 3, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    categories_table = [[x] for x in kems]
    ax_cipher = fig.add_subplot(gs[2:len(kems) + 2, 0:3])
    ax_cipher.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])
    
    categories_table = [[x] for x in sigs]
    ax_cipher = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 0:3])
    
    
    ax_cipher.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])

    nt_times = [[f'{float(data["native"]["kem"][x]["keygen"]["mean_mj"]) / 1000:.3f}'] for x in kems]
    ax1_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 3])
    ax1_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[f'{float(data["native"]["kem"][x]["encaps"]["mean_mj"]) / 1000:.3f}'] for x in kems]
    ax2_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 6])
    ax2_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[f'{float(data["native"]["kem"][x]["decaps"]["mean_mj"]) / 1000:.3f}'] if x != "ECDHE" else "-" for x in kems]
    ax3_nt_table = fig.add_subplot(gs[2:len(kems) + 2, 9])
    ax3_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[f'{float(data["native"]["sig"][x]["keygen"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax1_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 3])
    ax1_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[f'{float(data["native"]["sig"][x]["encaps"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax2_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 6])
    ax2_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_times = [[f'{float(data["native"]["sig"][x]["decaps"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax3_nt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 9])
    ax3_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[f'{float(data["unikraft"]["kem"][x]["keygen"]["mean_mj"]) / 1000:.3f}'] for x in kems]
    ax1_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 4])
    ax1_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[f'{float(data["unikraft"]["kem"][x]["encaps"]["mean_mj"]) / 1000:.3f}'] for x in kems]
    ax2_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 7])
    ax2_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[f'{float(data["unikraft"]["kem"][x]["decaps"]["mean_mj"]) / 1000:.3f}'] if x != "ECDHE" else "-"  for x in kems]
    ax3_uk_table = fig.add_subplot(gs[2:len(kems) + 2, 10])
    ax3_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[f'{float(data["unikraft"]["sig"][x]["keygen"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax1_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 4])
    ax1_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[f'{float(data["unikraft"]["sig"][x]["encaps"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax2_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 7])
    ax2_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_times = [[f'{float(data["unikraft"]["sig"][x]["decaps"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax3_uk_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 10])
    ax3_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[f'{float(data["docker"]["kem"][x]["keygen"]["mean_mj"]) / 1000:.3f}'] for x in kems]
    ax1_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 5])
    ax1_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[f'{float(data["docker"]["kem"][x]["encaps"]["mean_mj"]) / 1000:.3f}'] for x in kems]
    ax2_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 8])
    ax2_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[f'{float(data["docker"]["kem"][x]["decaps"]["mean_mj"]) / 1000:.3f}'] if x != "ECDHE" else "-" for x in kems]
    ax3_cnt_table = fig.add_subplot(gs[2:len(kems) + 2, 11])
    ax3_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[f'{float(data["docker"]["sig"][x]["keygen"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax1_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 5])
    ax1_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[f'{float(data["docker"]["sig"][x]["encaps"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax2_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 8])
    ax2_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_times = [[f'{float(data["docker"]["sig"][x]["decaps"]["mean_mj"]) / 1000:.3f}'] for x in sigs]
    ax3_cnt_table = fig.add_subplot(gs[len(kems) + 4:len(kems) + 4 + len(sigs), 11])
    ax3_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    format_axes(fig)
    #fig.text(0.5, 0.01, 'Table 3: Energy Consumption (J) of Traditional and Post-quantum Primitives.', ha='center')
    plt.savefig("table_primitives_energy.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show() 


def plot_table_tls():
    with open(os.path.join(SCRIPT_DIR, "results/tls_speed.json"), "r") as f:
        data = json.load(f)["tls"]

    with open(os.path.join(SCRIPT_DIR, "results/tls_memory.json"), "r") as f:
        data_mem = json.load(f)["tls"]
        
    with open(os.path.join(SCRIPT_DIR, "results/tls_power.json"), "r") as f:
        data_power = json.load(f)

    # Data
    categories = [
    "Dilithium2+Kyber512",
    "Falcon-512+Kyber512",
    "Dilithium3+Kyber768",
    "Falcon-1024+Kyber768",
    "Dilithium3+Kyber1024",
    "Falcon-1024+Kyber1024",
    "SPHINCS+-SHA2-128s-simple+Kyber512",
    "Dilithium2+BIKE-L1",
    "Dilithium2+HQC-128",
    "Dilithium2+FrodoKEM-640-AES",
    "Dilithium2+FrodoKEM-640-SHAKE",
    "RSA-2048+ECDHE",
    "ECDSA+ECDHE"
    ]
    
    categories_shortened = [
    "Dil2+Kyb5",
    "Fal5+Kyb5",
    "Dil3+Kyb7",
    "Fal10+Kyb7",
    "Dil3+Kyb10",
    "Fal10+Kyb10",
    "SPHIs+Kyb5",
    "Dil2+BIKE",
    "Dil2+HQC",
    "Dil2+FrodAES",
    "Dil2+FrodSHAKE",
    "RSA+ECDHE",
    "ECDSA+ECDHE"
    ]

    fig = plt.figure(figsize=(12, 5))
    height = len(categories) + 2
    gs = GridSpec(height, 15, figure=fig, wspace=0.0, hspace=0.0, height_ratios=[1 for _ in range(height - 1)]+ [4])

    ax_cipher = fig.add_subplot(gs[1, 0:3])
    ax_cipher.text(0.5, 0.5, "Cipher", va="center", ha="center")
    ax_time = fig.add_subplot(gs[0, 3:6])
    ax_time.text(0.5, 0.5, "Conn. (1/30s)", va="center", ha="center")
    ax_power = fig.add_subplot(gs[0, 6:9])
    ax_power.text(0.5, 0.5, "Power (W)", va="center", ha="center")
    ax_energy = fig.add_subplot(gs[0, 9:12])
    ax_energy.text(0.5, 0.5, "Energy (J)", va="center", ha="center")
    ax_mem = fig.add_subplot(gs[0, 12:15])
    ax_mem.text(0.5, 0.5, "Memory (MiB)", va="center", ha="center")
    
    categories_table = [[x] for x in categories_shortened]
    ax_ciphers = fig.add_subplot(gs[2:, 0:3])
    ax_ciphers.table(cellText=categories_table, cellLoc="center", bbox=[0, 0, 1, 1])
    
    ax_nt1 = fig.add_subplot(gs[1, 3])
    ax_nt1.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt2 = fig.add_subplot(gs[1, 6])
    ax_nt2.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt3 = fig.add_subplot(gs[1, 9])
    ax_nt3.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    ax_nt4 = fig.add_subplot(gs[1, 12])
    ax_nt4.text(0.5, 0.5, "Ntv.", va="center", ha="center")
    
    nt_times = [[f'{float(data["native"][x]["initial"]["real"]["connections"]):.0f}'] for x in categories]
    ax1_nt_table = fig.add_subplot(gs[2:, 3])
    ax1_nt_table.table(cellText=nt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_power = [[f'{float(data_power["native"][x]["initial"]["user"]["mean_mw"]) / 1000:.2f}'] for x in categories]
    ax2_nt_table = fig.add_subplot(gs[2:, 6])
    ax2_nt_table.table(cellText=nt_power, cellLoc="center", bbox=[0, 0, 1, 1])
    
    nt_energy = [[f'{float(data_power["native"][x]["initial"]["user"]["mean_mj"]) / 1000:.2f}'] for x in categories]
    ax3_nt_table = fig.add_subplot(gs[2:, 9])
    ax3_nt_table.table(cellText=nt_energy, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["native"][x]["memory"]["res_used_kib"]] for x in categories]
    nt_mem = [[f"{(sum(x) / len(x) / 1000):.2f}"] for x in array_list]
    ax4_nt_table = fig.add_subplot(gs[2:, 12])
    ax4_nt_table.table(cellText=nt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    ax_uk1 = fig.add_subplot(gs[1, 4])
    ax_uk1.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk2 = fig.add_subplot(gs[1, 7])
    ax_uk2.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk3 = fig.add_subplot(gs[1, 10])
    ax_uk3.text(0.5, 0.5, "Uk.", va="center", ha="center")
    ax_uk4 = fig.add_subplot(gs[1, 13])
    ax_uk4.text(0.5, 0.5, "Uk.", va="center", ha="center")
    
    uk_times = [[f'{float(data["unikraft"][x]["initial"]["real"]["connections"]):.0f}'] for x in categories]
    ax1_uk_table = fig.add_subplot(gs[2:, 4])
    ax1_uk_table.table(cellText=uk_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_power = [[f'{float(data_power["unikraft"][x]["initial"]["user"]["mean_mw"]) / 1000:.2f}'] for x in categories]
    ax2_uk_table = fig.add_subplot(gs[2:, 7])
    ax2_uk_table.table(cellText=uk_power, cellLoc="center", bbox=[0, 0, 1, 1])
    
    uk_energy = [[f'{float(data_power["unikraft"][x]["initial"]["user"]["mean_mj"]) / 1000:.2f}'] for x in categories]
    ax3_uk_table = fig.add_subplot(gs[2:, 10])
    ax3_uk_table.table(cellText=uk_energy, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x)for x in data_mem["unikraft"][x]["memory"]["res_used_kib"]] for x in categories]
    uk_mem = [[f"{(sum(x) / len(x) / 1000):.2f}"] for x in array_list]
    ax4_uk_table = fig.add_subplot(gs[2:, 13])
    ax4_uk_table.table(cellText=uk_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    ax_cnt1 = fig.add_subplot(gs[1, 5])
    ax_cnt1.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt2 = fig.add_subplot(gs[1, 8])
    ax_cnt2.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt3 = fig.add_subplot(gs[1, 11])
    ax_cnt3.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    ax_cnt4 = fig.add_subplot(gs[1, 14])
    ax_cnt4.text(0.5, 0.5, "Cntr.", va="center", ha="center")
    
    cnt_times = [[f'{float(data["docker"][x]["initial"]["real"]["connections"]):.0f}'] for x in categories]
    ax1_cnt_table = fig.add_subplot(gs[2:, 5])
    ax1_cnt_table.table(cellText=cnt_times, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_power = [[f'{float(data_power["docker"][x]["initial"]["user"]["mean_mw"]) / 1000:.2f}'] for x in categories]
    ax2_cnt_table = fig.add_subplot(gs[2:, 8])
    ax2_cnt_table.table(cellText=cnt_power, cellLoc="center", bbox=[0, 0, 1, 1])
    
    cnt_energy = [[f'{float(data_power["docker"][x]["initial"]["user"]["mean_mj"]) / 1000:.2f}'] for x in categories]
    ax3_cnt_table = fig.add_subplot(gs[2:, 11])
    ax3_cnt_table.table(cellText=cnt_energy, cellLoc="center", bbox=[0, 0, 1, 1])
    
    array_list = [[float(x) / 1000 for x in data_mem["docker"][x]["memory"]["res_used_kib"]] for x in categories]
    cnt_mem = [[f"{(sum(x) / len(x)):.2f}"] for x in array_list]
    ax4_cnt_table = fig.add_subplot(gs[2:, 14])
    ax4_cnt_table.table(cellText=cnt_mem, cellLoc="center", bbox=[0, 0, 1, 1])
    
    #fig.text(0.5, 0.01, 'Table 3: Time, Power, Energy, and Memory consumption of Traditional and PQ TLS 1.3 Handshake.', ha='center')
    format_axes(fig)
    plt.savefig("table_tls.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()


def plot_bar_tls_speed():

    categories = [
    "Dilithium2+Kyber512",
    "Falcon-512+Kyber512",
    "Dilithium3+Kyber768",
    "Falcon-1024+Kyber768",
    "Dilithium3+Kyber1024",
    "Falcon-1024+Kyber1024",
    #"SPHINCS+-SHA2-128s-simple+Kyber512",
    "Dilithium2+BIKE-L1",
    "Dilithium2+HQC-128",
    "Dilithium2+FrodoKEM-640-AES",
    "Dilithium2+FrodoKEM-640-SHAKE",
    "RSA-2048+ECDHE",
    "ECDSA+ECDHE"
    ]
    categories.reverse()
    with open(os.path.join(SCRIPT_DIR, "results/tls_speed.json"), "r") as f:
        data = json.load(f)["tls"]
        
    native_values = [
        data["native"][x]["initial"]["real"]["connections"] for x in categories
    ]
    unikraft_values = [
        data["unikraft"][x]["initial"]["real"]["connections"] for x in categories
    ]
    docker_values = [
        data["docker"][x]["initial"]["real"]["connections"] for x in categories
    ]

    bar_width = 0.175
    bar_dist = 0.075

    x = np.arange(len(categories))
    plt.figure(figsize=(9, 5))

   
    plt.barh(x+ bar_width + bar_dist, unikraft_values, height=bar_width, label="Unikraft", color="#D81B60", edgecolor="black")
    plt.barh(x , native_values, height=bar_width, label="Native", color="#1E88E5", edgecolor="black")
    plt.barh(x - bar_width - bar_dist, docker_values, height=bar_width, label="Docker", color="#FFC107", edgecolor="black")

    plt.xlabel("Connections (1/30s)")
    #plt.title("Figure 1: TLS Connections of Traditional and PQ TLS 1.3 handshakes")
    plt.yticks(range(len(categories)), categories)
   
    plt.xscale("log")
    plt.xlim(100, 20000)
    plt.legend()
    plt.tight_layout()
    
    plt.savefig("bar_tls_speed.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()


def plot_bar_tls_power():

    categories = [
    "Dilithium2+Kyber512",
    "Falcon-512+Kyber512",
    "Dilithium3+Kyber768",
    "Falcon-1024+Kyber768",
    "Dilithium3+Kyber1024",
    "Falcon-1024+Kyber1024",
    "SPHINCS+-SHA2-128s-simple+Kyber512",
    "Dilithium2+BIKE-L1",
    "Dilithium2+HQC-128",
    "Dilithium2+FrodoKEM-640-AES",
    "Dilithium2+FrodoKEM-640-SHAKE",
    "RSA-2048+ECDHE",
    "ECDSA+ECDHE"
    ]
    categories.reverse()
    with open(os.path.join(SCRIPT_DIR, "results/tls_power.json"), "r") as f:
        data = json.load(f)
        
    native_values = [
        float(data["native"][x]["initial"]["user"]["mean_mw"]) for x in categories
    ]
    unikraft_values = [
        float(data["unikraft"][x]["initial"]["user"]["mean_mw"]) for x in categories
    ]
    docker_values = [
        float(data["docker"][x]["initial"]["user"]["mean_mw"]) for x in categories
    ]

    bar_width = 0.175
    bar_dist = 0.075

    x = np.arange(len(categories))
    plt.figure(figsize=(9, 5))

   
    plt.barh(x+ bar_width + bar_dist, unikraft_values, height=bar_width, label="Unikraft", color="#D81B60", edgecolor="black", )
    plt.barh(x , native_values, height=bar_width, label="Native", color="#1E88E5", edgecolor="black")
    plt.barh(x - bar_width - bar_dist, docker_values, height=bar_width, label="Docker", color="#FFC107", edgecolor="black")

    plt.xlabel("Average Power Consumption (mW)")
    #plt.title("Figure 2: Power Consumption of Traditional and PQ TLS 1.3 handshakes")
    plt.yticks(range(len(categories)), categories)
    plt.xlim(3000, 3600)  
    plt.legend()
    plt.tight_layout()
    
    plt.savefig("bar_tls_power.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()
    
def plot_bar_tls_energy():

    categories = [
    "Dilithium2+Kyber512",
    "Falcon-512+Kyber512",
    "Dilithium3+Kyber768",
    "Falcon-1024+Kyber768",
    "Dilithium3+Kyber1024",
    "Falcon-1024+Kyber1024",
    "SPHINCS+-SHA2-128s-simple+Kyber512",
    "Dilithium2+BIKE-L1",
    "Dilithium2+HQC-128",
    "Dilithium2+FrodoKEM-640-AES",
    "Dilithium2+FrodoKEM-640-SHAKE",
    "RSA-2048+ECDHE",
    "ECDSA+ECDHE"
    ]
    categories.reverse()
    
    with open(os.path.join(SCRIPT_DIR, "results/tls_power.json"), "r") as f:
        data = json.load(f)
        
    native_values = [
        float(data["native"][x]["initial"]["user"]["mean_mj"]) / 1000 for x in categories
    ]
    unikraft_values = [
        float(data["unikraft"][x]["initial"]["user"]["mean_mj"]) / 1000 for x in categories
    ]
    docker_values = [
        float(data["docker"][x]["initial"]["user"]["mean_mj"]) / 1000 for x in categories
    ]

    bar_width = 0.175
    bar_dist = 0.075

    x = np.arange(len(categories))
    plt.figure(figsize=(9, 5))

   
    plt.barh(x+ bar_width + bar_dist, unikraft_values, height=bar_width, label="Unikraft", color="#D81B60", edgecolor="black", )
    plt.barh(x , native_values, height=bar_width, label="Native", color="#1E88E5", edgecolor="black")
    plt.barh(x - bar_width - bar_dist, docker_values, height=bar_width, label="Docker", color="#FFC107", edgecolor="black")

    plt.xlabel("Average Energy Consumption (J)")
    #plt.title("Figure 2: Energy Consumption of Traditional and PQ TLS 1.3 handshakes")
    plt.yticks(range(len(categories)), categories)
    plt.xlim(180, 240)  

    plt.legend()
    plt.tight_layout()
    
    plt.savefig("bar_tls_energy.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()
 
    
      
def plot_bar_tls_mem():
    with open(os.path.join(SCRIPT_DIR, "results/tls_mem.json"), "r") as f:
        data = json.load(f)["tls"]

    # Data
    categories = [
        "SPHINCS+-SHA2-128s-simple+Kyber512",
       #"Dilithium3+Kyber512",
        "Falcon-1024+Kyber512",
        "SPHINCS+-SHA2-128s-simple+FrodoKEM-640-AES",
        #"Dilithium3+FrodoKEM-640-AES",
        "Falcon-1024+FrodoKEM-640-AES",
    ]
    native_values = []
    native_values_float = []
    native_values_str = [data["native"][x]["memory"]["used_mib"] for x in categories]
    for i in range(len(native_values)):
        for j in range(len(native_values[i])):
            native_values_float.append(float(native_values[i][j]))
        native_values.append(np.mean(native_values_float))

    unikraft_values = [data["unikraft"][x]["memory"]["used_mib"] for x in categories]
    for i in range(len(unikraft_values)):
        for j in range(len(unikraft_values[i])):
            unikraft_values[i][j] = float(unikraft_values[i][j])

    docker_values = [data["docker"][x]["memory"]["used_mib"] for x in categories]
    for i in range(len(docker_values)):
        for j in range(len(docker_values[i])):
            docker_values[i][j] = float(docker_values[i][j])

    # Bar width
    bar_width = 0.25

    # X locations for the groups
    x = np.arange(len(categories))

    # Create bars
    plt.barh(x - bar_width, native_values, height=bar_width, label="Native", color="b")
    plt.barh(x, unikraft_values, height=bar_width, label="Unikraft", color="g")
    plt.barh(x + bar_width, docker_values, height=bar_width, label="Docker", color="r")

    # Adding labels and title
    plt.xlabel("Algorithms")
    plt.ylabel("Connections")
    plt.title("TLS Connections in 30 seconds")
    plt.xticks(x, categories)
    plt.legend()

    for i in range(len(categories)):
        plt.text(-2, i - bar_width, categories[i], va="center", ha="right")

    # Show the plot
    plt.tight_layout()
    plt.show()


def plot_bar_primitives_speed():

    sigs = [
    "SPHINCS+-SHA2-128s-simple",
    "SPHINCS+-SHA2-128f-simple",
    "Falcon-512",
    "Dilithium2",
    "Dilithium3",
    "Falcon-1024",
    "ECDSA",
    "RSA-2048",
    ]
    kems = [
        "Kyber512",
        "Kyber768",
        "Kyber1024",
        "BIKE-L1",
        "HQC-128",
        "FrodoKEM-640-AES",
        "FrodoKEM-640-SHAKE",
        "ECDHE",
    ]
    #categories.reverse()
    with open(os.path.join(SCRIPT_DIR, "results/primitives_speed.json"), "r") as f:
        data = json.load(f)["primitive"]
        
    native_values_keygen_sig = [
        data["native"]["sig"][x]["keygen"]["mean_us"] for x in sigs
    ]
    
    native_values_encaps_sig = [
        data["native"]["sig"][x]["encaps"]["mean_us"] for x in sigs
    ]
    
    native_values_decaps_sig = [
        data["native"]["sig"][x]["decaps"]["mean_us"] for x in sigs
    ]
    
    unikraft_values_keygen_sig = [
        data["unikraft"]["sig"][x]["keygen"]["mean_us"] for x in sigs
    ]
    
    unikraft_values_encaps_sig = [
        data["unikraft"]["sig"][x]["encaps"]["mean_us"] for x in sigs
    ]
    
    unikraft_values_decaps_sig = [
        data["unikraft"]["sig"][x]["decaps"]["mean_us"] for x in sigs
    ]
    
    docker_values_keygen_sig = [
        data["docker"]["sig"][x]["keygen"]["mean_us"] for x in sigs
    ]
    
    docker_values_encaps_sig = [
        data["docker"]["sig"][x]["encaps"]["mean_us"] for x in sigs
    ]
    
    docker_values_decaps_sig = [
        data["docker"]["sig"][x]["decaps"]["mean_us"] for x in sigs
    ]
    
    # unikraft_values = [
    #     data["unikraft"][x]["initial"]["real"]["connections"] for x in categories
    # ]
    # docker_values = [
    #     data["docker"][x]["initial"]["real"]["connections"] for x in categories
    # ]

    bar_width = 0.06
    bar_dist = 0.03

    x = np.arange(0, len(sigs), 1)
    plt.figure(figsize=(12, 5))


    plt.bar(x - bar_width - bar_dist, width=bar_width, height=native_values_keygen_sig, color="#1E88E5", edgecolor="black")
    plt.bar(x, width=bar_width, height=native_values_encaps_sig, label="Native   (keygen/sign/verify)", color="#1E88E5", edgecolor="black")
    plt.bar(x + bar_width + bar_dist, width=bar_width,height=native_values_decaps_sig, color="#1E88E5", edgecolor="black")

    plt.bar(x + bar_width + 0.5 * bar_width + 3 * bar_dist, width=bar_width, height=unikraft_values_keygen_sig, label="Unikraft (keygen/sign/verify)", color="#D81B60", edgecolor="black")
    plt.bar(x + 2 * bar_width + 0.5 * bar_width + 4 * bar_dist, width=bar_width, height=unikraft_values_encaps_sig, color="#D81B60", edgecolor="black")
    plt.bar(x + 3 * bar_width + 0.5 * bar_width + 5 * bar_dist, width=bar_width,height=unikraft_values_decaps_sig, color="#D81B60", edgecolor="black")
    
    plt.bar(x - 3 * bar_width - 0.5 * bar_width - 5 * bar_dist, width=bar_width, height=docker_values_keygen_sig, color="#FFC107", edgecolor="black")
    plt.bar(x - 2 * bar_width - 0.5 * bar_width - 4 * bar_dist, width=bar_width, height=docker_values_encaps_sig, color="#FFC107", edgecolor="black")
    plt.bar(x - bar_width - 0.5 * bar_width - 3 * bar_dist, width=bar_width,height=docker_values_decaps_sig, label="Docker  (keygen/sign/verify)", color="#FFC107", edgecolor="black")
    
    
    plt.ylabel("Execution Time (us)")
    #plt.title("Figure 1: TLS Connections of Traditional and PQ TLS 1.3 handshakes")
    
    sigs = [
    "SPHINCS+s",
    "SPHINCS+f",
    "Falcon-512",
    "Dilithium2",
    "Dilithium3",
    "Falcon-1024",
    "ECDSA",
    "RSA-2048",
    ]
       
    plt.xticks(range(len(sigs)), sigs)
    
    plt.yscale("log")
    #plt.ylim(100, 20000)
    
    plt.legend()
    plt.tight_layout()
    
    plt.savefig("bar_sig_speed.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()
    
    with open(os.path.join(SCRIPT_DIR, "results/primitives_speed.json"), "r") as f:
        data = json.load(f)["primitive"]
        
    native_values_keygen_kem = [
        data["native"]["kem"][x]["keygen"]["mean_us"] for x in kems
    ]
    
    native_values_encaps_kem = [
        data["native"]["kem"][x]["encaps"]["mean_us"] for x in kems
    ]
    
    native_values_decaps_kem = [
        data["native"]["kem"][x]["decaps"]["mean_us"] for x in kems
    ]
    
    unikraft_values_keygen_kem = [
        data["unikraft"]["kem"][x]["keygen"]["mean_us"] for x in kems
    ]
    
    unikraft_values_encaps_kem = [
        data["unikraft"]["kem"][x]["encaps"]["mean_us"] for x in kems
    ]
    
    unikraft_values_decaps_kem = [
        data["unikraft"]["kem"][x]["decaps"]["mean_us"] for x in kems
    ]
    
    docker_values_keygen_kem = [
        data["docker"]["kem"][x]["keygen"]["mean_us"] for x in kems
    ]
    
    docker_values_encaps_kem = [
        data["docker"]["kem"][x]["encaps"]["mean_us"] for x in kems
    ]
    
    docker_values_decaps_kem = [
        data["docker"]["kem"][x]["decaps"]["mean_us"] for x in kems
    ]
    
    plt.figure(figsize=(12, 5))

    plt.bar(x - bar_width - bar_dist, width=bar_width, height=native_values_keygen_kem, color="#1E88E5", edgecolor="black")
    plt.bar(x, width=bar_width, height=native_values_encaps_kem, label="Native   (keygen/sign/verify)", color="#1E88E5", edgecolor="black")
    plt.bar(x + bar_width + bar_dist, width=bar_width,height=native_values_decaps_kem, color="#1E88E5", edgecolor="black")

    plt.bar(x + bar_width + 0.5 * bar_width + 3 * bar_dist, width=bar_width, height=unikraft_values_keygen_kem, label="Unikraft (keygen/sign/verify)", color="#D81B60", edgecolor="black")
    plt.bar(x + 2 * bar_width + 0.5 * bar_width + 4 * bar_dist, width=bar_width, height=unikraft_values_encaps_kem, color="#D81B60", edgecolor="black")
    plt.bar(x + 3 * bar_width + 0.5 * bar_width + 5 * bar_dist, width=bar_width,height=unikraft_values_decaps_kem, color="#D81B60", edgecolor="black")
    
    plt.bar(x - 3 * bar_width - 0.5 * bar_width - 5 * bar_dist, width=bar_width, height=docker_values_keygen_kem, color="#FFC107", edgecolor="black")
    plt.bar(x - 2 * bar_width - 0.5 * bar_width - 4 * bar_dist, width=bar_width, height=docker_values_encaps_kem, color="#FFC107", edgecolor="black")
    plt.bar(x - bar_width - 0.5 * bar_width - 3 * bar_dist, width=bar_width,height=docker_values_decaps_kem, label="Docker  (keygen/sign/verify)", color="#FFC107", edgecolor="black")
    
    plt.ylabel("Execution Time (us)")
    
    kems = [
        "Kyber512",
        "Kyber768",
        "Kyber1024",
        "BIKE-L1",
        "HQC-128",
        "FrodoKEM-AES",
        "FrodoKEM-SHAKE",
        "ECDHE",
    ]
        
    
    plt.xticks(range(len(kems)), kems)
    
    plt.yscale("log")
    #plt.ylim(100, 20000)
    
    plt.legend()
    plt.tight_layout()
    
    plt.savefig("bar_kem_speed.pdf", format="pdf", dpi=300, bbox_inches="tight", pad_inches= 0.1)
    plt.show()
    
    
def format_axes(fig):
    for i, ax in enumerate(fig.axes):
        ax.tick_params(labelbottom=False, labelleft=False, labelright=False)
        ax.get_xaxis().set_ticks([])
        ax.get_yaxis().set_ticks([])
        # for spine in ax.spines.values():
        #         spine.set_visible(False)
        

if __name__ == "__main__":
    main()
