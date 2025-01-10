import matplotlib.pyplot as plt
import numpy as np

# 设置中文字体
plt.rcParams["font.sans-serif"] = ["Microsoft YaHei"]  # 设置中文字体
plt.rcParams["axes.unicode_minus"] = False  # 正常显示负号

# 1. 公众对国家安全教育重要性的认知 - 饼图
labels_1 = ["非常重要", "重要", "一般", "不太重要", "完全不重要"]
sizes_1 = [50, 35, 10, 4, 1]
plt.figure(figsize=(6, 6))
plt.pie(
    sizes_1,
    labels=labels_1,
    autopct="%1.1f%%",
    startangle=90,
    colors=["#ff9999", "#66b3ff", "#99ff99", "#ffcc99", "#c2c2f0"],
)
plt.title("公众对国家安全教育重要性的认知")
plt.axis("equal")  # 确保饼图是圆形
plt.show()

# 2. 公众对《国家安全法》熟悉程度 - 条形图
labels_2 = ["很熟悉", "听说过但不熟悉", "没有听过"]
sizes_2 = [18, 60, 22]
plt.figure(figsize=(8, 6))
plt.barh(labels_2, sizes_2, color="#66b3ff")
plt.xlabel("百分比 (%)")
plt.title("公众对《国家安全法》熟悉程度")
plt.show()

# 3. 公众对国家安全形势的了解程度 - 堆积条形图
labels_3 = ["非常了解", "了解一些", "听说过但不了解", "完全不了解"]
sizes_3 = [10, 40, 30, 20]
cumulative = np.cumsum(sizes_3)
plt.figure(figsize=(8, 6))
plt.bar(labels_3, sizes_3, color="#ff9999", edgecolor="black")
for i in range(1, len(cumulative)):
    plt.bar(
        labels_3[i],
        sizes_3[i],
        bottom=cumulative[i - 1],
        color="#66b3ff",
        edgecolor="black",
    )
plt.xlabel("了解程度")
plt.ylabel("百分比 (%)")
plt.title("公众对国家安全形势的了解程度")
plt.show()

# 4. 公众对高质量发展与国家安全的关联性认知 - 饼图
labels_4 = [
    "高质量发展是国家安全的基础",
    "高质量发展可以增强国家安全",
    "高质量发展与国家安全无关",
    "不清楚",
]
sizes_4 = [25, 50, 10, 15]
plt.figure(figsize=(6, 6))
plt.pie(
    sizes_4,
    labels=labels_4,
    autopct="%1.1f%%",
    startangle=90,
    colors=["#ffcc99", "#99ff99", "#ff9999", "#c2c2f0"],
)
plt.title("公众对高质量发展与国家安全的关联性认知")
plt.axis("equal")
plt.show()

# 5. 公众对高水平安全与高质量发展的关系认知 - 饼图
labels_5 = [
    "高水平安全是高质量发展的前提",
    "高水平安全可以保障高质量发展",
    "高水平安全与高质量发展无关",
    "不清楚",
]
sizes_5 = [30, 45, 10, 15]
plt.figure(figsize=(6, 6))
plt.pie(
    sizes_5,
    labels=labels_5,
    autopct="%1.1f%%",
    startangle=90,
    colors=["#ffcc99", "#66b3ff", "#ff9999", "#c2c2f0"],
)
plt.title("公众对高水平安全与高质量发展的关系认知")
plt.axis("equal")
plt.show()

# 6. 公众对平衡发展与安全关系的看法 - 条形图
labels_6 = [
    "优先发展经济",
    "优先保障安全",
    "同等重要，需要平衡",
    "不清楚",
]
sizes_6 = [10, 5, 70, 15]
plt.figure(figsize=(8, 6))
plt.barh(labels_6, sizes_6, color="#66b3ff")
plt.xlabel("百分比 (%)")
plt.title("公众对平衡发展与安全关系的看法")
plt.show()

# 7. 公众对国家安全教育案例了解程度 - 堆积条形图
labels_7 = ["了解很多", "了解一些", "听说过，但不了解具体案例", "完全没听说过"]
sizes_7 = [5, 20, 50, 25]
cumulative_7 = np.cumsum(sizes_7)
plt.figure(figsize=(8, 6))
plt.bar(labels_7, sizes_7, color="#ff9999", edgecolor="black")
for i in range(1, len(cumulative_7)):
    plt.bar(
        labels_7[i],
        sizes_7[i],
        bottom=cumulative_7[i - 1],
        color="#66b3ff",
        edgecolor="black",
    )
plt.xlabel("了解程度")
plt.ylabel("百分比 (%)")
plt.title("公众对国家安全教育案例了解程度")
plt.show()

# 8. 公众对案例学习帮助程度的看法 - 条形图
labels_8 = ["非常有帮助", "有帮助", "一般", "没有帮助", "不清楚"]
sizes_8 = [39, 36, 16, 5, 4]
plt.figure(figsize=(8, 6))
plt.barh(labels_8, sizes_8, color="#66b3ff")
plt.xlabel("百分比 (%)")
plt.title("公众对案例学习帮助程度的看法")
plt.show()
