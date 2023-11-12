import pandas as pd

# 读取Excel文件
df = pd.read_excel('course.xls')

# 打印每一行的内容
for index, row in df.iterrows():
    print(row)
