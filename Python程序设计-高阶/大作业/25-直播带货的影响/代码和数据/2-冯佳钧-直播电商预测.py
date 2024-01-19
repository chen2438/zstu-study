import tensorflow   as tf
import numpy        as np

x_data,y_data=[],[]

x_data=[
    2017.0,2018.0,2019.0,2020.0,2021.0,2022.0,2023.0
]
y_data=[
    196.4,1354.1,4437.5,12850,23615.1,35000,45657
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

x_data_split,y_data_split=split_data(y_data,3,1)

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

num_pred=5

for i in range(num_pred):
    if(i==0):x_pred=[y_data[-3:]]
    else:x_pred=[np.append(x_pred[0][-2:],y_pred[0])]
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