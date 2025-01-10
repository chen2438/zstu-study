import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
import torch
import torch.nn as nn
from torch.autograd import Variable

# 数据加载
df = pd.read_csv("data.csv")
df.set_index("项目", inplace=True)
df = df.transpose()

# 数据预处理
data = df["直播电商市场规模"].values
data = data.reshape(-1, 1)

scaler = MinMaxScaler(feature_range=(0, 1))
data_scaled = scaler.fit_transform(data)


def create_dataset(dataset, look_back=1):
    X, Y = [], []
    for i in range(len(dataset) - look_back - 1):
        a = dataset[i : (i + look_back), 0]
        X.append(a)
        Y.append(dataset[i + look_back, 0])
    return np.array(X), np.array(Y)


look_back = 1
X, Y = create_dataset(data_scaled, look_back)

# 分割数据集
train_size = int(len(X) * 0.67)
test_size = len(X) - train_size
X_train, X_test = X[0:train_size], X[train_size : len(X)]
Y_train, Y_test = Y[0:train_size], Y[train_size : len(Y)]

# 转换为PyTorch张量
X_train = torch.Tensor(np.array(X_train))
X_test = torch.Tensor(np.array(X_test))
Y_train = torch.Tensor(np.array(Y_train))
Y_test = torch.Tensor(np.array(Y_test))

# 调整形状 [样本数, 时间步, 特征数]
X_train = torch.reshape(X_train, (X_train.shape[0], 1, X_train.shape[1]))
X_test = torch.reshape(X_test, (X_test.shape[0], 1, X_test.shape[1]))


# 定义LSTM模型
class LSTM(nn.Module):
    def __init__(self, input_size=1, hidden_layer_size=100, output_size=1):
        super().__init__()
        self.hidden_layer_size = hidden_layer_size
        self.lstm = nn.LSTM(input_size, hidden_layer_size)
        self.linear = nn.Linear(hidden_layer_size, output_size)
        self.hidden_cell = (
            torch.zeros(1, 1, self.hidden_layer_size),
            torch.zeros(1, 1, self.hidden_layer_size),
        )

    def forward(self, input_seq):
        lstm_out, self.hidden_cell = self.lstm(
            input_seq.view(len(input_seq), 1, -1), self.hidden_cell
        )
        predictions = self.linear(lstm_out.view(len(input_seq), -1))
        return predictions[-1]


# 实例化模型
model = LSTM()
loss_function = nn.MSELoss()
optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

# 训练模型
epochs = 150
for i in range(epochs):
    for seq, labels in zip(X_train, Y_train):
        optimizer.zero_grad()
        model.hidden_cell = (
            torch.zeros(1, 1, model.hidden_layer_size),
            torch.zeros(1, 1, model.hidden_layer_size),
        )

        y_pred = model(seq)

        # 修改labels的形状
        labels = labels.unsqueeze(0)

        single_loss = loss_function(y_pred, labels)
        single_loss.backward()
        optimizer.step()

    if i % 25 == 1:
        print(f"epoch: {i:3} loss: {single_loss.item():10.8f}")

print(f"epoch: {i:3} loss: {single_loss.item():10.10f}")

# 预测
model.eval()
test_outputs = []
for seq in X_test:
    with torch.no_grad():
        model.hidden = model.hidden_cell

        # model.hidden = (
        #     torch.zeros(1, 1, model.hidden_layer_size),
        #     torch.zeros(1, 1, model.hidden_layer_size),
        # )
        test_outputs.append(model(seq).item())

# 反归一化预测结果
test_outputs = scaler.inverse_transform(np.array(test_outputs).reshape(-1, 1))
Y_train_reshaped = Y_train.numpy().reshape(-1, 1)
Y_train_inverse = scaler.inverse_transform(Y_train_reshaped)

# 可视化结果
plt.figure(figsize=(15, 6))
plt.plot(scaler.inverse_transform(data_scaled), label="Original Data")
plt.plot(
    np.arange(look_back, len(Y_train_inverse) + look_back),
    Y_train_inverse,
    label="Training Data",
)


plt.plot(
    np.arange(len(Y_train) + 2 * look_back, len(Y_train) + len(Y_test) + 2 * look_back),
    test_outputs,
    label="Predictions",
)
plt.legend()
plt.show()
