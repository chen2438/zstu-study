import torch
import torch.nn as nn
import pandas as pd
from sklearn.preprocessing import StandardScaler
import numpy as np


# 示例数据
data = {
    "year": [2018, 2019, 2020, 2021, 2022],
    "GMV": [100, 400, 5000, 8000, 15000],  # 示例：抖音GMV
}

df = pd.DataFrame(data)

# 数据预处理
scaler = StandardScaler()
df_scaled = scaler.fit_transform(df)

# 分离特征和目标
X = torch.tensor(df_scaled[:, 0:1], dtype=torch.float32)
y = torch.tensor(df_scaled[:, 1], dtype=torch.float32)

# 定义模型
model = nn.Linear(1, 1)

# 损失函数和优化器
criterion = nn.MSELoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.01)

# 训练模型
epochs = 100
for epoch in range(epochs):
    model.train()
    optimizer.zero_grad()

    # 前向传播
    y_pred = model(X)

    # 计算损失
    loss = criterion(y_pred, y.view(-1, 1))

    # 反向传播
    loss.backward()
    optimizer.step()

    if epoch % 10 == 0:
        print(f"Epoch {epoch}, Loss: {loss.item()}")

# 预测
model.eval()
predict_data = [[2023, 0], [2024, 0], [2025, 0]]  # 添加虚拟GMV值
predict_data_scaled = scaler.transform(predict_data)
predict_years_tensor = torch.tensor(predict_data_scaled[:, 0:1], dtype=torch.float32)
predictions = model(predict_years_tensor)
# print(predictions.detach().numpy())

# 将预测结果转换回原始尺度
original_scale_predictions = scaler.inverse_transform(
    np.concatenate(
        (predict_years_tensor.detach().numpy(), predictions.detach().numpy()), axis=1
    )
)
print(original_scale_predictions[:, 1])  # 打印原始尺度的预测GMV


import matplotlib.pyplot as plt

# 原始数据
original_years = df["year"].values
original_gmv = df["GMV"].values

# 预测数据
predicted_years = [2023, 2024, 2025]
predicted_gmv = original_scale_predictions[:, 1]  # 从之前的输出中获取

# 绘制折线图
plt.figure(figsize=(10, 6))
plt.plot(original_years, original_gmv, label="Original GMV", marker="o")
plt.plot(predicted_years, predicted_gmv, label="Predicted GMV", marker="x")

# 添加标题和标签
plt.title("GMV from 2018 to 2025")
plt.xlabel("Year")
plt.ylabel("GMV")
plt.xticks(list(range(2018, 2026)))  # 设置x轴刻度
plt.legend()

# 显示图表
plt.show()
