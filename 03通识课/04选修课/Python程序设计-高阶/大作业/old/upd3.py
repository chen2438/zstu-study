import torch
import torch.nn as nn
import torch.optim as optim

# 检查是否有可用的GPU，如果没有，则使用CPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# 数据准备
# 输入：年份和直播电商市场规模
# 输出：线下零售额
X = torch.tensor(
    [[2018, 1354], [2019, 4437], [2020, 12850], [2021, 23615], [2022, 35000]],
    dtype=torch.float,
).to(device)
y = (
    torch.tensor([290922, 305325, 274380, 309939, 301880], dtype=torch.float)
    .view(-1, 1)
    .to(device)
)


# 定义一个简单的全连接神经网络
class SimpleNN(nn.Module):
    def __init__(self):
        super(SimpleNN, self).__init__()
        self.fc1 = nn.Linear(2, 10)  # 输入层到隐藏层
        self.fc2 = nn.Linear(10, 1)  # 隐藏层到输出层

    def forward(self, x):
        x = torch.relu(self.fc1(x))
        x = self.fc2(x)
        return x


# 实例化模型，定义损失函数和优化器
model = SimpleNN().to(device)
criterion = nn.MSELoss()
optimizer = optim.Adam(model.parameters(), lr=0.001)

# 训练模型
epochs = 5000
for epoch in range(epochs):
    # 前向传播
    outputs = model(X)
    loss = criterion(outputs, y)

    # 反向传播和优化
    optimizer.zero_grad()
    loss.backward()
    optimizer.step()

    # 每1000个epoch打印一次损失
    if (epoch + 1) % 1000 == 0:
        print(f"Epoch [{epoch+1}/{epochs}], Loss: {loss.item():.4f}")

# 使用模型进行预测
predicted = model(X).detach().cpu().numpy()
print(predicted)
