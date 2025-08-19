#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import os
import json

SCRIPT_PATH = __file__
SCRIPT_DIR = os.path.dirname(SCRIPT_PATH)

# take this table as reference
"""
Operation                            | Iterations | Total time (s) | Time (us): mean | pop. stdev | High-prec time (ns): mean | pop. stdev
------------------------------------ | ----------:| --------------:| ---------------:| ----------:| -------------------------:| ----------:
BIKE-L1                              |            |                |                 |            |                           |           
keygen                               |        448 |          3.006 |        6710.393 |   1131.390 |                   6710376 |    1131394
encaps                               |       8435 |          3.000 |         355.666 |      7.118 |                    355637 |       7119
decaps                               |        584 |          3.000 |        5137.187 |     52.629 |                   5137154 |      52619
BIKE-L3                              |            |                |                 |            |                           |           
keygen                               |        145 |          3.012 |       20774.124 |    173.470 |                  20774093 |     173483
encaps                               |       2748 |          3.001 |        1092.033 |     39.129 |                   1091991 |      39124
decaps                               |        184 |          3.003 |       16323.158 |   2268.648 |                  16323104 |    2268661
BIKE-L5                              |            |                |                 |            |                           |           
keygen                               |         58 |          3.028 |       52202.828 |    775.223 |                  52202778 |     775254
encaps                               |       1107 |          3.002 |        2711.478 |     29.496 |                   2711449 |      29495
decaps                               |         75 |          3.001 |       40016.800 |    461.803 |                  40016759 |     461842
Classic-McEliece-348864              |            |                |                 |            |                           |           
keygen                               |         39 |          3.080 |       78985.897 |  45500.571 |                  78985886 |   45500607
encaps                               |     146363 |          3.000 |          20.497 |      3.928 |                     20467 |       3930
decaps                               |        154 |          3.014 |       19568.727 |    202.225 |                  19568721 |     202231
Classic-McEliece-348864f             |            |                |                 |            |                           |           
keygen                               |         91 |          3.013 |       33108.538 |    234.284 |                  33108508 |     234294
encaps                               |     146759 |          3.000 |          20.442 |      3.588 |                     20411 |       3589
decaps                               |        155 |          3.017 |       19461.697 |    105.317 |                  19461677 |     105319
Classic-McEliece-460896              |            |                |                 |            |                           |           
keygen                               |         13 |          3.055 |      234982.538 | 148376.994 |                 234982538 |  148376985
encaps                               |      75227 |          3.000 |          39.880 |     13.330 |                     39849 |      13329
decaps                               |         73 |          3.031 |       41517.041 |   3109.858 |                  41516979 |    3109859
Classic-McEliece-460896f             |            |                |                 |            |                           |           
keygen                               |         31 |          3.092 |       99732.645 |    831.247 |                  99732546 |     831292
encaps                               |      78091 |          3.000 |          38.417 |     13.600 |                     38386 |      13600
decaps                               |         74 |          3.030 |       40947.703 |    421.624 |                  40947674 |     421638
Classic-McEliece-6688128             |            |                |                 |            |                           |           
keygen                               |          8 |          3.132 |      391455.875 | 211565.113 |                 391455744 |  211565189
encaps                               |      34355 |          3.000 |          87.324 |     27.387 |                     87292 |      27389
decaps                               |         38 |          3.027 |       79651.263 |   2876.729 |                  79651240 |    2876728
Classic-McEliece-6688128f            |            |                |                 |            |                           |           
keygen                               |         17 |          3.088 |      181630.176 |  13414.894 |                 181630163 |   13414922
encaps                               |      32937 |          3.000 |          91.085 |     27.984 |                     91053 |      27984
"""


def main():
    # plot_power()
    # plot_table()
    plot_bar_tls()
    #plot_power()
    


