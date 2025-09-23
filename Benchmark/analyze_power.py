#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import os
import json
from scipy.interpolate import interp1d
from datetime import datetime, timedelta

SCRIPT_PATH = __file__
SCRIPT_DIR = os.path.dirname(SCRIPT_PATH)


def main():
    plot_power_primitives()
    #plot_power_tls()


def plot_power_tls():

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
        "ECDSA+ECDHE",
    ]

    with open(os.path.join(SCRIPT_DIR, "results/tls_power"), "r") as f:
        data = f.readlines()[2:]
    with open(os.path.join(SCRIPT_DIR, "results/tls_power_meta.json")) as f:
        data_json = json.load(f)["tls"]

    first_val = float(data[0].split(" ")[0])
    show_values_num = len(data)
    timestamps = [float(d.split(" ")[0]) - first_val for d in data][:show_values_num]
    voltages = [float(d.split(" ")[2]) for d in data][:show_values_num]
    amps = [float(d.split(" ")[3]) for d in data][:show_values_num]
    wattage = [amp * voltages[i] for i, amp in enumerate(amps)]
    first_val_ws = float(data[0].split(" ")[7])
    ws = [float(d.split(" ")[7]) - first_val for d in data][:show_values_num]

    # Wattage
    amps_smooth = []

    amps_smooth.append((amps[0] + amps[1]) / 2)
    for i in range(1, len(amps) - 1):
        amps_smooth.append((amps[i - 1] + amps[i] + amps[i + 1]) / 3)

    amps_smooth.append((amps[-1] + amps[-2]) / 2)

    amps_temp = amps_smooth
    amps_smooth = []

    amps_smooth.append((amps_temp[0] + amps_temp[1]) / 2)
    for i in range(1, len(amps_temp) - 1):
        amps_smooth.append((amps_temp[i - 1] + amps_temp[i] + amps_temp[i + 1]) / 3)

    amps_smooth.append((amps_temp[-1] + amps_temp[-2]) / 2)

    timestamps_np = np.array(timestamps)
    # interpolated
    interp_func = interp1d(timestamps_np - timestamps[0], amps, kind="cubic")

    x_new = np.linspace(timestamps[0], timestamps[-1], len(timestamps))
    # print(x_new[:100])
    y_new = interp_func(x_new)

    dy_new = np.gradient(y_new, x_new)
    dy_new = dy_new / 100
    plt.figure(figsize=(10, 5))
    # plt.plot(x_new, y_new, '-', color='purple', label='Amps Interpolated')
    plt.plot(x_new, dy_new, "-", color="pink", label="Amps Derivative")
    plt.plot(timestamps, wattage, linestyle="-", color="g", label="Wattage")
    plt.plot(
        timestamps, amps_smooth, linestyle="-", color="orange", label="Amps Smooth"
    )

    start_point_found = False
    x = 0
    x2 = 0

    time_first = timestamps[0]
    time_buff = 0.0

    recorded_times = {}
    recorded_times_end = {}
    assert data_json["native"]["Dilithium2+Kyber512"]["initial"]["user"]["order"] == 0

    time_start = timestamp(
        data_json["native"]["Dilithium2+Kyber512"]["initial"]["user"]["timestamp_start"]
    )

    shift = 21

    for cat in categories:
        for virt in ["unikraft", "docker", "native"]:
            time_x = (
                timestamp(data_json[virt][cat]["initial"]["user"]["timestamp_start"])
                - time_start
                + shift
            )
            line = plt.Line2D(
                [time_x, time_x],
                [0, 1],
                color="grey",
                linewidth=2,
                label="Colored Line",
            )
            plt.gca().add_line(line)
            recorded_times[data_json[virt][cat]["initial"]["user"]["order"]] = time_x
            time_x = (
                timestamp(data_json[virt][cat]["initial"]["user"]["timestamp_stop"])
                - time_start
                + shift
            )
            line = plt.Line2D(
                [time_x, time_x],
                [0, 1],
                color="black",
                linewidth=1,
                label="Colored Line",
            )
            plt.gca().add_line(line)
            recorded_times_end[data_json[virt][cat]["initial"]["user"]["order"]] = (
                time_x
            )

    print(f"Length of recorded values: {len(recorded_times)}")

    energy_analyzed = {}
    wattage_analyzed = {}
    intervall_i = 0

    for i in range(len(amps_smooth) - 1):

        amps_prev = amps_smooth[i]
        amps_next = amps_smooth[i + 1]
        difference = 0.02
        difference_down = 0.05
        if (
            intervall_i < 39
            and amps_next - amps_prev > difference
            and recorded_times[intervall_i] < timestamps[i] - timestamps[0]
            and not start_point_found
        ):
            start_point_found = True
            x = i
            time_buff = timestamps[i]
            continue

        if (
            intervall_i < 39
            and recorded_times_end[intervall_i] - recorded_times[intervall_i]
            < timestamps[i] - time_buff
            and start_point_found
        ) or (
            timestamps[i] - time_buff > 5.0
            and amps_prev - amps_next > difference_down
            and start_point_found
        ):
            start_point_found = False
            x2 = i
            energy_analyzed[intervall_i] = ws[x2] - ws[x]
            wattage_analyzed[intervall_i] = np.mean(wattage[x : x2 + 1]).tolist()
            intervall_i += 1

            rect = plt.Rectangle(
                (timestamps[x], 0.35),
                timestamps[x2] - timestamps[x],
                0.5,
                linewidth=1,
                edgecolor="r",
                facecolor="none",
            )
            plt.gca().add_patch(rect)

    print(f"Length of analyzed values: {len(energy_analyzed)} {len(wattage_analyzed)}")

    # print(energy_analyzed)
    # print(wattage_analyzed)

    for cat in categories:
        for virt in ["unikraft", "docker", "native"]:
            ener = energy_analyzed[data_json[virt][cat]["initial"]["user"]["order"]]
            data_json[virt][cat]["initial"]["user"]["mean_mj"] = f"{1000 * ener:.2f}"

            wat = wattage_analyzed[data_json[virt][cat]["initial"]["user"]["order"]]
            data_json[virt][cat]["initial"]["user"]["mean_mw"] = f"{1000 * wat:.2f}"

    with open(
        os.path.join(
            SCRIPT_DIR,
            "results_primitives_power"
            + datetime.today().strftime("%Y-%m-%d_%H-%M-%S")
            + ".json",
        ),
        "w",
    ) as f:
        json.dump(data_json, f)

    plt.title("Wattage")
    plt.xlabel("Time (seconds)")
    plt.ylabel("Wattage")

    plt.yticks(np.arange(0, 10, 1))

    plt.grid()
    plt.tight_layout()

    plt.show()


