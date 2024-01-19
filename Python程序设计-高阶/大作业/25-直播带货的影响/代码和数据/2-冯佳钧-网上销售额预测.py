import tensorflow   as tf
import numpy        as np
#py环境采用3.9.18
x_data,y_data=[],[]

x_data=[
    2017.01,2017.02,2017.03,2017.04,2017.05,2017.06,2017.07,2017.08,2017.09,2017.10,2017.11,2017.12,
    2018.01,2018.02,2018.03,2018.04,2018.05,2018.06,2018.07,2018.08,2018.09,2018.10,2018.11,2018.12,
    2019.01,2019.02,2019.03,2019.04,2019.05,2019.06,2019.07,2019.08,2019.09,2019.10,2019.11,2019.12,
    2020.01,2020.02,2020.03,2020.04,2020.05,2020.06,2020.07,2020.08,2020.09,2020.10,2020.11,2020.12,
    2021.01,2021.02,2021.03,2021.04,2021.05,2021.06,2021.07,2021.08,2021.09,2021.10,2021.11,2021.12,
    2022.01,2022.02,2022.03,2022.04,2022.05,2022.06,2022.07,2022.08,2022.09,2022.10,2022.11,2022.12,
    2023.01,2023.02,2023.03,2023.04,2023.05,2023.06,2023.07
]
y_data=[
    4234,4346,5465,5135,5483,6410,5544,5894,6276,6563,8956,7445,
    6014,6257,7047,6474,6899,8119,7053,7332,7590,7754,10150,9376,
    7683,6300,8396,8060,8202,9520,7811,8421,8844,9070,12651,11366,
    6510,7202,8457,8529,9478,11325,9284,9541,9739,11210,14099,12227,
    8651,8936,10506,9545,10601,12894,9975,10119,10644,11894,14984,12135,
    9543,10015,10562,8572,10912,13403,10217,11071,11589,13658,15043,13268,
    10272,10272,12319,11245,12798,14715,11476
]
    
x_data,y_data=np.array(x_data),np.array(y_data)
y_data=y_data.astype('float32')

def split_data(seq,wth,fea):
    x,y=[],[]
    for i in range(len(seq)):
        idx_end=i+wth
        if idx_end>len(seq)-1:break
        x_seq,y_seq=seq[i:idx_end],seq[idx_end]
        x.append(x_seq),y.append(y_seq)
        x_proc,y_proc=np.array(x),np.array(y)
        x_proc=x_proc.reshape((x_proc.shape[0],x_proc.shape[1],fea))
    return x_proc,y_proc

x_data_split,y_data_split=split_data(y_data,12,1)

class CNN(tf.keras.Model):
    def __init__(self):
        super(CNN,self).__init__()
        self.c1=tf.keras.layers.Conv1D(filters=64,kernel_size=2,activation='relu',strides=1,padding='same')
        self.p1=tf.keras.layers.MaxPooling1D(pool_size=2,strides=None,padding='same')
        self.flatten=tf.keras.layers.Flatten()
        self.f1=tf.keras.layers.Dense(units=50,activation='relu',use_bias=True,kernel_initializer='glorot_uniform',bias_initializer='zeros',)
        self.f2=tf.keras.layers.Dense(units=1)
        
    def call(self,x):
        x=self.c1(x)
        x=self.p1(x)
        x=self.flatten(x)
        x=self.f1(x)
        y=self.f2(x)
        return y
    
model=CNN()
model.compile(optimizer='adam',loss='mse',metrics=['accuracy'])
model.fit(x_data_split,y_data_split,batch_size=32,epochs=10000)

num_pred=70

for i in range(num_pred):
    if(i==0):x_pred=[y_data[-12:]]
    else:x_pred=[np.append(x_pred[0][-11:],y_pred[0])]
    x_pred_split=np.expand_dims(x_pred,axis=-1)
    y_pred=model.predict(x_pred_split,verbose=0)
    y_data=np.append(y_data,y_pred[0][0])
    
print(y_data)

import matplotlib.pyplot as plt

time=[]
for i in range(len(y_data)): time.append(i)

data=y_data.tolist()

plt.plot(time,data)
plt.show()