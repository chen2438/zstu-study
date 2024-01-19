import torch
import torch.nn as nn
import numpy as np
import matplotlib
import matplotlib.pyplot as plt

matplotlib.rcParams["font.family"] = "Songti SC"

# 准备数据
years = torch.tensor([2018, 2019, 2020, 2021, 2022, 2023]).float()
talent_broadcast = torch.tensor([67.1, 69.5, 67.9, 56.8, 52.7, 50.2]).float()

# 归一化处理
years_normalized = (years - years.mean()) / years.std()
# print(years_normalized)
talent_broadcast_normalized = (
    talent_broadcast - talent_broadcast.mean()
) / talent_broadcast.std()


# 线性模型
class LinearModel(nn.Module):
    def __init__(self):
        super(LinearModel, self).__init__()
        self.linear = nn.Linear(1, 1)  # 线性层

    def forward(self, x):  # 前向传播
        return self.linear(x)


model = LinearModel()

# 损失函数和优化器
criterion = nn.MSELoss()  # 均方误差
optimizer = torch.optim.Adam(model.parameters(), lr=0.01)  # Adam 优化器, 学习率 0.01

# from torch.utils.tensorboard import SummaryWriter

# writer = SummaryWriter("runs/linear_model")
# sample_input = torch.tensor([[0.0]])  # 使用归一化后的输入形式
# writer.add_graph(model, sample_input)
# writer.close()

# 训练模型
epochs = 2000
loss_values = []  # 损失
for epoch in range(epochs):
    model.train()
    optimizer.zero_grad()  # 清除旧的梯度

    # 前向传播
    outputs = model(years_normalized.unsqueeze(1))
    loss = criterion(outputs, talent_broadcast_normalized.unsqueeze(1))

    # 反向传播
    loss.backward()  # 计算梯度
    optimizer.step()  # 更新权重

    # 记录损失值
    loss_values.append(loss.item())

    # if epoch % 100 == 0:
    # print(f"Epoch: {epoch+1}/{epochs}, Loss: {loss.item()}")


# 预测未来5年的市场占比
future_years = torch.tensor([2024, 2025, 2026, 2027, 2028]).float()
future_years_normalized = (future_years - years.mean()) / years.std()

model.eval()  # 评估
with torch.no_grad():
    future_predictions = model(future_years_normalized.unsqueeze(1)).flatten()
    # 反归一化
    future_predictions = (
        future_predictions * talent_broadcast.std() + talent_broadcast.mean()
    )

print(talent_broadcast)
print(future_predictions)

# 绘制折线图
plt.figure(figsize=(10, 6))
plt.plot(years, talent_broadcast, label="历史数据", marker="o")
plt.plot(future_years, future_predictions, label="预测数据", marker="x", linestyle="--")
plt.xlabel("年份")
plt.ylabel("市场占比 (%)")
plt.title("达人播市场占比预测 (2018-2028)")
plt.legend()
plt.grid(True)
plt.show()
