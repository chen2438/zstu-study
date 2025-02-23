我第一次实验时，采用的二分类的代码来实验，但是复现效果不佳，于是将多分类的模型设计来改善原来的部分代码，但由于二分类的代码和多分类的代码混合，模型效果依旧不佳



这次实验让我深刻认识到二分类与多分类任务在设计逻辑上的差异，以及代码一致性的重要性。



下面是我的文件说明：

- cataract-prediction-using-vgg19-test.ipynb：我的实验代码，其中数据处理是二分类，模型设计是多分类，模型效果不佳，预测准确率将近60%
- multi_class_cataract_prediction.py：经GPT修改后的多分类代码，未经实验
- vgg19.h5：我的实验`cataract-prediction-using-vgg19-test.ipynb`输出模型，将其放在相同目录，能减少实验耗时

- full_df.csv和archive.zip：kaggle实验数据，由于文件较大，请在官网下载

