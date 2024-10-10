import pandas as pd
from pmdarima import auto_arima
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号 #有中文出现的情况，需要u'内容'

# 从Excel文件读取数据
df1 = pd.read_excel('网上零售额.xlsx', header=None, names=['月份', '值'])

# 将月份转换为pandas的日期格式
df1['月份'] = pd.to_datetime(df1['月份'], format='%Y年%m月')

# 设置月份为索引
df1.set_index('月份', inplace=True)

# 使用auto_arima自动寻找最佳ARIMA模型
model = auto_arima(df1['值'], seasonal=True, m=12)
print(model.summary())

# 拟合模型
model.fit(df1['值'])

# 进行预测
forecast = model.predict(n_periods=13)

# 创建正确的预测日期索引（每个月的第一天）
forecast_index = pd.date_range(start=df1.index[-1] + pd.offsets.MonthBegin(1), periods=13, freq='MS')

# 创建预测数据的DataFrame
forecast_df1 = pd.DataFrame({'预测': forecast}, index=forecast_index)

# 打印forecast_df以进行调试
print(forecast_df1)

# 创建包含历史和预测数据的DataFrame
combined_index = df1.index.append(forecast_index)
combined_values = pd.concat([df1['值'], pd.Series(forecast, index=forecast_index)])
combined_df = pd.DataFrame({'值': combined_values}, index=combined_index)

# 将合并后的数据导出到Excel
combined_df.to_excel('历史+预测-网上零售额合并后的数据.xlsx')

# 可视化历史数据和预测数据
plt.figure(figsize=(10, 5))
plt.plot(df1, label='历史数据')
plt.plot(forecast_df1, label='预测', color='red')
plt.title("2024年网上零售额预测")
plt.xlabel('日期')
plt.ylabel('单位（亿元）')
plt.legend()
plt.show()

df2 = pd.read_excel('零售总额.xlsx', header=None, names=['月份', '值'])

# 将月份转换为pandas的日期格式
df2['月份'] = pd.to_datetime(df2['月份'], format='%Y年%m月')

# 设置月份为索引
df2.set_index('月份', inplace=True)

# 使用auto_arima自动寻找最佳ARIMA模型
model = auto_arima(df2['值'], seasonal=True, m=12)

# 拟合模型
model.fit(df2['值'])

# 进行预测
forecast = model.predict(n_periods=13)

# 创建正确的预测日期索引（每个月的第一天）
forecast_index = pd.date_range(start=df2.index[-1] + pd.offsets.MonthBegin(1), periods=13, freq='MS')

# 创建预测数据的DataFrame
forecast_df2 = pd.DataFrame({'预测': forecast}, index=forecast_index)

# 打印forecast_df以进行调试
print(forecast_df2)

# 创建包含历史和预测数据的DataFrame
combined_index = df2.index.append(forecast_index)
combined_values = pd.concat([df2['值'], pd.Series(forecast, index=forecast_index)])
combined_df = pd.DataFrame({'值': combined_values}, index=combined_index)

# 将合并后的数据导出到Excel
combined_df.to_excel('历史+预测-社会零售总额合并后的数据.xlsx')
# 可视化历史数据和预测数据
plt.figure(figsize=(10, 5))
plt.plot(df2, label='历史数据')
plt.plot(forecast_df2, label='预测', color='red')
plt.title("2024年零售总额预测")
plt.xlabel('日期')
plt.ylabel('单位（亿元）')
plt.legend()
plt.show()


# 读取数据
online_sales = pd.read_excel('历史+预测-网上零售额合并后的数据.xlsx', header=0, names=['月份', '网上零售额'])
total_sales = pd.read_excel('历史+预测-社会零售总额合并后的数据.xlsx', header=0, names=['月份', '零售总额'])
# print(online_sales)


# 合并数据
merged_data = pd.merge(online_sales, total_sales, on='月份', how='inner')

print(merged_data)

# 计算占比
merged_data['Online_Percentage'] = merged_data['网上零售额'] / merged_data['零售总额'] * 100
merged_data['线下零售额'] = merged_data['零售总额'] - merged_data['网上零售额']
merged_data.to_excel('合并后的数据.xlsx', index=False)
# 绘制图表
plt.figure(figsize=(10, 6))
plt.plot(merged_data['月份'], merged_data['Online_Percentage'], marker='o')
plt.xlabel('月份')
plt.ylabel('百分比 (%)')
plt.title('网上零售额占社会零售总额百分比')
plt.grid(True)
plt.show()