def plot_power():
    with open(os.path.join(SCRIPT_DIR, "results/primitives.power"), "r") as f:
        data = f.readlines()[2:]

    first_val = float(data[0].split(" ")[0])
    show_values_num = len(data)
    timestamps = [float(d.split(" ")[0]) - first_val for d in data][:show_values_num]
    voltages = [float(d.split(" ")[2]) for d in data][:show_values_num]
    amps = [float(d.split(" ")[3]) for d in data][:show_values_num]
    wattage = [float(d.split(" ")[7]) for d in data][:show_values_num]

    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, voltages, linestyle="-", color="b", label="Volts")

    plt.title("Voltage")
    plt.xlabel("Time (seconds)")
    plt.ylabel("Volts")

    plt.yticks(np.arange(0, 10, 1))
    plt.xticks(np.arange(0, 1500, 10))

    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()

    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, amps, linestyle="-", color="r", label="Amps")

    plt.title("Amps")
    plt.xlabel("Time (seconds)")
    plt.ylabel("Amps")

    plt.yticks(np.arange(0, 10, 1))
    plt.xticks(np.arange(0, 1500, 100))

    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()

    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, amps, linestyle="-", color="g", label="Wattage")

    start_point_found = False
    x = 0
    x2 = 0
    for i in range(len(wattage) - 1):

        wattage_prev = wattage[i]
        wattage_next = wattage[i + 1]
        # Define the rectangle parameters
        difference = 0.035
        if wattage_next - wattage_prev > difference and not start_point_found:
            print("start at " + str(i))
            start_point_found = True
            x = i
            continue 
        
        if abs(wattage_prev - wattage_next) > difference and start_point_found:
            print("end at " + str(i))
            x2 = i
            start_point_found = False
            rect = plt.Rectangle((timestamps[x], 0.35), timestamps[x2] - timestamps[x], 0.5, linewidth=1, edgecolor='r', facecolor='none')
            plt.gca().add_patch(rect)    
    
    plt.title("Wattage")
    plt.xlabel("Time (seconds)")
    plt.ylabel("Wattage")


    plt.yticks(np.arange(0, 10, 1))
    #plt.xticks(np.arange(0, 1500, 1))

    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()

    # with open(os.path.join(SCRIPT_DIR, "results/tls.power"), "r") as f:
    #     data = f.readlines()[2:]

    # first_val = float(data[0].split(" ")[0])
    # show_values_num = len(data)
    # timestamps = [float(d.split(" ")[0]) - first_val for d in data][:show_values_num]
    # voltages = [float(d.split(" ")[2]) for d in data][:show_values_num]
    # amps = [float(d.split(" ")[3]) for d in data][:show_values_num]
    # wattage = [float(d.split(" ")[7]) for d in data][:show_values_num]

    # plt.figure(figsize=(10, 5))
    # plt.plot(timestamps, voltages, linestyle="-", color="b", label="Volts")

    # plt.title("Voltage")
    # plt.xlabel("Time (seconds)")
    # plt.ylabel("Volts")

    # plt.yticks(np.arange(0, 10, 1))
    # plt.xticks(np.arange(0, 1500, 100))

    # plt.grid()
    # plt.legend()
    # plt.tight_layout()

    # # Show the plot
    # plt.show()

    # plt.figure(figsize=(10, 5))
    # plt.plot(timestamps, amps, linestyle="-", color="r", label="Volts")

    # plt.title("Amps")
    # plt.xlabel("Time (seconds)")
    # plt.ylabel("Amps")

    # plt.yticks(np.arange(0, 10, 1))
    # plt.xticks(np.arange(0, 1500, 100))

    # plt.grid()
    # plt.legend()
    # plt.tight_layout()

    # # Show the plot
    # plt.show()

    # plt.figure(figsize=(10, 5))
    # plt.plot(timestamps, amps, linestyle="-", color="g", label="Wattage")

    # plt.title("Wattage")
    # plt.xlabel("Time (seconds)")
    # plt.ylabel("Wattage")

    # plt.yticks(np.arange(0, 10, 1))
    # plt.xticks(np.arange(0, 1500, 10))

    # plt.grid()
    # plt.legend()
    # plt.tight_layout()

    # # Show the plot
    # plt.show()


