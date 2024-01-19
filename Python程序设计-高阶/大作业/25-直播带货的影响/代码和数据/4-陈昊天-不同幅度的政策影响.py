import matplotlib
import matplotlib.pyplot as plt
import numpy as np

matplotlib.rcParams["font.family"] = "Songti SC"

physical_store_sales = np.array(
    [
        290922,
        305325,
        274380,
        309939,
        301880,
        304448,
        307101,
        309754,
        312407,
        315060,
        317713,
    ]
)
live_streaming_sales = np.array(
    [
        1354,
        4437,
        12850,
        23615,
        34879,
        45657,
        57591,
        71848,
        89328,
        110940,
        137729,
    ]
)

years = len(physical_store_sales)
simulations = 10
reduction_percentages = np.linspace(0.05, 0.50, 11)  # 比例，等差

simulation_results = np.zeros((len(reduction_percentages), years))

for i, reduction in enumerate(reduction_percentages):
    for j in range(simulations):
        # 每年减少的市场规模
        reduction_amounts = live_streaming_sales * reduction
        # 实体店市场增加的规模
        adjusted_physical_store_sales = physical_store_sales + reduction_amounts

        simulation_results[i] += adjusted_physical_store_sales

    # 均值
    simulation_results[i] /= simulations


plt.figure(figsize=(12, 6))
for i, reduction in enumerate(reduction_percentages):
    plt.plot(
        range(2018, 2018 + years),
        simulation_results[i],
        label=f"{reduction*100:.1f}%",
    )
plt.title("不同幅度的政策影响对实体店规模的反应")
plt.xlabel("年份")
plt.ylabel("实体店市场规模")
plt.legend()
plt.ylim(100000, 400000)
plt.grid(True)
plt.show()
