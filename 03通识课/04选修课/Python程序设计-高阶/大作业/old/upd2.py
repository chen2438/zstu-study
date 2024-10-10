import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt

# 1. 数据
years = torch.tensor([2018, 2019, 2020, 2021, 2022], dtype=torch.float32)
data = torch.tensor(
    [
        [100, 400, 5000, 8000, 15000],  # 抖音GMV
        [300, 1500, 3812, 6500, 9000],  # 快手GMV
        [1000, 2000, 4000, 5000, 7700],  # 淘宝GMV
        [0.3545, 0.5684, 0.7502, 1.59, 1.87],  # 直播电商企业数
        [1354, 4437, 12850, 23615, 35000],  # 直播电商市场规模
        [2.2, 2.5, 3.72, 4.3, 4.73],  # 直播电商用户规模
        [296.95, 1775, 2822.58, 4639.68, 7399.58],  # 直播电商人均年消费额
    ],
    dtype=torch.float32,
)


# 2. 模型
class MLP(nn.Module):
    def __init__(self):
        super(MLP, self).__init__()
        self.layers = nn.Sequential(
            nn.Linear(1, 64),
            nn.ReLU(),
            nn.Linear(64, 64),
            nn.ReLU(),
            nn.Linear(64, 7),  # 7个预测输出
        )

    def forward(self, x):
        return self.layers(x)


model = MLP()

# 3. 损失函数和优化器
criterion = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

# 4. 训练模型
for epoch in range(1000):  # 1000个epoch
    for i in range(years.shape[0]):
        inputs = years[i].reshape(-1, 1)
        targets = data[:, i]

        # 前向传播
        outputs = model(inputs)
        loss = criterion(outputs, targets)

        # 后向传播和优化
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

    if epoch % 100 == 0:  # 每100个epoch打印一次损失值
        print(f"Epoch [{epoch+1}/1000], Loss: {loss.item():.4f}")

# 5. 预测
future_years = torch.tensor([2023, 2024, 2025], dtype=torch.float32).reshape(-1, 1)
predicted = model(future_years).T  # 转置预测数据

# 6. 绘制图表
all_years = torch.cat((years, future_years.reshape(-1)), 0)
all_data = torch.cat((data, predicted.detach()), 1).numpy()

# 每个指标一个图
labels = [
    "Douyin GMV",
    "kuaishou GMV",
    "taobao GMV",
    "直播电商企业数",
    "直播电商市场规模",
    "直播电商用户规模",
    "直播电商人均年消费额",
]
for i in range(data.shape[0]):
    plt.figure()
    plt.plot(all_years, all_data[i, :], marker="o")
    plt.title(labels[i])
    plt.xlabel("Year")
    plt.ylabel("Value")
    plt.grid(True)
    plt.show()
