def count_function_words(file_path):
    with open(file_path, "r", encoding="utf-8") as file:
        text = file.read()

    # 虚词列表
    function_words = [
        "之",
        "其",
        "或",
        "亦",
        "方",
        "于",
        "即",
        "皆",
        "因",
        "仍",
        "故",
        "尚",
        "呢",
        "了",
        "不",
        "乃",
        "呀",
        "吗",
        "啊",
        "把",
        "让",
        "向",
        "往",
        "在",
        "比",
        "好",
        "可",
        "便",
        "就",
        "还",
        "依",
        "只",
        "犹",
        "才",
        "早",
        "没",
        "吧",
        "过",
        "得",
        "地",
        "个",
        "著",
        "上",
        "着",
        "起",
        "来",
        "下",
        "去",
        "进",
        "回",
        "北",
        "南",
        "东",
        "西",
        "头",
        "里",
        "外",
        "前",
        "后",
        "内",
        "中",
        "间",
    ]

    total_words = len(text)
    function_words_count = 0

    for word in function_words:
        function_words_count += text.count(word)

    function_words_ratio = function_words_count / total_words

    return function_words_ratio


# 分别统计《水浒传》和《三国演义》的虚词比例
shuihu_ratio = count_function_words("shuihu.txt")
sanguo_ratio = count_function_words("sanguo.txt")

# 输出结果
print("《水浒传》虚词比例:", shuihu_ratio)
print("《三国演义》虚词比例:", sanguo_ratio)

# 比较虚词比例，判断风格是否相近
if abs(shuihu_ratio - sanguo_ratio) < 0.1:
    print("《水浒传》和《三国演义》风格相近")
else:
    print("《水浒传》和《三国演义》风格不相近")