def plot_power_primitives():

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

    with open(os.path.join(SCRIPT_DIR, "results/primitives_power"), "r") as f:
        data = f.readlines()[2:]
    with open(os.path.join(SCRIPT_DIR, "results/primitives_power_meta.json")) as f:
        data_json = json.load(f)["primitive"]

    first_val = float(data[0].split(" ")[0])
    show_values_num = len(data)
    timestamps = [float(d.split(" ")[0]) - first_val for d in data][:show_values_num]
    voltages = [float(d.split(" ")[2]) for d in data][:show_values_num]
    amps = [float(d.split(" ")[3]) for d in data][:show_values_num]
    wattage = [amp * voltages[i] for i, amp in enumerate(amps)]
    first_val_ws = float(data[0].split(" ")[7])
    ws = [float(d.split(" ")[7]) - first_val for d in data][:show_values_num]

    # Voltage
    # plt.figure(figsize=(10, 5))
    # plt.plot(timestamps, voltages, linestyle="-", color="b", label="Volts")

    # plt.title("Voltage")
    # plt.xlabel("Time (seconds)")
    # plt.ylabel("Volts")

    # plt.yticks(np.arange(0, 10, 1))
    # plt.xticks(np.arange(0, 1500, 10))

    # plt.grid()
    # plt.legend()
    # plt.tight_layout()

    # plt.show()

    # Amps
    # plt.figure(figsize=(10, 5))
    # plt.plot(timestamps, amps, linestyle="-", color="r", label="Amps")

    # plt.title("Amps")
    # plt.xlabel("Time (seconds)")
    # plt.ylabel("Amps")

    # plt.yticks(np.arange(0, 10, 1))
    # plt.xticks(np.arange(0, 1500, 100))

    # plt.grid()
    # plt.legend()
    # plt.tight_layout()

    # plt.show()

    # Wattage
    amps_smooth = []

    amps_smooth.append((amps[0] + amps[1]) / 2)
    for i in range(1, len(amps) - 1):
        amps_smooth.append((amps[i - 1] + amps[i] + amps[i + 1]) / 3)

    amps_smooth.append((amps[-1] + amps[-2]) / 2)

    amps_temp = amps_smooth
    amps_smooth = []

    amps_smooth.append((amps_temp[0] + amps_temp[1]) / 2)
    for i in range(1, len(amps_temp) - 1):
        amps_smooth.append((amps_temp[i - 1] + amps_temp[i] + amps_temp[i + 1]) / 3)

    amps_smooth.append((amps_temp[-1] + amps_temp[-2]) / 2)

    timestamps_np = np.array(timestamps)
    # interpolated
    interp_func = interp1d(timestamps_np - timestamps[0], amps, kind="cubic")

    x_new = np.linspace(timestamps[0], timestamps[-1], len(timestamps))
    # print(x_new[:100])
    y_new = interp_func(x_new)

    dy_new = np.gradient(y_new, x_new)
    dy_new = dy_new / 100
    plt.figure(figsize=(10, 5))
    # plt.plot(x_new, y_new, '-', color='purple', label='Amps Interpolated')
    plt.plot(x_new, dy_new, "-", color="pink", label="Amps Derivative")
    plt.plot(timestamps, wattage, linestyle="-", color="g", label="Wattage")
    plt.plot(
        timestamps, amps_smooth, linestyle="-", color="orange", label="Amps Smooth"
    )

    start_point_found = False
    x = 0
    x2 = 0

    time_first = timestamps[0]
    time_buff = 0.0

    recorded_times = {}
    recorded_times_end = {}
    assert (
        data_json["native"]["sig"]["SPHINCS+-SHA2-128s-simple"]["keygen"]["order"] == 0
    )

    time_start = timestamp(
        data_json["native"]["sig"]["SPHINCS+-SHA2-128s-simple"]["keygen"][
            "timestamp_start"
        ]
    )
    shift = 26
    for sig in sigs:
        for virt in ["unikraft", "docker", "native"]:
            for mode in ["keygen", "encaps", "decaps"]:
                time_x = (
                    timestamp(data_json[virt]["sig"][sig][mode]["timestamp_start"])
                    - time_start
                    + shift
                )
                line = plt.Line2D(
                    [time_x, time_x],
                    [0, 1],
                    color="grey",
                    linewidth=2,
                    label="Colored Line",
                )
                plt.gca().add_line(line)
                recorded_times[data_json[virt]["sig"][sig][mode]["order"]] = time_x
                time_x = (
                    timestamp(data_json[virt]["sig"][sig][mode]["timestamp_stop"])
                    - time_start
                    + shift
                )
                line = plt.Line2D(
                    [time_x, time_x],
                    [0, 1],
                    color="black",
                    linewidth=1,
                    label="Colored Line",
                )
                plt.gca().add_line(line)
                recorded_times_end[data_json[virt]["sig"][sig][mode]["order"]] = time_x

    for kem in kems:
        for virt in ["unikraft", "docker", "native"]:
            for mode in ["keygen", "encaps", "decaps"]:
                if kem == "ECDHE" and mode == "decaps":
                    continue
                time_x = (
                    timestamp(data_json[virt]["kem"][kem][mode]["timestamp_start"])
                    - time_start
                    + shift
                )
                line = plt.Line2D(
                    [time_x, time_x],
                    [0, 1],
                    color="grey",
                    linewidth=2,
                    label="Colored Line",
                )
                plt.gca().add_line(line)
                recorded_times[data_json[virt]["kem"][kem][mode]["order"]] = time_x
                time_x = (
                    timestamp(data_json[virt]["kem"][kem][mode]["timestamp_stop"])
                    - time_start
                    + shift
                )
                line = plt.Line2D(
                    [time_x, time_x],
                    [0, 1],
                    color="black",
                    linewidth=1,
                    label="Colored Line",
                )
                plt.gca().add_line(line)
                recorded_times_end[data_json[virt]["kem"][kem][mode]["order"]] = time_x
    print(f"Length of recorded values: {len(recorded_times)}")
    # print(len(recorded_times_end))
    # print(recorded_times)
    # print(recorded_times_end)
    energy_analyzed = {}
    wattage_analyzed = {}
    intervall_i = 0
    # print(timestamps[3400] - timestamps[0])
    # print(recorded_times_end[0])
    for i in range(len(amps_smooth) - 1):

        amps_prev = amps_smooth[i]
        amps_next = amps_smooth[i + 1]
        # Define the rectangle parameters
        # if abs(amps_prev - amps_next) > difference and start_point_found:
        #     print("end at " + str(i))
        difference = 0.020

        no_measurements = False
        for virt in ["unikraft", "docker", "native"]:
            if data_json[virt]["kem"]["ECDHE"]["decaps"]["order"] == intervall_i:
                # print("No measurements")
                no_measurements = True
                intervall_i += 1

        if no_measurements:
            continue

        if (
            intervall_i < 144
            and amps_next - amps_prev > difference
            and recorded_times[intervall_i] < timestamps[i] - timestamps[0]
            and not start_point_found
        ):

            # print("start at " + str(i))
            start_point_found = True
            x = i
            time_buff = timestamps[i]
            continue

        if (
            intervall_i < 144
            and recorded_times_end[intervall_i] - recorded_times[intervall_i]
            < timestamps[i] - time_buff
            and start_point_found
        ) or (
            timestamps[i] - time_buff > 5.0
            and amps_prev - amps_next > difference
            and start_point_found
        ):
            start_point_found = False
            x2 = i
            energy_analyzed[intervall_i] = ws[x2] - ws[x]
            # print(wattage[x + 100])
            wattage_analyzed[intervall_i] = np.mean(wattage[x : x2 + 1]).tolist()
            intervall_i += 1
            rect = plt.Rectangle(
                (timestamps[x], 0.35),
                timestamps[x2] - timestamps[x],
                0.5,
                linewidth=1,
                edgecolor="r",
                facecolor="none",
            )
            plt.gca().add_patch(rect)

    print(f"Length of analyzed values: {len(energy_analyzed)} {len(wattage_analyzed)}")

    print(energy_analyzed)
    print(wattage_analyzed)

    for kem in kems:
        for virt in ["unikraft", "docker", "native"]:
            for mode in ["keygen", "encaps", "decaps"]:
                if kem == "ECDHE" and mode == "decaps":
                    continue
                ener = energy_analyzed[data_json[virt]["kem"][kem][mode]["order"]]
                data_json[virt]["kem"][kem][mode]["mean_mj"] = f"{1000 * ener:.2f}"
                wat = wattage_analyzed[data_json[virt]["kem"][kem][mode]["order"]]
                data_json[virt]["kem"][kem][mode]["mean_mw"] = f"{1000 * wat:.2f}"

    for sig in sigs:
        for virt in ["unikraft", "docker", "native"]:
            for mode in ["keygen", "encaps", "decaps"]:
                ener = energy_analyzed[data_json[virt]["sig"][sig][mode]["order"]]
                data_json[virt]["sig"][sig][mode]["mean_mj"] = f"{1000 * ener:.2f}"
                wat = wattage_analyzed[data_json[virt]["sig"][sig][mode]["order"]]
                data_json[virt]["sig"][sig][mode]["mean_mw"] = f"{1000 * wat:.2f}"

    with open(
        os.path.join(
            SCRIPT_DIR,
            "results_primitives_power"
            + datetime.today().strftime("%Y-%m-%d_%H-%M-%S")
            + ".json",
        ),
        "w",
    ) as f:
        json.dump(data_json, f)

    plt.title("Wattage")
    plt.xlabel("Time (seconds)")
    plt.ylabel("Wattage")

    plt.yticks(np.arange(0, 10, 1))
    # plt.xticks(np.arange(0, 1500, 1))

    plt.grid()
    # plt.legend()
    plt.tight_layout()

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


def timestamp(time_string):
    # time_string = "08:30:18.424587"
    time_object = datetime.strptime(time_string, "%H:%M:%S.%f")
    today_date = datetime.now().date()
    combined_datetime = datetime.combine(today_date, time_object.time())
    unix_timestamp = combined_datetime.timestamp()
    # print(unix_timestamp)
    return unix_timestamp


if __name__ == "__main__":
    main()
