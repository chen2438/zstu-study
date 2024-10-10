---
description: 发布于 2024-01-08
categories:
- study
date: 2024-01-08
slug: computer-network-final-review
title: 计算机网络 期末复习
updated: 2024-01-10
tags: 
- study
- computer-network
copyright: false
---

# 计算机网络 期末复习

zstu 浙江理工大学 2023学年第1学期 计算机网络

```bash
考前关键词速记 不完全版

协议、接口、服务
协议：语法（格式）、语义（功能）、同步（顺序）
OSI：物理 数据链路 网络 传输 会话 表示 应用

物理：透明传输比特流
接口参数、电气特征

数据链路：将网络层的IP数据报组装成帧
组装成帧、差错控制、流量控制
PPP协议

网络层：把网络层分组从源端传到目的端
路由选择、差错控制、流量控制、拥塞控制
IP、ICMP、ARP、OSPF

传输层：负责两个进程之间传输报文段TCP或用户数据报UDP
差错控制、流量控制、拥塞控制
TCP、UDP

会话层：管理进程间的会话
表示层：处理两个通信系统中交换信息的方式
应用层：为网络应用提供访问OSI的手段

TCP/IP：网络接口层、网际层、传输层、应用层

香农定理：速率[bps]=带宽[Hz]*log2(1+S/N)
信噪比[dB]=10*log10(S/N)
S/N也是信噪比

物理层：中继器 集线器
数据链路层：交换机 隔离冲突域
网络层：路由器 隔离广播域

路由器：路由选择、存储转发

CRC：生成多项式,高阶在左,得到二进制G；
在二进制数据M右补len(G)-1个0；
列竖式，被除数是M，除数是G，异或运算
补的len(G)-1个0实际上就是余数的位置,余数计算完后填充之,接受端可以再次CRC检验是否差错，如有差错，余数不为0

MAC地址格式：12个十六进制，2个为一组：11-22-33-44-55-66
交换机能够划分VLAN

PPP 真数据-传输数据：7E:7D5E 7D:7D5D <20:7D<20

IP片偏移字段是片偏移字节/8

UDP面向报文，TCP面向字节流
UDP在IP的基础上提供复用和分用，对数据部分的差错检验
UDP首部8B，TCP首部20B

TCP连接建立
C->S SYN,seq=c
S->C SYN,ACK,seq=s,ack=c+1
C->S ACK,seq=c+1,ack=S+1

连接释放
C->S FIN,seq=c
S->C ACK,seq=s1,ack=c+1
S->C FIN,seq=s2,ack=c+1
C->S ACK,seq=c+1,ack=s2+1
C等待2MSL 2倍最长报文段寿命 关闭连接
S立即关闭连接

可靠传输：累计确认，超时重传，冗余确认重传（快重传）
流量控制：接收方设置 接收窗口rwnd

拥塞控制：发送方设置 拥塞窗口cwnd
慢开始：指数增大 拥塞避免：加法增大 网络拥塞：乘法减小并慢开始
快重传 快恢复

递归：本地->根->顶级->权限
迭代：本地->根 本地->顶级 本地->权限
```



## 第 1 章 计算机网络体系结构

### 1.1 概述

#### 1.1.1 概念

