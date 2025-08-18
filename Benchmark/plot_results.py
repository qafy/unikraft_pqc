#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import os 

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
    plot_power()
    #plot_table()

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
    plt.plot(timestamps, voltages, linestyle='-', color='b', label='Power (Volts)')

    plt.title('Voltage Over Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Power (Volts)')
    
    plt.yticks(np.arange(0, 10, 1))
    plt.xticks(np.arange(0, 1500, 10))
    
    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()
    
    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, amps, linestyle='-', color='r', label='Power (Volts)')

    plt.title('Amps Over Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Power (Amps)')
    
    plt.yticks(np.arange(0, 10, 1))
    plt.xticks(np.arange(0, 1500, 100))
    
    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()
    
    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, amps, linestyle='-', color='g', label='Power (Amps)')

    plt.title('Wattage Over Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Power (W)')
    
    plt.yticks(np.arange(0, 10, 1))
    plt.xticks(np.arange(0, 1500, 1))
    
    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()
    
    with open(os.path.join(SCRIPT_DIR, "results/tls.power"), "r") as f:
        data = f.readlines()[2:]

    first_val = float(data[0].split(" ")[0])
    show_values_num = len(data)
    timestamps = [float(d.split(" ")[0]) - first_val for d in data][:show_values_num]
    voltages = [float(d.split(" ")[2]) for d in data][:show_values_num]
    amps = [float(d.split(" ")[3]) for d in data][:show_values_num]
    wattage = [float(d.split(" ")[7]) for d in data][:show_values_num]
    
    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, voltages, linestyle='-', color='b', label='Power (Volts)')

    plt.title('Voltage Over Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Power (Volts)')
    
    plt.yticks(np.arange(0, 10, 1))
    plt.xticks(np.arange(0, 1500, 100))
    
    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()
    
    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, amps, linestyle='-', color='r', label='Power (Volts)')

    plt.title('Amps Over Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Power (Amps)')
    
    plt.yticks(np.arange(0, 10, 1))
    plt.xticks(np.arange(0, 1500, 100))
    
    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()
    
    plt.figure(figsize=(10, 5))
    plt.plot(timestamps, amps, linestyle='-', color='g', label='Power (Amps)')

    plt.title('Wattage Over Time')
    plt.xlabel('Time (seconds)')
    plt.ylabel('Power (W)')
    
    plt.yticks(np.arange(0, 10, 1))
    plt.xticks(np.arange(0, 1500, 10))
    
    plt.grid()
    plt.legend()
    plt.tight_layout()

    # Show the plot
    plt.show()

def plot_table():
    # Sample data
    data = [
        ['Cipher', 'Time (s)', 'Power (W)'],
        ["BIKE-L1", 50, 0],
        ["hi", 50, 500],
    ]

    # Create a figure and axis
    fig, ax = plt.subplots()

    # Hide axes
    ax.axis('tight')
    ax.axis('off')

    # Create the table
    table = ax.table(cellText=data, loc='center', cellLoc='center')

    # Display the table
    plt.show()
    fig.savefig("figure.pdf", bbox_inches="tight")

def plot_bar():
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



if __name__ == "__main__":
    main()



