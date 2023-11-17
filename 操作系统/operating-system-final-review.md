# 第2章 进程的描述与控制

## 2.1 前驱图和程序执行

### 2.1.1 前驱图

![image-20231116192713336](https://media.opennet.top/i/2023/11/16/vvdxpr-0.png)

### 2.1.2 程序顺序执行

顺序性、封闭性、可再现性

### 2.1.3 程序并发执行

间断性、失去封闭性、不可再现性

## 2.2 进程的描述

### 2.2.1 进程的定义与特征

![image-20231116193126917](https://media.opennet.top/i/2023/11/16/vxv1tj-0.png)

特征：动态性、并发性、独立性、异步性

### 2.2.2 进程的状态与转换

![image-20231116193508421](https://media.opennet.top/i/2023/11/16/w055fw-0.png)

![image-20231116193529034](https://media.opennet.top/i/2023/11/16/w08vxf-0.png)

### 2.2.3 挂起操作*

![image-20231116193816368](https://media.opennet.top/i/2023/11/16/w1z25l-0.png)

![image-20231116193914940](https://media.opennet.top/i/2023/11/16/w2juep-0.png)

### 2.2.4 进程管理中的数据结构

**PCB 进程控制块**

![image-20231116194342949](https://media.opennet.top/i/2023/11/16/w53eg2-0.png)

**组织方式**

线性、链接、索引

![image-20231116194610008](https://media.opennet.top/i/2023/11/16/w6p8y8-0.png)

## 2.3 进程控制

### 2.3.1 进程的创建

![image-20231116194844457](https://media.opennet.top/i/2023/11/16/w838rc-0.png)

### 2.3.2 进程的终止

![image-20231116195014923](https://media.opennet.top/i/2023/11/16/w93wuy-0.png)

### 2.3.3 进程的阻塞和唤醒

![image-20231116195218754](https://media.opennet.top/i/2023/11/16/wacdsc-0.png)

![image-20231116195259541](https://media.opennet.top/i/2023/11/16/wat8o4-0.png)

### 2.3.4 进程的挂起和激活*

![image-20231116195408372](https://media.opennet.top/i/2023/11/16/wbg9r9-0.png)

## 2.4 进程通信

### 2.4.1 进程通信的类型

**共享存储**

![image-20231116195956778](https://media.opennet.top/i/2023/11/16/x2r346-0.png)

**消息传递**

![image-20231116200016849](https://media.opennet.top/i/2023/11/16/x2vhon-0.png)

![image-20231116200030499](https://media.opennet.top/i/2023/11/16/x2ydnt-0.png)

**管道**

![image-20231116200058327](https://media.opennet.top/i/2023/11/16/x3f361-0.png)

**客户机-服务器系统**

套接字（socket）

远程过程调用（RPC）

### 2.4.2 消息传递通信的实现方式*

## 2.5 线程

### 2.5.1 线程的引入

![image-20231116200638157](https://media.opennet.top/i/2023/11/16/x6kekn-0.png)

![image-20231116200654772](https://media.opennet.top/i/2023/11/16/x6nyjh-0.png)

### 2.5.2 线程与进程的比较

![image-20231116200915717](https://media.opennet.top/i/2023/11/16/x88pxp-0.png)

### 2.5.3 线程状态与线程控制块

![image-20231116201618775](https://media.opennet.top/i/2023/11/16/xceo4v-0.png)

![image-20231116202447189](https://media.opennet.top/i/2023/11/16/xhcati-0.png)

## 2.6 线程的实现*

### 2.6.1 线程的实现方式

![image-20231116202113846](https://media.opennet.top/i/2023/11/16/xfcvwl-0.png)

**用户级线程**

![image-20231116202126932](https://media.opennet.top/i/2023/11/16/xfg1lx-0.png)

![image-20231116202145532](https://media.opennet.top/i/2023/11/16/xfjj07-0.png)

**内核级线程**

![image-20231116202245275](https://media.opennet.top/i/2023/11/16/xg588m-0.png)

**组合方式**

![image-20231116202409376](https://media.opennet.top/i/2023/11/16/xh49ya-0.png)

### 2.6.2 线程的具体实现*

### 2.6.3 线程的创建和终止

![image-20231116202553947](https://media.opennet.top/i/2023/11/16/xhz2zf-0.png)

# 第 3 章 处理机调度与死锁

## 3.1 处理机调度概述

### 3.1.1 处理机调度的层次

低级调度：进程

中级调度：内存

高级调度：作业

### 3.1.2 作业和作业调度*

### 3.1.3 进程调度

![image-20231116205134672](https://media.opennet.top/i/2023/11/16/xxd0ry-0.png)

![image-20231116205255493](https://media.opennet.top/i/2023/11/16/xybafc-0.png)

### 3.1.4 处理机调度算法的目标

![image-20231116205429423](https://media.opennet.top/i/2023/11/16/xz43jx-0.png)

## 3.2 调度算法

![image-20231116214138669](https://media.opennet.top/i/2023/11/16/zeygq5-0.png)

### 3.2.1 先来先服务

First Come First Server

非抢占式

![image-20231116212059976](https://media.opennet.top/i/2023/11/16/z2thlx-0.png)

![image-20231116212111191](https://media.opennet.top/i/2023/11/16/z2w7ia-0.png)

### 3.2.2 短作业优先

Short Job First

默认非抢占式

![image-20231116212644135](https://media.opennet.top/i/2023/11/16/z6e9b4-0.png)

### 3.2.3 优先级

Priority-Scheduling

![image-20231116212906154](https://media.opennet.top/i/2023/11/16/z7murf-0.png)

**高响应比优先 Highest Response Ratio Next**

非抢占式

![image-20231116213235943](https://media.opennet.top/i/2023/11/16/z9l5f7-0.png)

### 3.2.4 时间片轮转

Round Robin

抢占式

![image-20231116213350818](https://media.opennet.top/i/2023/11/16/za9leq-0.png)

![image-20231116213409955](https://media.opennet.top/i/2023/11/16/zam412-0.png)

### 3.2.5 多级队列

Multileved Queue

![image-20231116213852992](https://media.opennet.top/i/2023/11/16/zd98uk-0.png)

### 3.2.6 多级反馈队列

Multileved Feedback Queue

![image-20231116214041741](https://media.opennet.top/i/2023/11/16/zee4lv-0.png)

![image-20231116214101385](https://media.opennet.top/i/2023/11/16/zeqk1h-0.png)

### 3.2.7 公平原则*

## 3.3 实时调度*

### 3.3.3 最早截止时间优先

![image-20231116214851284](https://media.opennet.top/i/2023/11/16/zknqyd-0.png)

![image-20231116215242040](https://media.opennet.top/i/2023/11/16/zljpnz-0.png)

![image-20231116215325418](https://media.opennet.top/i/2023/11/16/zm0yry-0.png)

![image-20231116215333916](https://media.opennet.top/i/2023/11/16/zm383u-0.png)

![image-20231116215356974](https://media.opennet.top/i/2023/11/16/zmguw8-0.png)

### 3.3.4 最低松弛度优先

![image-20231116215530960](https://media.opennet.top/i/2023/11/16/zna7fw-0.png)

![image-20231116215549177](https://media.opennet.top/i/2023/11/16/zndw96-0.png)

## 3.5 死锁

### 3.5.1 资源问题

可重用资源：eg 设备、文件

可消耗资源：eg 进程间通信的信息

可抢占资源：eg 处理机、内存

不可抢占资源：eg 磁带机、打印机

### 3.5.2 死锁产生的原因

![image-20231116220343748](https://media.opennet.top/i/2023/11/16/10fx9qv-0.png)

### 3.5.3 死锁的定义、条件和处理

![image-20231116220509465](https://media.opennet.top/i/2023/11/16/10gwb7u-0.png)

![image-20231116220621855](https://media.opennet.top/i/2023/11/16/10hkeur-0.png)

![image-20231116220726985](https://media.opennet.top/i/2023/11/16/10i7d4p-0.png)

![image-20231116220814908](https://media.opennet.top/i/2023/11/16/10iq6yk-0.png)

![image-20231116220838896](https://media.opennet.top/i/2023/11/16/10iv0rv-0.png)

### 3.5.4 资源分配图

![image-20231116223653605](https://media.opennet.top/i/2023/11/16/10zlmsf-0.png)

## 3.6 死锁预防

![image-20231116221943559](https://media.opennet.top/i/2023/11/16/10pgk0a-0.png)

## 3.7 死锁避免

### 3.7.1 系统安全状态

![image-20231116222213550](https://media.opennet.top/i/2023/11/16/10r27tj-0.png)

### 3.7.2 银行家算法

**安全性算法**

![image-20231116222850785](https://media.opennet.top/i/2023/11/16/10v3olo-0.png)

![image-20231116223042329](https://media.opennet.top/i/2023/11/16/10w0168-0.png)

![image-20231116223205479](https://media.opennet.top/i/2023/11/16/10wyltz-0.png)

![image-20231116223221771](https://media.opennet.top/i/2023/11/16/10x1608-0.png)

## 3.8 死锁的检测与解除

### 3.8.1 死锁的检测

![image-20231116223825740](https://media.opennet.top/i/2023/11/16/110mm2l-0.png)

### 3.8.2 死锁的解除

![image-20231116223948933](https://media.opennet.top/i/2023/11/16/111d5fk-0.png)

# 第 4 章 进程同步

## 4.1 进程同步的基本概念

### 4.1.1 进程同步概念的引入

![image-20231116224702880](https://media.opennet.top/i/2023/11/16/115umxr-0.png)

![image-20231116224926532](https://media.opennet.top/i/2023/11/16/1176cix-0.png)

![image-20231116224934340](https://media.opennet.top/i/2023/11/16/117842h-0.png)

### 4.1.2 临界区问题

![image-20231116224815899](https://media.opennet.top/i/2023/11/16/116iu4g-0.png)

![image-20231116225152456](https://media.opennet.top/i/2023/11/16/118ixc3-0.png)

## 4.2 软件同步机制

![image-20231116225614099](https://media.opennet.top/i/2023/11/16/11ba3aq-0.png)

## 4.3 硬件同步机制

![image-20231116225727284](https://media.opennet.top/i/2023/11/16/11by19d-0.png)

![image-20231116225841583](https://media.opennet.top/i/2023/11/16/11cmu8e-0.png)

![image-20231116225922187](https://media.opennet.top/i/2023/11/16/11d3xjq-0.png)

![image-20231116225938363](https://media.opennet.top/i/2023/11/16/11d78hb-0.png)

## 4.4 信号量机制

### 4.4.1 信号量机制介绍

**整形**

![image-20231116230802524](https://media.opennet.top/i/2023/11/16/1265u9s-0.png)

**记录型**

![image-20231116230952942](https://media.opennet.top/i/2023/11/16/127bs6t-0.png)

**AND型**

![image-20231116231303102](https://media.opennet.top/i/2023/11/16/12959g7-0.png)

![image-20231116231316185](https://media.opennet.top/i/2023/11/16/1297zdc-0.png)

**信号量集**

![image-20231116231532069](https://media.opennet.top/i/2023/11/16/12aic3l-0.png)

![image-20231116231637813](https://media.opennet.top/i/2023/11/16/12b4v71-0.png)

### 4.4.2 信号量的应用

![image-20231116231845747](https://media.opennet.top/i/2023/11/16/12cdnm0-0.png)

![image-20231116231954339](https://media.opennet.top/i/2023/11/16/12d0oui-0.png)

## 4.5 管程

**管程的定义**

![image-20231116232323399](https://media.opennet.top/i/2023/11/16/12f7sie-0.png)

![image-20231116232336515](https://media.opennet.top/i/2023/11/16/12falmh-0.png)

**条件变量**

![image-20231116232517709](https://media.opennet.top/i/2023/11/16/12gdcmf-0.png)

![image-20231116232530078](https://media.opennet.top/i/2023/11/16/12gfzo4-0.png)

![image-20231116232537110](https://media.opennet.top/i/2023/11/16/12ghkw2-0.png)

## 4.6 经典的进程同步问题

### 4.6.1 生产者-消费者问题

![image-20231116233208058](https://media.opennet.top/i/2023/11/16/12khom2-0.png)

![image-20231116233339249](https://media.opennet.top/i/2023/11/16/12l9ooo-0.png)