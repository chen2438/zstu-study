import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.impute import KNNImputer
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix

# 1.数据加载及预处理

# 加载数据
df = pd.read_csv("data_lib1.csv")

# 展示头部数据
print("头部数据")
print(df.head())

# 展示尾部数据
print("尾部数据")
print(df.tail())

# 数据类型和完整性确认
print("数据类型和完整性确认")
print(df.info())

# （1）检查是否有重复数据并删除
df = df.drop_duplicates()

# （2）检查是否存在缺失数据以及各特征缺失数据的比例
print("各特征缺失数据的比例")
print(df.isnull().mean())

# 使用KNNImputer根据特征间的关系填充缺失数据
imputer = KNNImputer(n_neighbors=5)

# （3）将字符串和布尔字符转换成整数
# 类别标签'diagnosis'是字符串需要被转化为整数，其余为数值特征
df["diagnosis"] = df["diagnosis"].map(
    {"M": 1, "B": 0}
)  # M:1 for malignant, B:0 for benign
df.iloc[:, 2:] = imputer.fit_transform(df.iloc[:, 2:])  # 使用KNN填充缺失值，不包括ID和诊断结果

# （4）尝试分析特征之间的关系，将其可视化
# sns.pairplot(df.iloc[:, 1:6], hue="diagnosis")
# plt.show()
# sns.pairplot(df.iloc[:, [1] + list(range(6, 10))], hue="diagnosis")
# plt.show()

# 预处理数据保存
df.to_csv("data_lib1_preprocessed.csv", index=False)

# 2.数据集分割

# 分离特征和标签
X = df.iloc[:, 2:10]  # 特征列
y = df["diagnosis"]  # 标签列

# 分割数据集
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=42
)

# 3.模型构建、训练、评估

# 决策树模型
dt_model = DecisionTreeClassifier(random_state=42)
dt_model.fit(X_train, y_train)
y_pred_dt = dt_model.predict(X_test)
accuracy_dt = accuracy_score(y_test, y_pred_dt)
print("Decision Tree Accuracy: {:.2f}%".format(accuracy_dt * 100))
print(classification_report(y_test, y_pred_dt))

# 支持向量机模型
svm_model = SVC(random_state=42)
svm_model.fit(X_train, y_train)
y_pred_svm = svm_model.predict(X_test)
accuracy_svm = accuracy_score(y_test, y_pred_svm)
print("SVM Accuracy: {:.2f}%".format(accuracy_svm * 100))
print(classification_report(y_test, y_pred_svm))

# 随机森林模型
rf_model = RandomForestClassifier(random_state=42)
rf_model.fit(X_train, y_train)
y_pred_rf = rf_model.predict(X_test)
accuracy_rf = accuracy_score(y_test, y_pred_rf)
print("Random Forest Accuracy: {:.2f}%".format(accuracy_rf * 100))
print(classification_report(y_test, y_pred_rf))


# 可视化预测结果
def plot_confusion_matrix(y_true, y_pred, title):
    cm = confusion_matrix(y_true, y_pred)
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues")
    plt.title(title)
    plt.xlabel("Predicted")
    plt.ylabel("Actual")
    plt.show()


plot_confusion_matrix(y_test, y_pred_dt, "Confusion Matrix - Decision Tree")
plot_confusion_matrix(y_test, y_pred_svm, "Confusion Matrix - SVM")
plot_confusion_matrix(y_test, y_pred_rf, "Confusion Matrix - Random Forest")

# 模型性能对比
models = ["Decision Tree", "SVM", "Random Forest"]
accuracies = [accuracy_dt, accuracy_svm, accuracy_rf]
plt.bar(models, accuracies)
plt.ylabel("Accuracy")
plt.title("Model Comparison")
plt.show()