def plot_table():
    # Sample data
    data = [
        ["Cipher", "Time (s)", "Power (W)"],
        ["BIKE-L1", 50, 0],
        ["hi", 50, 500],
    ]

    # Create a figure and axis
    fig, ax = plt.subplots()

    # Hide axes
    ax.axis("tight")
    ax.axis("off")

    # Create the table
    table = ax.table(cellText=data, loc="center", cellLoc="center")

    # Display the table
    plt.show()
    fig.savefig("figure.pdf", bbox_inches="tight")


def plot_bar_tls():
    with open(os.path.join(SCRIPT_DIR, "results/tls.json"), "r") as f:
        data = json.load(f)["tls"]

    # Data
    categories = [
        "SPHINCS+-SHA2-128s-simple+Kyber512",
        "Dilithium3+Kyber512",
        "Falcon-1024+Kyber512",
        "Dilithium3+FrodoKEM-640-AES",
        "Falcon-1024+FrodoKEM-640-AES",
        "Falxon-1024+BIKE-L1",
    ]
    
    native_values = [data["native"][x]["initial"]["real"]["connections"] for x in categories]
    unikraft_values = [data["unikraft"][x]["initial"]["real"]["connections"] for x in categories]
    docker_values= [data["docker"][x]["initial"]["real"]["connections"] for x in categories]

    # Bar width
    bar_width = 0.25

    # X locations for the groups
    x = np.arange(len(categories))

    # Create bars
    plt.barh(x - bar_width, native_values, height=bar_width, label='Native', color='b')
    plt.barh(x, unikraft_values, height=bar_width, label='Unikraft', color='g')
    plt.barh(x + bar_width, docker_values, height=bar_width, label='Docker', color='r')
    
    
    # Adding labels and title
    plt.xlabel("Algorithms")
    plt.ylabel("Connections")
    plt.title("TLS Connections in 30 seconds")
    #plt.xticks(x, categories)
    plt.legend()

    for i in range(len(categories)):
        plt.text(-2, i - bar_width, categories[i], va='center', ha='right')
        

    # Show the plot
    plt.tight_layout()
    plt.show()

def plot_bar_tls_mem():
    with open(os.path.join(SCRIPT_DIR, "results/tls_mem.json"), "r") as f:
        data = json.load(f)["tls"]

    # Data
    categories = [
        "SPHINCS+-SHA2-128s-simple+Kyber512",
        "Dilithium3+Kyber512",
        "Falcon-1024+Kyber512",
        "SPHINCS+-SHA2-128s-simple+FrodoKEM-640-AES",
        "Dilithium3+FrodoKEM-640-AES",
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
    
    docker_values= [data["docker"][x]["memory"]["used_mib"] for x in categories]
    for i in range(len(docker_values)):
        for j in range(len(docker_values[i])):
            docker_values[i][j] = float(docker_values[i][j])

    # Bar width
    bar_width = 0.25

    # X locations for the groups
    x = np.arange(len(categories))

    # Create bars
    plt.barh(x - bar_width, native_values, height=bar_width, label='Native', color='b')
    plt.barh(x, unikraft_values, height=bar_width, label='Unikraft', color='g')
    plt.barh(x + bar_width, docker_values, height=bar_width, label='Docker', color='r')
    
    
    # Adding labels and title
    plt.xlabel("Algorithms")
    plt.ylabel("Connections")
    plt.title("TLS Connections in 30 seconds")
    #plt.xticks(x, categories)
    plt.legend()

    for i in range(len(categories)):
        plt.text(-2, i - bar_width, categories[i], va='center', ha='right')
        

    # Show the plot
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
