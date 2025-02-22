import matplotlib.pyplot as plt

# 读取C++程序输出的文件
physical_pages = []
page_fault_rates = []
with open("page_fault_rates.txt", "r") as file:
    next(file)  # 跳过标题行
    for line in file:
        data = line.split()
        physical_pages.append(int(data[0]))
        page_fault_rates.append(float(data[1]))

# 绘制曲线图
plt.plot(physical_pages, page_fault_rates, marker='o')
plt.title('Physical Page Number vs Page Fault Rate')
plt.xlabel('Physical Page Number')
plt.ylabel('Page Fault Rate')
plt.xticks(range(1, 19))
plt.grid(True)
plt.savefig('page_fault_rates.png')  # 保存图像
plt.show()
