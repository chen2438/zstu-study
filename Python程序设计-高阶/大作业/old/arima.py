from statsmodels.tsa.arima.model import ARIMA
import pandas as pd
from statsmodels.graphics.tsaplots import plot_acf, plot_pacf
import numpy as np

# 准备数据
df = pd.DataFrame(
    {"Year": np.arange(2018, 2024), "Market_Share": market_share_darenbo.flatten()}
)

# 设置年份为索引
df.set_index("Year", inplace=True)

# 绘制自相关和偏自相关图来帮助确定ARIMA模型的参数
fig, ax = plt.subplots(1, 2, figsize=(12, 6))

plot_acf(df.Market_Share, ax=ax[0], title="自相关图")
plot_pacf(df.Market_Share, ax=ax[1], title="偏自相关图")

plt.show()

# 确定ARIMA模型的参数
# 这里我们使用一个简单的方法来确定参数，但在实际应用中可能需要更复杂的方法
p = 1  # 自回归项的阶数
d = 1  # 差分的阶数
q = 1  # 移动平均项的阶数

# 训练ARIMA模型
model = ARIMA(df.Market_Share, order=(p, d, q))
model_fit = model.fit()

# 预测未来5年
forecast = model_fit.forecast(steps=5)
forecast_years = np.arange(2024, 2029)

# 将预测结果与原始数据结合起来
combined_years = np.concatenate((df.index.values, forecast_years))
combined_shares = np.concatenate((df.Market_Share.values, forecast))

# 绘制包含预测的折线图
plt.figure(figsize=(10, 6))
plt.plot(combined_years, combined_shares, label="含预测数据", marker="o")
plt.title("达人播市场占比预测 (2018-2028) 使用ARIMA模型")
plt.xlabel("年份")
plt.ylabel("市场占比 (%)")
plt.grid(True)
plt.show()
