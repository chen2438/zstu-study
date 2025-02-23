import tkinter as tk
from tkinter import Scrollbar

# 创建GUI窗口
root = tk.Tk()
root.title("分析结果")

# 从文本文件中读取分析结果
file_path = './output.txt'
with open(file_path, "r") as file:
    result_text = file.read()

# 创建文本框来显示分析结果
text_box = tk.Text(root, wrap="word")
text_box.insert("1.0", result_text)
text_box.pack(side="left", fill="both", expand=True)

# 创建一个垂直滚动条并绑定到文本框
scrollbar = Scrollbar(root, command=text_box.yview)
scrollbar.pack(side="right", fill="y")
text_box.config(yscrollcommand=scrollbar.set)

# 运行GUI
root.mainloop()