![image-20240103224020688](https://media.opennet.top/i/2024/01/03/10xi1sm-0.png)

![image-20240103224042222](https://media.opennet.top/i/2024/01/03/10xmcwa-0.png)

#### 1.1.2 组成

![image-20240103224122234](https://media.opennet.top/i/2024/01/03/10y407x-0.png)

#### 1.1.3 功能

![image-20240103224203192](https://media.opennet.top/i/2024/01/03/10yccom-0.png)

![image-20240103224213602](https://media.opennet.top/i/2024/01/03/10yf0b4-0.png)

#### 1.1.4 分类

按分布范围：广域网、城域网、局域网、个人局域网

按传输技术：广播式网络、点对点网络

按拓扑结构：总线形、星形、环形、网状

![image-20240103224512814](https://media.opennet.top/i/2024/01/03/1106ps7-0.png)

按使用者：公用网、专用网

按交换技术：电路交换、报文交换、分组交换

按传输介质：无线、有线

#### 1.1.5 标准化*

![image-20240103224708451](https://media.opennet.top/i/2024/01/03/111cw5p-0.png)

#### 1.1.6 性能指标

![image-20240103132922510](https://media.opennet.top/i/2024/01/03/lv5rd8-0.png)

![image-20240103132932912](https://media.opennet.top/i/2024/01/03/lv7vxl-0.png)

#### 题目

假设收发两端之间的传输距离为1000km，信号在媒体上的传播速率为2×10^8m/s。 数据长度为10^6bits,数据发送速率为1Mb/s。试计算发送时延和传播时延。

![image-20240103133254150](https://media.opennet.top/i/2024/01/03/lx4gy3-0.png)

![image-20240106094841155](https://media.opennet.top/i/2024/01/06/fk9ygk-0.png)

![Screenshot_2024_01_06_09_49_17_08_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/fkzyz3-0.jpg)

![image-20240106094856400](https://media.opennet.top/i/2024/01/06/fkdgvk-0.png)

![image-20240106094903872](https://media.opennet.top/i/2024/01/06/fkeuaw-0.png)

![Screenshot_2024_01_06_09_49_44_73_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/fl1vto-0.jpg)

![image-20240106095117092](https://media.opennet.top/i/2024/01/06/flom3f-0.png)

![Screenshot_2024_01_06_09_52_37_33_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/fnfakx-0.jpg)

![image-20240106095135002](https://media.opennet.top/i/2024/01/06/flse9u-0.png)

![Screenshot_2024_01_06_09_53_12_61_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/fnhco1-0.jpg)

![image-20240106095147617](https://media.opennet.top/i/2024/01/06/fm3w9w-0.png)

![Screenshot_2024_01_06_09_53_32_07_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/fnyzcu-0.jpg)

### 1.2 体系结构与参考模型

![image-20240103215529785](https://media.opennet.top/i/2024/01/03/ziyczl-0.png)

#### 1.2.1 分层结构

![image-20240103224831385](https://media.opennet.top/i/2024/01/03/112bt3c-0.png)

![image-20240103215408526](https://media.opennet.top/i/2024/01/03/zhzo2m-0.png)

![image-20240103215420161](https://media.opennet.top/i/2024/01/03/zib7tt-0.png)

![image-20240103215550334](https://media.opennet.top/i/2024/01/03/zj2v7u-0.png)

#### 1.2.2 协议、接口、服务

![image-20240103225341048](https://media.opennet.top/i/2024/01/03/115cuww-0.png)

![image-20240103225011320](https://media.opennet.top/i/2024/01/03/1135x5w-0.png)

![image-20240103225151335](https://media.opennet.top/i/2024/01/03/1148jq8-0.png)

![image-20240103225317881](https://media.opennet.top/i/2024/01/03/1157w0w-0.png)

![image-20240103225332587](https://media.opennet.top/i/2024/01/03/115b535-0.png)

服务分为：面向连接/无连接，可靠/不可靠，有应答/无应答

#### 1.2.3 OSI 和 TCP/IP 参考模型

##### OSI 参考模型

![image-20240101224634248](https://media.opennet.top/i/2024/01/01/1119evw-0.png)

![image-20240101224706429](https://media.opennet.top/i/2024/01/01/111osxe-0.png)

![image-20240101224741715](https://media.opennet.top/i/2024/01/01/111w9qz-0.png)

![image-20240101225022199](https://media.opennet.top/i/2024/01/01/113kt6j-0.png)

![image-20240101224923757](https://media.opennet.top/i/2024/01/01/112zkoz-0.png)

![image-20240101225113686](https://media.opennet.top/i/2024/01/01/11448eg-0.png)

![image-20240101225245366](https://media.opennet.top/i/2024/01/01/114w8wj-0.png)

![image-20240101225319959](https://media.opennet.top/i/2024/01/01/115c7op-0.png)

![image-20240101225357862](https://media.opennet.top/i/2024/01/01/115kcxn-0.png)

![image-20240101225502009](https://media.opennet.top/i/2024/01/01/116f9wd-0.png)

##### TCP/IP模型

![image-20240101225647851](https://media.opennet.top/i/2024/01/01/117ahhs-0.png)

![image-20240101225655060](https://media.opennet.top/i/2024/01/01/117c4ey-0.png)

![image-20240103104340609](https://media.opennet.top/i/2024/01/03/h4zmco-0.png)

##### 5层协议

![image-20240103104455735](https://media.opennet.top/i/2024/01/03/h5oaw9-0.png)

#### 题目

列出OSI七层协议和TCP/IP四层协议的名字。举例2种常用的应用层协议。

![image-20240103104638143](https://media.opennet.top/i/2024/01/03/h6rjbz-0.png)

![image-20240106095924555](https://media.opennet.top/i/2024/01/06/fqhnnc-0.png)

![Screenshot_2024_01_06_10_00_07_71_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/fr4e4u-0.jpg)

![image-20240106100158648](https://media.opennet.top/i/2024/01/06/fs4g86-0.png)

![Screenshot_2024_01_06_10_05_21_83_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/gjfwe8-0.jpg)

![Screenshot_2024_01_06_10_05_59_78_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/gjhd3v-0.jpg)

![image-20240106100209118](https://media.opennet.top/i/2024/01/06/fs6itk-0.png)

![Screenshot_2024_01_06_10_06_26_88_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/gjk035-0.jpg)

![Screenshot_2024_01_06_10_06_57_69_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/gjlgfy-0.jpg)

## 第 2 章 物理层

### 2.1 通信基础

#### 2.1.1 概念

##### 码元

![image-20240103104746417](https://media.opennet.top/i/2024/01/03/h7eoil-0.png)

##### 波特率 比特率 带宽

![image-20240103104905973](https://media.opennet.top/i/2024/01/03/h84sjn-0.png)

![image-20240103104940677](https://media.opennet.top/i/2024/01/03/h8khrq-0.png)

#### 2.1.2 奈奎斯特定理 香农定理

![image-20240103105337106](https://media.opennet.top/i/2024/01/03/haz1wu-0.png)

![image-20240103105435119](https://media.opennet.top/i/2024/01/03/hbi0n3-0.png)

#### 题目

在无噪声情况下，若某通信链路的波特率为2000，采用8种振幅等级的调制技术，则该通信链路的最大数据传输速率是多少bps。

（用3bit可以表示一个码元）

![image-20240103111007510](https://media.opennet.top/i/2024/01/03/i8p8p1-0.png)

若链路的频率带宽为4000Hz，信噪比为30dB，该链路理论最大数据传输速率是多少bps（香农定理）。

![image-20240103110605821](https://media.opennet.top/i/2024/01/03/hi8ngf-0.png)

![image-20240106100926491](https://media.opennet.top/i/2024/01/06/gk9thr-0.png)

![Screenshot_2024_01_06_10_10_22_54_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/glsr54-0.jpg)

![image-20240106100935322](https://media.opennet.top/i/2024/01/06/gkbiuq-0.png)

![Screenshot_2024_01_06_10_11_12_22_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/glunqm-0.jpg)

#### 2.1.3 编码与调制

![image-20240103135608372](https://media.opennet.top/i/2024/01/03/mb6fah-0.png)

![image-20240103135624491](https://media.opennet.top/i/2024/01/03/mb9ph1-0.png)

#### 题目

以太网采用曼彻斯特编码，数据率为50Mb/s在物理媒体上的码元传输速率是多少码元/秒？

码元传输速率 = 50Mb/s * 2 = 100M码元/秒

#### 2.1.4 交换

![image-20240103111901467](https://media.opennet.top/i/2024/01/03/idseqg-0.png)

##### 电路交换

![image-20240103111357325](https://media.opennet.top/i/2024/01/03/iattju-0.png)

##### 报文交换 分组交换

![image-20240103111758399](https://media.opennet.top/i/2024/01/03/id66f2-0.png)

![image-20240103111813438](https://media.opennet.top/i/2024/01/03/idh9l1-0.png)

![image-20240103111841434](https://media.opennet.top/i/2024/01/03/idn47r-0.png)

#### 题目

![image-20240103111957300](https://media.opennet.top/i/2024/01/03/iecdj2-0.png)

注：优缺点自行补充

![image-20240103114259928](https://media.opennet.top/i/2024/01/03/is1wlf-0.png)

![image-20240106094356238](https://media.opennet.top/i/2024/01/06/fhe359-0.png)

![Screenshot_2024_01_06_09_46_28_55_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/fjphhi-0.jpg)

![Screenshot_2024_01_06_09_47_18_25_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/fjr6la-0.jpg)

### 2.2 传输介质

有线：双绞线、同轴电缆、光纤

无线：无线电波、微波、红外线、激光

物理层特性：机械特性、电气特性、功能特性、过程特性

### 2.3 物理层设备

#### 2.3.1 中继器

![image-20240103141943118](https://media.opennet.top/i/2024/01/03/ncvykm-0.png)

![image-20240103142001313](https://media.opennet.top/i/2024/01/03/nd08em-0.png)

#### 2.3.2 集线器

![image-20240103142153548](https://media.opennet.top/i/2024/01/03/ne5jt7-0.png)

#### 题目

交换机和集线器分别工作在哪一层？

交换机：数据链路层

集线器：物理层

## 第 3 章 数据链路层

### 3.3 差错控制

#### 3.3.1 检错编码

##### 循环冗余码 CRC

![image-20240103130115366](https://media.opennet.top/i/2024/01/03/kqn0da-0.png)

![image-20240103130202568](https://media.opennet.top/i/2024/01/03/kqwpmr-0.png)

#### 题目

设生成多项式G(x)=x^3+x+1，要发送的数据为101010，求CRC技术产生的余数（写出计算过程）。

![image-20240103131849955](https://media.opennet.top/i/2024/01/03/los3pt-0.png)

![image-20240106101303010](https://media.opennet.top/i/2024/01/06/gmigm3-0.png)

![Screenshot_2024_01_06_10_14_19_73_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/go73wn-0.jpg)

![image-20240106101327263](https://media.opennet.top/i/2024/01/06/gmniq4-0.png)

![Screenshot_2024_01_06_10_15_17_10_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/go8yro-0.jpg)

### 3.5 介质访问控制

#### 3.5.1 信道划分

这部分应属于物理层，请注意

##### 码分多址 CDMA*

![image-20240103120111552](https://media.opennet.top/i/2024/01/03/j32upt-0.png)

![image-20240103120124086](https://media.opennet.top/i/2024/01/03/j35udy-0.png)

#### 题目

站点A,B,C通过CDMA共享链路，A,B,C的码片序列分别是（1,1,1,1）、（1,-1,1,-1）和（1,1,-1,-1）。如果从链路上收到序列是（2，0，2，0，0，-2，0，-2，0，2，0，2），则C收到A发送的数据是什么。

![image-20240103121256837](https://media.opennet.top/i/2024/01/03/jxq6u0-0.png)

#### 3.5.2 随机访问

##### CSMA/CD 协议*

![image-20240103141243717](https://media.opennet.top/i/2024/01/03/n8s0lq-0.png)

![image-20240103141308073](https://media.opennet.top/i/2024/01/03/n8uhb8-0.png)

![image-20240103141318503](https://media.opennet.top/i/2024/01/03/n952bj-0.png)

![image-20240103141331756](https://media.opennet.top/i/2024/01/03/n989i1-0.png)

#### 题目

CSMA/CD协议的10Mb/s以太网中争用期51.2us，某个站在发送数据时检测到碰撞，执行退避算法时选择了随机数r=15。试问这个站需要等待多长时间后才能再次发送数据？
$$
\text{退避时间} = \text{争用期} \times r = 51.2 \text{微秒} \times 15 = 768微秒
$$

### 3.6 局域网

#### 3.6.2 以太网 IEEE 802.3

##### MAC 帧

![image-20240103184444889](https://media.opennet.top/i/2024/01/03/udvu3i-0.png)

![image-20240103184458070](https://media.opennet.top/i/2024/01/03/udyk5l-0.png)

![image-20240103184508180](https://media.opennet.top/i/2024/01/03/ue0uj2-0.png)

#### 3.6.4 虚拟局域网 VLAN

![image-20240103145805540](https://media.opennet.top/i/2024/01/03/nzme81-0.png)

![image-20240103145816404](https://media.opennet.top/i/2024/01/03/nzxlkh-0.png)

![image-20240103145827519](https://media.opennet.top/i/2024/01/03/o0796x-0.png)

#### 题目

虚拟局域网，它的主要作用是什么？

（1）将一个局域网分为多个逻辑网络，每个网络是独立的广播域。减少不必要的广播流量

（2）每个部门有自己的VLAN，减小广播范围，提高安全性

![image-20240106101714087](https://media.opennet.top/i/2024/01/06/goydep-0.png)

![Screenshot_2024_01_06_10_18_43_46_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/gq4umz-0.jpg)

### 3.7 广域网

#### 3.7.2 PPP 协议*

![image-20240103134818790](https://media.opennet.top/i/2024/01/03/m6gax6-0.png)

![image-20240103134830589](https://media.opennet.top/i/2024/01/03/m6ihpt-0.png)

![image-20240103134846863](https://media.opennet.top/i/2024/01/03/m6mcpn-0.png)

![image-20240103134919871](https://media.opennet.top/i/2024/01/03/m71iss-0.png)

![image-20240103134700544](https://media.opennet.top/i/2024/01/03/m5i9yi-0.png)

#### 题目

一个PPP帧的数据部分（用十六进制写出）是7D 5E 22 7D 5D 7D 25 65 7D 5E。试问真正的数据是什么（用十六进制写出）？

![image-20240103135238905](https://media.opennet.top/i/2024/01/03/m8zeyw-0.png)

### 3.8 数据链路层设备

#### 3.8.2 交换机

##### 原理 特点

![image-20240103142548579](https://media.opennet.top/i/2024/01/03/ngh82f-0.png)

![image-20240103142600450](https://media.opennet.top/i/2024/01/03/ngjwor-0.png)

##### 自学习算法

![image-20240103142820355](https://media.opennet.top/i/2024/01/03/ni3wog-0.png)

![image-20240103142925619](https://media.opennet.top/i/2024/01/03/niqglz-0.png)

#### 题目

交换机和集线器分别工作在哪一层？

交换机：数据链路层

集线器：物理层

![image-20240103184804216](https://media.opennet.top/i/2024/01/03/ufsdhi-0.png)

![image-20240106102007892](https://media.opennet.top/i/2024/01/06/gqpe25-0.png)

![image-20240106102020033](https://media.opennet.top/i/2024/01/06/gqs3is-0.png)

答：最大吞吐量为 100Mbps。整个系统是一个碰撞域。

![image-20240106102158063](https://media.opennet.top/i/2024/01/06/grues2-0.png)

![Screenshot_2024_01_06_10_22_27_09_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/gscw4h-0.jpg)

## 第 4 章 网络层

### 4.3 IPv4

#### 4.3.1 IPv4 分组

##### 格式

![image-20240103162046036](https://media.opennet.top/i/2024/01/03/qojpx0-0.png)

![image-20240103162109977](https://media.opennet.top/i/2024/01/03/qoowjh-0.png)

![image-20240103162121050](https://media.opennet.top/i/2024/01/03/qp098h-0.png)

##### 分片

![image-20240103162308558](https://media.opennet.top/i/2024/01/03/qq4r2k-0.png)

![image-20240103162324160](https://media.opennet.top/i/2024/01/03/qq89u2-0.png)

#### 题目

一个数据报长度为4000字节（固定首部长度20字节）。现在经过一个网络传送，但此网络能够传送的最大数据长度为1460字节。试问应当划分为几个短些的数据报片？各数据报片的数据字段长度、片偏移字段和MF标志应为何数值？

![image-20240103163206707](https://media.opennet.top/i/2024/01/03/qv8gdz-0.png)

![image-20240106103011475](https://media.opennet.top/i/2024/01/06/gwooti-0.png)

> 感谢 byc gg 的勘误

数据帧是数据链路层，其数据部分1200，所以IP的首部加数据为1200

IP首部为160，数据部分长度规定为8B的倍数。1200-160=1040bit=130B=16.25*8B，数据部分长度选择1024

前三个IP分组为(160+1024)*3=3552 bit

最后一个为160+(3200-1024*3)=288 bit

总共3552+288=3840 bit

#### 4.3.2 IPv4 地址与 NAT

##### IPv4 地址

![image-20240103151307201](https://media.opennet.top/i/2024/01/03/owdz4l-0.png)

![image-20240103151326598](https://media.opennet.top/i/2024/01/03/owqtar-0.png)

![image-20240103151337531](https://media.opennet.top/i/2024/01/03/owt5th-0.png)

##### 网络地址转换 NAT

![image-20240103151658302](https://media.opennet.top/i/2024/01/03/oypgzu-0.png)

![image-20240103151709856](https://media.opennet.top/i/2024/01/03/oz0sbu-0.png)

![image-20240103151722714](https://media.opennet.top/i/2024/01/03/oz4g0a-0.png)

![image-20240103151741757](https://media.opennet.top/i/2024/01/03/oz77j9-0.png)

#### 题目

以下三个IP地址分别属于哪类？192.168.0.1，10.1.1.1，128.191.1.1

C类、A类、B类

### 4.3.3 子网划分 子网掩码 CIDR

##### 子网划分

![image-20240103152118406](https://media.opennet.top/i/2024/01/03/p1gadz-0.png)

##### 子网掩码

![image-20240103154039367](https://media.opennet.top/i/2024/01/03/pcvow6-0.png)

![image-20240103154047866](https://media.opennet.top/i/2024/01/03/pcwwc4-0.png)

##### 无分类地址 CIDR

![image-20240103154407366](https://media.opennet.top/i/2024/01/03/pf5ceo-0.png)

![image-20240103154433543](https://media.opennet.top/i/2024/01/03/pf7weo-0.png)

![image-20240103154700718](https://media.opennet.top/i/2024/01/03/pgkaf4-0.png)

##### 分组转发

![image-20240103155020625](https://media.opennet.top/i/2024/01/03/pip69d-0.png)

![image-20240103155030992](https://media.opennet.top/i/2024/01/03/pirmln-0.png)

![image-20240103155039205](https://media.opennet.top/i/2024/01/03/piu6nv-0.png)

#### 题目

什么叫分类编址和无分类编址（CIDR）？它们区别是什么？

![image-20240103155331651](https://media.opennet.top/i/2024/01/03/pkka2s-0.png)

![image-20240103155340634](https://media.opennet.top/i/2024/01/03/pklw7z-0.png)

已知地址块中的一个地址是206.150.86.24/20。这个地址块中的最小地址和最大地址，地址掩码是什么？地址块中共有多少个地址？

![image-20240103161139819](https://media.opennet.top/i/2024/01/03/qj51wv-0.png)

![image-20240106102810034](https://media.opennet.top/i/2024/01/06/gvhh32-0.png)

![Screenshot_2024_01_06_10_28_24_65_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/gvxn8x-0.jpg)

#### 4.3.4 ARP DHCP ICMP

##### ARP

![image-20240103160003220](https://media.opennet.top/i/2024/01/03/pobnxw-0.png)

![image-20240103160014502](https://media.opennet.top/i/2024/01/03/pomno5-0.png)

#### 题目

![image-20240106103234187](https://media.opennet.top/i/2024/01/06/gy08mu-0.png)

![Screenshot_2024_01_06_10_33_26_56_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/gzgln0-0.jpg)

![Screenshot_2024_01_06_10_34_14_93_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/gzhvft-0.jpg)

### 4.4 IPv6

#### 4.4.1 特点

![image-20240103230747743](https://media.opennet.top/i/2024/01/03/121kksn-0.png)

### 4.5 路由协议

#### 4.5.3 路由信息协议 RIP

![image-20240103175621231](https://media.opennet.top/i/2024/01/03/sxdnd8-0.png)

![image-20240103175638952](https://media.opennet.top/i/2024/01/03/sxhhne-0.png)

![image-20240103175651583](https://media.opennet.top/i/2024/01/03/sxjyka-0.png)

#### 4.5.4 开放最短路径优先协议 OSPF

![image-20240103180202881](https://media.opennet.top/i/2024/01/03/t0l24g-0.png)

![image-20240103180211855](https://media.opennet.top/i/2024/01/03/t0w0tt-0.png)

![image-20240103180221004](https://media.opennet.top/i/2024/01/03/t0ya0y-0.png)

![image-20240103180244811](https://media.opennet.top/i/2024/01/03/t135y7-0.png)

#### 题目

假定网络中的路由器B使用rip协议，其路由表有如下的项目（这三列分别表示“目的网络”、“距离”和“下一跳路由器”）

N1   5    A

N2   3    C

N6    8    F

N8    4    E

N9    4    F

现在B收到从C发来的路由信息（这两列分别表示“目的网络”“距离”）：

N2    5

N3    8

N6    3

N8    3

N9    5

试求出路由器B更新后的路由表（详细说明每一个步骤）。

![image-20240103182627740](https://media.opennet.top/i/2024/01/03/u33n1k-0.png)

#### 4.5.5 边界网关协议 BGP*

![image-20240103230325984](https://media.opennet.top/i/2024/01/03/11b88ye-0.png)

![image-20240103230339831](https://media.opennet.top/i/2024/01/03/11bb6n6-0.png)

### 4.6 IP 组播*

#### 4.6.1 概念*

![image-20240103230617449](https://media.opennet.top/i/2024/01/03/11cyqu4-0.png)

### 4.7 移动 IP*

#### 4.7.1 概念

![image-20240103231100204](https://media.opennet.top/i/2024/01/03/123eun4-0.png)

### 4.8 网络层设备

#### 4.8.1 冲突域和广播域

![image-20240103143435901](https://media.opennet.top/i/2024/01/03/nlrjhg-0.png)

![image-20240103144413274](https://media.opennet.top/i/2024/01/03/nrkmtw-0.png)

#### 题目

什么是冲突域和广播域？

#### 4.8.2 路由器

![image-20240103163454422](https://media.opennet.top/i/2024/01/03/qwyid3-0.png)

![image-20240103163510060](https://media.opennet.top/i/2024/01/03/qx9trt-0.png)

![image-20240103163518577](https://media.opennet.top/i/2024/01/03/qxbw5b-0.png)

#### 4.8.3 路由表与路由转发

![image-20240103163809025](https://media.opennet.top/i/2024/01/03/qz24hp-0.png)

![image-20240103163820720](https://media.opennet.top/i/2024/01/03/qz4eba-0.png)

![image-20240103163829947](https://media.opennet.top/i/2024/01/03/qz6ud7-0.png)

#### 题目

已知路由器转发表如下所示。

前缀地址掩码    下一跳地址 

192.4.153.0/26    接口m0

128.96.39.0/25    接口m1

128.96.39.128/25   R2

默认             R4

\------------------------------

现收到如下分组，分别计算下一跳。

（1）128.96.39.12

（2）128.96.39.129

（3）192.4.153.17

（4）192.4.153.99

![image-20240103165158444](https://media.opennet.top/i/2024/01/03/r738jk-0.png)

如图所示，网络145.13.0.0/16划分为四个子网N1，N2，N3，N4。四个子网与路由器R连接的接口分别是m0，m1，m2，m3。路由器R的第五个接口m4连接到互联网。

1）试给出路由器R的路由表。

2）路由器R收到一个分组，其目的地址是145.13.168.24。试解释这个分组是怎样被转发的。

3）路由器R收到一个分组，其目的地址是145.10.168.24。试解释这个分组是怎样被转发的。

![img](https://media.opennet.top/i/2024/01/03/u4761n-0.jpeg)

![image-20240103183722334](https://media.opennet.top/i/2024/01/03/u9le4v-0.png)

![Screenshot_2024_01_06_10_24_32_81_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/gtlbwt-0.jpg)

## 第 5 章 传输层

### 5.2 UDP 协议

#### 5.2.1 UDP 数据报

![image-20240103221303836](https://media.opennet.top/i/2024/01/03/10h42qm-0.png)

![image-20240103221315371](https://media.opennet.top/i/2024/01/03/10hev0o-0.png)

### 5.3 TCP 协议

#### 5.3.1 特点

![image-20240103204054436](https://media.opennet.top/i/2024/01/03/xn0hii-0.png)

#### 5.3.2 报文段

![image-20240103204403975](https://media.opennet.top/i/2024/01/03/xohdpf-0.png)

![image-20240103204422994](https://media.opennet.top/i/2024/01/03/xou3j0-0.png)

![image-20240103204433643](https://media.opennet.top/i/2024/01/03/xow6cv-0.png)

![image-20240103204443317](https://media.opennet.top/i/2024/01/03/xoydb3-0.png)

#### 题目

主机A向主机B连续发送了两个TCP报文段，其序号分别为50和120。试问：

（1）第一报文大小多少？

（2）如果A发送的第一个报文段丢失了，但第二个报文段到达了B。B在第二个报文段到达后向A发送确认。试问这个确认号ack应为多少？

(1) 120 - 50 = 70 B

(2) 50

#### 5.3.3 连接管理

![image-20240103204719973](https://media.opennet.top/i/2024/01/03/xqlq9v-0.png)

![image-20240103204910167](https://media.opennet.top/i/2024/01/03/xrhmji-0.png)

##### 连接建立

![image-20240103204731042](https://media.opennet.top/i/2024/01/03/xqnzn6-0.png)

![image-20240103204739394](https://media.opennet.top/i/2024/01/03/xqpsbx-0.png)

##### 连接释放

![image-20240103205033442](https://media.opennet.top/i/2024/01/03/xsguzk-0.png)

![image-20240103205041329](https://media.opennet.top/i/2024/01/03/xsijsp-0.png)

![image-20240103205049828](https://media.opennet.top/i/2024/01/03/xsk4bc-0.png)

#### 5.3.4 可靠传输

![image-20240103210024866](https://media.opennet.top/i/2024/01/03/xydrql-0.png)

![image-20240103210034809](https://media.opennet.top/i/2024/01/03/xyfbxs-0.png)

#### 5.3.5 流量控制

![image-20240103210234432](https://media.opennet.top/i/2024/01/03/xzmzrk-0.png)

![image-20240103210312163](https://media.opennet.top/i/2024/01/03/y03akr-0.png)

#### 题目

设主机A通过TCP向主机B发送数据。甲发送(seq=101，DATA）的段，随后收到B发送（seq=201，ack= 201，rwnd = 300）的段。请问A可以继续向B发送的数据序号范围是多少？

201~500

#### 5.3.6 拥塞控制

##### 慢开始和拥塞避免

![image-20240103210933551](https://media.opennet.top/i/2024/01/03/yrm255-0.png)

![image-20240103210945126](https://media.opennet.top/i/2024/01/03/yrnx36-0.png)

![image-20240103210956903](https://media.opennet.top/i/2024/01/03/yrq82e-0.png)

##### 快重传和快恢复

![image-20240103211025820](https://media.opennet.top/i/2024/01/03/ys5fqn-0.png)

![image-20240103211036282](https://media.opennet.top/i/2024/01/03/ys7d7c-0.png)

### 题目

TCP和UDP的主要区别是什么？

![image-20240103211358205](https://media.opennet.top/i/2024/01/03/yu4ugd-0.png)

当用户在应用程序想要对数据的发送时机和内容进行控制，应当选择TCP还是UDP?

选择UDP。

(1) UDP无需建立连接，不会引入建立连接的延迟

(2) UDP没有流量控制和拥塞控制，发送方自行控制速率

(3) 对于应用层的报文，UDP一次交付一个完整的报文，不会将其分片

(4) UDP不保证可靠传输，不会影响报文顺序

![image-20240106103559266](https://media.opennet.top/i/2024/01/06/h06p22-0.png)

![Screenshot_2024_01_06_10_38_32_66_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/h2ie9e-0.jpg)

5-06：丢弃。

5-07：可能，但应用程序必须额外提供与TCP相同的功能。

![Screenshot_2024_01_06_10_42_33_92_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/06/h4c3cc-0.jpg)

![image-20240106104320541](https://media.opennet.top/i/2024/01/06/h4h0tg-0.png)

![Screenshot_2024_01_06_10_45_42_69_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/h7f4x9-0.jpg)

![image-20240106104350034](https://media.opennet.top/i/2024/01/06/h4w1al-0.png)

![Screenshot_2024_01_06_10_46_24_32_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/h6vllw-0.jpg)

![image-20240106104359566](https://media.opennet.top/i/2024/01/06/h4y2ac-0.png)

![Screenshot_2024_01_06_10_46_52_25_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/h78h9e-0.jpg)

## 第 6 章 应用层

![image-20240103213527429](https://media.opennet.top/i/2024/01/03/z71cyb-0.png)

### 6.1 网络应用模型

客户/服务器模型、P2P模型

### 6.2 域名系统 DNS

#### 6.2.2 域名服务器

![image-20240103212244423](https://media.opennet.top/i/2024/01/03/yzeifm-0.png)

![image-20240103212258249](https://media.opennet.top/i/2024/01/03/yzhmoe-0.png)

#### 6.2.3 域名解析过程

![image-20240103212513571](https://media.opennet.top/i/2024/01/03/z0rf8r-0.png)

![image-20240103212523481](https://media.opennet.top/i/2024/01/03/z12nru-0.png)

![image-20240103212625199](https://media.opennet.top/i/2024/01/03/z1olib-0.png)

![image-20240103212701108](https://media.opennet.top/i/2024/01/03/z1vnjk-0.png)

![image-20240103212708571](https://media.opennet.top/i/2024/01/03/z1x89e-0.png)

#### 题目

![image-20240106105610664](https://media.opennet.top/i/2024/01/06/hc5qbe-0.png)

答：有可能，如果你能够直接使用对方邮件服务器的IP地址。

### 6.3 文件传输协议 FTP

#### 6.3.2 控制连接 数据连接*

![image-20240103234319110](https://media.opennet.top/i/2024/01/03/12mtif3-0.png)

### 6.4 电子邮件

#### 6.4.1 组成结构*

##### 收发过程

![image-20240103234522919](https://media.opennet.top/i/2024/01/03/12o12fy-0.png)

### 6.5 万维网 WWW

#### 6.5.2 超文本传输协议 HTTP

![image-20240103213430715](https://media.opennet.top/i/2024/01/03/z6gubx-0.png)

![image-20240103213439536](https://media.opennet.top/i/2024/01/03/z6iprp-0.png)

![image-20240103213501826](https://media.opennet.top/i/2024/01/03/z6nndx-0.png)

![image-20240103213509418](https://media.opennet.top/i/2024/01/03/z6p5qt-0.png)

#### 题目

用户从地址栏输入某URL后直到网页显示在屏幕上这一过程，计算机要执行哪些应用层和传输层协议？

应用层：DNS、HTTP

传输层：UDP、TCP

假设您在Web浏览器中单击某个链接以获取网页。关联URL的地址没有缓存在本地主机中，因此DNS查找是获取IP地址所必需的。假设之前访问了n个DNS服务器，您的主机从DNS接收IP地址；连续的访问导致RTT，即RTT1，…，RTTn。进一步假设与链接相关联的网页包含恰好一个对象，由少量HTML文本组成。让RTT0表示本地主机和包含对象的服务器之间的RTT。

1）假设对象的传输时间为零，从客户端点击链接到客户端收到对象一共花费多少时间（RTT为单位）？

2）现在假设HTML文件引用了同一服务器上的8个非常小的对象。忽略传输时间，回答在以下条件下，一共经历多长时间？

a) 没有并行连接的非持久HTTP1.0？

b) 并行连接（2个并行）的非持久HTTP1.0？ 

c) 非流水线持久HTTP1.1？

d) 流水线持久HTTP1.1?

![image-20240103214807197](https://media.opennet.top/i/2024/01/03/zefc3j-0.png)

![image-20240106105746130](https://media.opennet.top/i/2024/01/06/hd77wm-0.png)

![Screenshot_2024_01_06_10_58_02_02_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/hdz7sm-0.jpg)

![Screenshot_2024_01_06_10_58_51_63_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/06/he1r78-0.jpg)
