import matplotlib
import matplotlib.pyplot as plt

matplotlib.rcParams["font.family"] = "Songti SC"

# 数据
years = range(2018, 2029)
physical_store_size = [
    290922,
    305325,
    274380,
    309939,
    301880,
    304448.0,
    307101.0,
    309754.0,
    312407.0,
    315060.0,
    317713.0,
]
live_commerce_size = [
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
influencer_market_size = [
    908.534,
    3083.715,
    8725.150000000001,
    13413.32,
    18381.233,
    22919.814,
    26549.451,
    30124.860528,
    33727.751615999994,
    37259.97558,
    40512.021247,
]

# 创建折线图
plt.figure(figsize=(10, 6))

# 绘制三条线
plt.plot(years, physical_store_size, label="实体店", color="blue")
plt.plot(years, live_commerce_size, label="直播电商", color="green")
plt.plot(years, influencer_market_size, label="头部主播", color="red")

# 设置标题和标签
plt.title("实体店、直播电商和头部主播的份额对比")
plt.xlabel("年份")
plt.ylabel("市场规模")
plt.xticks(years)
plt.legend()

# 显示图表
plt.grid(True)
plt.tight_layout()
plt.show()
