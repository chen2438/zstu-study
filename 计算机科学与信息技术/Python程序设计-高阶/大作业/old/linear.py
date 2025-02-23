import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

matplotlib.rcParams["font.family"] = "Songti SC"

# 准备数据
years = np.array([2018, 2019, 2020, 2021, 2022, 2023]).reshape(-1, 1)
market_share_darenbo = np.array([67.1, 69.5, 67.9, 56.8, 52.7, 50.2]).reshape(-1, 1)

# 训练线性回归模型
model = LinearRegression()
model.fit(years, market_share_darenbo)

# 使用模型进行未来5年的预测
future_years = np.array([2024, 2025, 2026, 2027, 2028]).reshape(-1, 1)
predicted_shares = model.predict(future_years)

# 绘制折线图
plt.figure(figsize=(10, 6))
plt.plot(years, market_share_darenbo, label="历史数据", marker="o")
plt.plot(future_years, predicted_shares, label="预测数据", marker="x", linestyle="--")
plt.title("达人播市场占比预测 (2018-2028)")
plt.xlabel("年份")
plt.ylabel("市场占比 (%)")
plt.legend()
plt.grid(True)
plt.show()
