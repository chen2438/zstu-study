---
description: 发布于 2024-01-08
categories:
- study
date: 2024-01-08
slug: operating-system-final-review
title: 操作系统 期末复习
updated: 2024-01-11
tags: 
- study
- operating-system
copyright: false
---

# 操作系统 期末复习

zstu 浙江理工大学 2023学年第1学期 操作系统

> 带参考标记 `※` 的章节建议优先阅读
>
> 带星号 `*` 的章节或许可以暂时略过

```bash
考前关键词速记

定义：操作系统是指控制和管理整个计算机系统的硬件和软件资源，合理的组织、调度计算机的工作与资源的分配，进而为用户和其他软件提供方便接口与环境的程序集合。
特征：并发 共享 虚拟 异步
功能：处理机管理 存储器管理 设备管理 文件管理 接口管理
接口：命令 程序

单道：内存只有一道作业，CPU处理只一个
多道：内存有多道作业，在CPU中交替运行

分时：用户共享主机 人机交互
同时性 交互性 独立性 及时性
时间片轮转调度

实时：在时间限制内完成紧急任务，不需要时间片排队
硬实时 软实时
最早截止时间优先调度、最低松弛度优先调度

顺序执行：顺序、封闭、可再现
并发执行：间断、失去封闭、不可再现

进程是程序的执行过程，是系统进行资源分配和调度的独立单位
特征：动态 并发 独立 异步
状态：创建 就绪 执行 阻塞 终止

活动就绪--挂起--静止就绪
活动阻塞--挂起--静止阻塞

进程控制块PCB组织方式：线性、链接、索引
执行、就绪、阻塞、（空闲）队列指针

创建：分配进程号、申请PCB、分配资源、初始化PCB、插入就绪队列
阻塞：找到PCB，保护现场，插入等待队列，下处理机
唤醒：找到PCB，移出等待队列，插入就绪队列

进程通信：共享存储、消息传递、管道

线程：是独立调度的基本单位；也可并发；不拥有系统资源；共享进程的资源；切换开销小；支持多处理机

低级 中级 高级调度：进程 内存 作业

周转 = 完成 - 到达
带权周转 = 周转/运行 >= 1
响应比 = 1 + 等待/要求运行

只有时间片轮转、多级反馈队列是抢占的
先来先服务 FCFS
短作业优先 SJF
高响应比优先 HRRN
时间片轮转 RR
多级反馈队列 FB

RR：当一个时间片结束时，刚好有新任务到达，那么在队列中，新任务在被剥夺时间片任务的前面

最早截止时间优先包括抢占式和非抢占式
开始截止时间不是Deadline，在开始截止时间前开始任务即可
如果任务错过，那么该任务就取消

最低松弛度：抢占式
两任务松弛度一样时，选择先到的那个（先来先服务）

死锁
原因：竞争资源、进程顺序非法、信号量使用不当
条件：互斥、不剥夺、请求并保持、循环等待

资源分配图
框：一类资源
圆圈：进程
框内圆圈数：资源数
要求几个资源就画几条分配边
进程出去的边为请求，进来的为已分配

银行家算法：
Process Work Need Allocation Work+=Allocation Finish
Allocation 已分配的资源
Need 还需要的资源
Work 系统剩余资源

进程同步 临界区准则：空闲让进、忙则等待、有限等待、让权等待

信号量 semaphore 不要忘记while循环

编译、链接、装入
绝对装入、可重定位装入、动态运行时装入
静态链接、装入时动态链接、运行时动态链接

内存分配：单一连续分配、固定分区分配、动态分区分配、动态重定位分区分配（紧凑）
首次适应：空闲分区 地址递增
邻近适应：地址递增，从上次查找结束位置查找
最佳适应：最小的满足要求的
最坏适应：最大的满足要求的

分页存储 地址变换机构
【页表寄存器：页表起始地址、页表长度】【越界中断】【逻辑地址：页号、页内偏移量】
【页表：页号->块号】【物理地址：块号、页内偏移量、物理地址】
页表起始地址+页号=页号
页表长度 < 页号 => 越界中断
块号 指向 物理地址
偏移量 指向 物理地址

页号=逻辑地址/页面大小
偏移量=逻辑地址%页面大小

请求分页 页表：状态位（是否调入内存）、访问次数、修改位、外存地址
内存分配策略：固定分配局部置换、可变分配全局置换、可变分配局部置换
一个程序的内存分配是固定/可变的，发生页面置换时仅限于自己的帧内/全局

页面置换算法：
最佳OPT，先进先出FIFO，最近最久未使用LRU，最少使用LFU，时钟置换CLOCK

请求分段 段表：比分页增加存取方式（权限）、增补位（是否有动态增长）

共享和保护功能

设备控制表 控制器控制表 通道控制表 系统设备表

安全分配：进程发出IO请求后就阻塞
逻辑设备表：逻辑设备名、物理设备名、驱动程序地址

SPOOLing：
缓冲区申请空闲块、暂存打印数据
申请空白用户请求打印表、填入打印数据、加入假脱机文件队列

缓冲区的目的：
缓和CPU与IO速度不匹配、减少中断、解决数据粒度不匹配、提高并行
单缓冲、双缓冲、循环缓冲、缓冲池

磁盘调度：先来先服务FCFS
最短寻道时间优先 SSTF
扫描 SCAN 循环扫描 C-SCAN

磁盘访问时间＝寻道时间＋旋转延迟时间＋数据传输时间

文件、记录、数据项

文件系统层次结构：文件系统接口、对对象进行操纵和管理的软件集合、对象及其属性
对象：文件、目录、磁盘存储空间
软件集合：IO控制、基本文件系统、文件组织模块、逻辑文件系统
接口：命令、程序

打开文件表：文件指针、计数、磁盘位置、权限
无结构文件、顺序、索引、索引顺序（分块查找）、哈希
文件控制块 FCB：基本信息、权限、使用信息
磁盘索引结点、内存索引结点
单级目录、两级、树形、无环图
线性检索、哈希

外存：连续分配、隐式链接（单链表）、显式链接 文件分配表 FAT、索引分配、混合索引分配
FAT的表项与全部磁盘块一一对应
FAT表项的长度取半个字节(4bit)的整数倍

文件存储空间：空闲表、空闲链表（空闲盘块链、空闲盘区链）、位示图、成组链接
```



## 第 1 章 操作系统概述

### 1.1 概念

#### 1.1.1 定义 ※

![image-20240105131334668](https://media.opennet.top/i/2024/01/05/lll9ao-0.png)

#### 1.1.2 特征 ※

并发和共享是最基本的特征

![image-20240105131527806](https://media.opennet.top/i/2024/01/05/lmi3wv-0.png)

![image-20240105131644509](https://media.opennet.top/i/2024/01/05/lnfsxj-0.png)

![image-20240105131806414](https://media.opennet.top/i/2024/01/05/lo64ou-0.png)

![image-20240105131851796](https://media.opennet.top/i/2024/01/05/looca6-0.png)

#### 1.1.3 目标和功能 ※

![image-20240105131944030](https://media.opennet.top/i/2024/01/05/lp7rac-0.png)

接口分为命令接口和程序接口

命令接口分为联机（交互式）、脱机（批处理）

程序接口由系统调用组成

### 1.2 发展历程

#### 1.2.1 手工

![image-20240105133546447](https://media.opennet.top/i/2024/01/05/lyrnb5-0.png)

#### 1.2.2 批处理 ※

![image-20240105133624640](https://media.opennet.top/i/2024/01/05/lyzrqp-0.png)

![image-20240105133647601](https://media.opennet.top/i/2024/01/05/lzd7ad-0.png)

![image-20240105133712491](https://media.opennet.top/i/2024/01/05/lzivoy-0.png)

#### 1.2.3 分时 ※

![image-20240105134009989](https://media.opennet.top/i/2024/01/05/m1ajrc-0.png)

![image-20240105134017262](https://media.opennet.top/i/2024/01/05/m1bx7q-0.png)

#### 1.2.4 实时 ※

![image-20240105134129487](https://media.opennet.top/i/2024/01/05/m28vp8-0.png)

#### 题目

单道批处理系统和多道批处理系统的区别

![image-20240105134349624](https://media.opennet.top/i/2024/01/05/m3jwx5-0.png)

分时操作系统和实时操作系统的区别

![image-20240105134505074](https://media.opennet.top/i/2024/01/05/m48ld8-0.png)

## 第 2 章 进程的描述与控制

### 2.1 前驱图和程序执行

#### 2.1.1 前驱图

![image-20231116192713336](https://media.opennet.top/i/2023/11/16/vvdxpr-0.png)

#### 2.1.2 程序顺序执行

顺序性、封闭性、可再现性

#### 2.1.3 程序并发执行

间断性、失去封闭性、不可再现性

### 2.2 进程的描述

#### 2.2.1 进程的定义与特征

![image-20231116193126917](https://media.opennet.top/i/2023/11/16/vxv1tj-0.png)

特征：动态性、并发性、独立性、异步性

#### 2.2.2 进程的状态与转换 ※

![image-20231116193508421](https://media.opennet.top/i/2023/11/16/w055fw-0.png)

![image-20231116193529034](https://media.opennet.top/i/2023/11/16/w08vxf-0.png)

#### 2.2.3 挂起操作*

就绪、阻塞状态可以被挂起

![image-20231116193816368](https://media.opennet.top/i/2023/11/16/w1z25l-0.png)

![image-20231116193914940](https://media.opennet.top/i/2023/11/16/w2juep-0.png)

#### 2.2.4 进程管理中的数据结构

**PCB 进程控制块**

![image-20231116194342949](https://media.opennet.top/i/2023/11/16/w53eg2-0.png)

**组织方式**

线性、链接、索引

![image-20231116194610008](https://media.opennet.top/i/2023/11/16/w6p8y8-0.png)

### 2.3 进程控制

#### 2.3.1 进程的创建

![image-20231116194844457](https://media.opennet.top/i/2023/11/16/w838rc-0.png)

#### 2.3.2 进程的终止

![image-20231116195014923](https://media.opennet.top/i/2023/11/16/w93wuy-0.png)

#### 2.3.3 进程的阻塞和唤醒 ※

阻塞：找到PCB，保护现场，将PCB插入等待队列，下处理机

唤醒：找到PCB，移出等待队列，插入就绪队列

![image-20231116195218754](https://media.opennet.top/i/2023/11/16/wacdsc-0.png)

![image-20231116195259541](https://media.opennet.top/i/2023/11/16/wat8o4-0.png)

#### 2.3.4 进程的挂起和激活*

![image-20231116195408372](https://media.opennet.top/i/2023/11/16/wbg9r9-0.png)

### 2.4 进程通信

#### 2.4.1 进程通信的类型

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

### 2.5 线程

#### 2.5.1 线程的引入

![image-20231116200638157](https://media.opennet.top/i/2023/11/16/x6kekn-0.png)

![image-20231116200654772](https://media.opennet.top/i/2023/11/16/x6nyjh-0.png)

#### 2.5.2 线程与进程的比较 ※

![image-20240105135842792](https://media.opennet.top/i/2024/01/05/mcfz8l-0.png)

#### 2.5.3 线程状态与线程控制块*

![image-20231116201618775](https://media.opennet.top/i/2023/11/16/xceo4v-0.png)

![image-20231116202447189](https://media.opennet.top/i/2023/11/16/xhcati-0.png)

### 2.6 线程的实现*

#### 2.6.1 线程的实现方式*

![image-20231116202113846](https://media.opennet.top/i/2023/11/16/xfcvwl-0.png)

**用户级线程**

![image-20231116202126932](https://media.opennet.top/i/2023/11/16/xfg1lx-0.png)

![image-20231116202145532](https://media.opennet.top/i/2023/11/16/xfjj07-0.png)

**内核级线程**

![image-20231116202245275](https://media.opennet.top/i/2023/11/16/xg588m-0.png)

**组合方式**

![image-20231116202409376](https://media.opennet.top/i/2023/11/16/xh49ya-0.png)

#### 2.6.3 线程的创建和终止*

![image-20231116202553947](https://media.opennet.top/i/2023/11/16/xhz2zf-0.png)

## 第 3 章 处理机调度与死锁

### 3.1 处理机调度概述

#### 3.1.1 处理机调度的层次 ※

越底层越低级

低级调度：进程

中级调度：内存

高级调度：作业

#### 3.1.3 进程调度

![image-20231116205134672](https://media.opennet.top/i/2023/11/16/xxd0ry-0.png)

![image-20231116205255493](https://media.opennet.top/i/2023/11/16/xybafc-0.png)

#### 3.1.4 性能指标 ※

![image-20231116205429423](https://media.opennet.top/i/2023/11/16/xz43jx-0.png)

### 3.2 调度算法 ※

只有与时间片轮转相关的算法是抢占的

![image-20231116214138669](https://media.opennet.top/i/2023/11/16/zeygq5-0.png)

#### 3.2.1 先来先服务 FCFS ※

First Come First Serve

非抢占式

简单、低效、长作业有利、CPU繁忙型有利

![image-20231116212059976](https://media.opennet.top/i/2023/11/16/z2thlx-0.png)

![image-20231116212111191](https://media.opennet.top/i/2023/11/16/z2w7ia-0.png)

#### 3.2.2 短作业优先 SJF ※

Short Job First

默认非抢占式

短作业有利，饥饿

![image-20231116212644135](https://media.opennet.top/i/2023/11/16/z6e9b4-0.png)

#### 3.2.3 优先级 ※

Priority-Scheduling

![image-20231116212906154](https://media.opennet.top/i/2023/11/16/z7murf-0.png)

**高响应比优先 Highest Response Ratio Next**

非抢占式

短作业有利，不饥饿

![image-20231116213235943](https://media.opennet.top/i/2023/11/16/z9l5f7-0.png)

#### 3.2.4 时间片轮转 ※

Round Robin

抢占式

注意就绪队列的排序方法是先来先服务

当一个时间片结束时，刚好有新任务到达，那么在队列中，新任务在被剥夺时间片任务的前面

![image-20231116213350818](https://media.opennet.top/i/2023/11/16/za9leq-0.png)

![image-20231116213409955](https://media.opennet.top/i/2023/11/16/zam412-0.png)

#### 3.2.5 多级队列

Multileved Queue

![image-20231116213852992](https://media.opennet.top/i/2023/11/16/zd98uk-0.png)

#### 3.2.6 多级反馈队列

Multileved Feedback Queue, FB

![image-20231116214041741](https://media.opennet.top/i/2023/11/16/zee4lv-0.png)

![image-20231116214101385](https://media.opennet.top/i/2023/11/16/zeqk1h-0.png)

#### 题目

 假设一个系统中有5个进程，它们达到时间和服务时间如图所示，忽略I/O及其他开销时间，若分别按先来先服务（FCFS）、非抢占式及抢占式短进程优先（SPF）、高响应比优先（HRRN）、时间片轮转（RR，时间片大小为1）、 ~~多反馈队列调度算法（FB，第i及队列的时间片=2i-1）~~ 进行CPU调度，请给出各进程的完成时间、周转时间、等待时间、带权周转时间。

![image-20240104153235196](https://media.opennet.top/i/2024/01/04/p816c1-0.png)

![image-20240104153101929](https://media.opennet.top/i/2024/01/04/p7047v-0.png)

![image-20240104153712377](https://media.opennet.top/i/2024/01/04/pano6n-0.png)

![image-20240104154242366](https://media.opennet.top/i/2024/01/04/pe0ztf-0.png)

![image-20240104154714414](https://media.opennet.top/i/2024/01/04/pglvzg-0.png)

![image-20240104160136689](https://media.opennet.top/i/2024/01/04/ppb5k7-0.png)

### 3.3 实时调度

#### 3.3.3 最早截止时间优先 ※

开始截止时间不是Deadline，在开始截止时间前开始任务即可

如果任务错过，那么该任务就取消

抢占式、非抢占式都有

![image-20231116214851284](https://media.opennet.top/i/2023/11/16/zknqyd-0.png)

![image-20231116215242040](https://media.opennet.top/i/2023/11/16/zljpnz-0.png)

![image-20231116215325418](https://media.opennet.top/i/2023/11/16/zm0yry-0.png)

![image-20231116215333916](https://media.opennet.top/i/2023/11/16/zm383u-0.png)

![image-20231116215356974](https://media.opennet.top/i/2023/11/16/zmguw8-0.png)

#### 3.3.4 最低松弛度优先 ※

抢占式

两任务松弛度一样时，选择先到的那个（先来先服务）

![image-20231116215530960](https://media.opennet.top/i/2023/11/16/zna7fw-0.png)

![image-20231116215549177](https://media.opennet.top/i/2023/11/16/zndw96-0.png)

#### 题目

对下面的5个非周期性实时任务，按最早开始截止时间优先调度算法应如何进行CPU调度？

![image-20240104161443892](https://media.opennet.top/i/2024/01/04/qkwldw-0.png)

![image-20240104161428981](https://media.opennet.top/i/2024/01/04/qktbrf-0.png)

![image-20240104161738462](https://media.opennet.top/i/2024/01/04/qmnrnw-0.png)

![img](https://media.opennet.top/i/2024/01/04/qkyxmk-0.png)

若有3个周期性任务，任务A要求每20ms执行一次，执行时间为10ms；任务B要求每50ms执行一次，执行时间为10ms；任务C要求每50ms执行一次，执行时间为15ms，应如何按最低松弛度优先算法对它们进行CPU调度？

![image-20240104163625696](https://media.opennet.top/i/2024/01/04/qxwcxg-0.png)

![img](https://media.opennet.top/i/2024/01/04/qxxsep-0.png)

### 3.5 死锁

#### 3.5.1 资源问题

可重用资源：eg 设备、文件

可消耗资源：eg 进程间通信的信息

可抢占资源：eg 处理机、内存

不可抢占资源：eg 磁带机、打印机

#### 3.5.2 死锁产生的原因

![image-20231116220343748](https://media.opennet.top/i/2023/11/16/10fx9qv-0.png)

#### 3.5.3 死锁的定义、条件和处理 ※

![image-20231116220509465](https://media.opennet.top/i/2023/11/16/10gwb7u-0.png)

![image-20231116220621855](https://media.opennet.top/i/2023/11/16/10hkeur-0.png)

![image-20231116220726985](https://media.opennet.top/i/2023/11/16/10i7d4p-0.png)

![image-20231116220814908](https://media.opennet.top/i/2023/11/16/10iq6yk-0.png)

![image-20231116220838896](https://media.opennet.top/i/2023/11/16/10iv0rv-0.png)

#### 3.5.4 资源分配图 ※

![image-20231116223653605](https://media.opennet.top/i/2023/11/16/10zlmsf-0.png)

### 3.6 死锁预防

![image-20231116221943559](https://media.opennet.top/i/2023/11/16/10pgk0a-0.png)

### 3.7 死锁避免

#### 3.7.1 系统安全状态 ※

![image-20231116222213550](https://media.opennet.top/i/2023/11/16/10r27tj-0.png)

#### 3.7.2 银行家算法 ※

**安全性算法**

![image-20231116222850785](https://media.opennet.top/i/2023/11/16/10v3olo-0.png)

![image-20231116223042329](https://media.opennet.top/i/2023/11/16/10w0168-0.png)

![image-20231116223205479](https://media.opennet.top/i/2023/11/16/10wyltz-0.png)

![image-20231116223221771](https://media.opennet.top/i/2023/11/16/10x1608-0.png)

#### 题目

Allocation 已分配的资源

Need 还需要的资源

Work 系统剩余资源

P2提出Request的意思是要求系统立即给它Request的资源

![image-20240104164606646](https://media.opennet.top/i/2024/01/04/r3hpu2-0.png)

**（1）该状态是否安全？
（2）若进程P2提出请求Request（1，2，2，2）后，系统能否将资源分配给它？**

![image-20240104170612905](https://media.opennet.top/i/2024/01/04/rffq6a-0.png)

![image-20240104170800384](https://media.opennet.top/i/2024/01/04/s4cwbr-0.png)

![image-20240104170810545](https://media.opennet.top/i/2024/01/04/s4f68q-0.png)

在银行家算法中,若出现下面的资源分配情况：

```
Process          Allocation           Need             Available
PO               0 0 3 2            0 0 1 2             1 6 2 2
P1               1 0 0 0            1 6 5 0
P2               1 3 5 4            2 3 5 6
P3               0 0 3 2            0 6 5 2
P4               0 0 1 4            0 6 5 6
```

(1)该状态是否安全?      

(2)若进程P2提出请求Request(1，2，2，2)后，系统能否将资源分配给它？

(3)如果系统立即满足P2的上述请求，请问，系统是否立即进入死锁状态?

(1)是，可以找到安全序列{P0,P3,P1,P2,P4}

(2)P2发出请求向量Request(1,2,2,2)后,系统按银行家算法进行检查:

①Request’(1,2,2,2) <=Need2(2,3,5,6)

②Request‘(1,2,2,2)<=Available(1,5,2,2)

③系统先假定可为P2分配资源并修改

Available=(0,3,0,0)

Allocation’=(2,5,7,6)

Need‘=(1,1,3,4)

④进行安全性检查:此时对所有的进程,条件Need_i<=Available(0,3,0,0)都不成立,即Available不能满足任何进程的请求,故系统进入不安全状态。

此时当进程P2提出请求Request(1,2,2,2)后,系统不能将资源分配给它。

(3)并没有马上进入死锁，因为上述进程没有申请新资源并因得不到资源而阻塞。只有当提出新的请求并导致所有没有执行完的多个进程因得不到资源而阻塞时，才死锁。

### 3.8 死锁的检测与解除

#### 3.8.1 死锁的检测 ※

![image-20231116223825740](https://media.opennet.top/i/2023/11/16/110mm2l-0.png)

#### 3.8.2 死锁的解除

![image-20231116223948933](https://media.opennet.top/i/2023/11/16/111d5fk-0.png)

## 第 4 章 进程同步

### 4.1 进程同步的基本概念

#### 4.1.1 进程同步概念的引入

![image-20231116224702880](https://media.opennet.top/i/2023/11/16/115umxr-0.png)

![image-20231116224926532](https://media.opennet.top/i/2023/11/16/1176cix-0.png)

![image-20231116224934340](https://media.opennet.top/i/2023/11/16/117842h-0.png)

#### 4.1.2 临界区问题

![image-20231116224815899](https://media.opennet.top/i/2023/11/16/116iu4g-0.png)

![image-20231116225152456](https://media.opennet.top/i/2023/11/16/118ixc3-0.png)

### 4.2 软件同步机制

![image-20231116225614099](https://media.opennet.top/i/2023/11/16/11ba3aq-0.png)

### 4.3 硬件同步机制

![image-20231116225727284](https://media.opennet.top/i/2023/11/16/11by19d-0.png)

![image-20231116225841583](https://media.opennet.top/i/2023/11/16/11cmu8e-0.png)

![image-20231116225922187](https://media.opennet.top/i/2023/11/16/11d3xjq-0.png)

![image-20231116225938363](https://media.opennet.top/i/2023/11/16/11d78hb-0.png)

### 4.4 信号量机制

#### 4.4.1 信号量机制介绍 ※

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

#### 4.4.2 信号量的应用 ※

![image-20231116231845747](https://media.opennet.top/i/2023/11/16/12cdnm0-0.png)

![image-20231116231954339](https://media.opennet.top/i/2023/11/16/12d0oui-0.png)

### 4.5 管程*

**管程的定义**

![image-20231116232323399](https://media.opennet.top/i/2023/11/16/12f7sie-0.png)

![image-20231116232336515](https://media.opennet.top/i/2023/11/16/12falmh-0.png)

**条件变量**

![image-20231116232517709](https://media.opennet.top/i/2023/11/16/12gdcmf-0.png)

![image-20231116232530078](https://media.opennet.top/i/2023/11/16/12gfzo4-0.png)

![image-20231116232537110](https://media.opennet.top/i/2023/11/16/12ghkw2-0.png)

### 4.6 经典的进程同步问题

#### 4.6.1 生产者-消费者问题 ※

![image-20231116233208058](https://media.opennet.top/i/2023/11/16/12khom2-0.png)

![image-20231116233339249](https://media.opennet.top/i/2023/11/16/12l9ooo-0.png)

![image-20231117092000107](https://media.opennet.top/i/2023/11/17/f7sjxn-0.png)

![image-20231117092011142](https://media.opennet.top/i/2023/11/17/f7uoom-0.png)

#### 4.6.2 哲学家进餐问题 ※

![image-20231117092150252](https://media.opennet.top/i/2023/11/17/f8opg3-0.png)

![image-20231117092332246](https://media.opennet.top/i/2023/11/17/f9scrr-0.png)

![image-20231117092411580](https://media.opennet.top/i/2023/11/17/fa8zro-0.png)

#### 4.6.3 读者-写者问题 ※

![image-20231117092606445](https://media.opennet.top/i/2023/11/17/fbe8km-0.png)

![image-20240104103417958](https://media.opennet.top/i/2024/01/04/gz7jss-0.png)

![image-20240104103450976](https://media.opennet.top/i/2024/01/04/gzmv99-0.png)

![image-20240104103522534](https://media.opennet.top/i/2024/01/04/h02az2-0.png)

#### 题目

试用记录型信号量写出一个不会死锁的哲学家进餐问题的算法。

```c
semaphore chopsticks[]={1,1,1,1,1};
semaphore maxNum=4;
void philosopher(int i){
    while(true){
        wait(maxNum);
    	wait(chopsticks[i]);
    	wait(chopsticks[(i+1)%5]);
    	进餐();
    	signal(chopsticks[i]);
    	signal(chopsticks[(i+1)%5]);
    	signal(maxNum);
        思考();
    }
}
```

嗜睡的理发师问题：一个理发店由一个有**N张沙发的等候室**和—个放**一张理发椅的理发室**组成。没有顾客要理发时，理发师便去睡觉。当—个顾客走进理发店时，如果所有的沙发都已被占用，**他便离开理发店**；否则，如果理发师正在为其他顾客理发，则该顾客就找一张空沙发坐下等待；如果理发师因无顾客正在睡觉，则由新到的顾客唤醒理发师为其理发。在理发完成后，顾客必须付费，**直到**理发师收费后才能离开理发店。试用信号量实现这一同步问题。

```c
int sofaUsed=0;
semaphore sofaUsedMutex=0;
semaphore wake = 0;
semaphore beginPay=0, endPay=0;
semaphore cutRoom=0;

void customer(){
	wait(sofaUsedMutex);//等待修改sofaUsed
    if(sofaUsed>=N){
        signal(sofaUsedMutex);
        离开理发店;
    }else{
        sofaUsed++;
        signal(sofaUsedMutex);
        
        wait(cutRoom);//等待进入理发室
        wait(sofaUsedMutex); sofaUsed--; signal(sofaUsedMutex);
        signal(wake);//唤醒理发师
        理发;
        signal(beginPay);//通知理发师,我付费了
        wait(endPay);//等待理发师收费
        signal(cutRoom);//离开理发室
        
        离开理发店;
    }
}

void barber(){
    while(true){
        wait(wake);//等待唤醒
    	给顾客理发;
    	wait(beginPay);//等待顾客付费
    	signal(endPay);//通知顾客已收费
    }
}
```

某车站售票厅，任何时刻最多可容纳20名购票者进入，当售票厅中少于20名购票者时，则厅外的购票者可立即进入，否则需在外面等待。若把一个购票者看作一个进程，请回答下列问题：

(1)用PV操作管理这些并发进程时，应怎样定义信号量，写出信号量的初值以及信号量各种取值的含义。

(2)根据所定义的信号量，把应执行的wait/signal操作填入下面空中，以保证进程能够正确地并发执行。

```
    parbegin  pmcess  PI(I＝1,2,....)
        begin
        (_______)
        进入售票厅
        购票
        退出； 
        (_______)
        end；
    parend;
```

答：

(1) 定义一信号量S，初始值为20。

S>0时s的值表示可继续进入售票厅的人数

S＝0时表示售票厅中已有20名顾客

S<0则|S|值为等待进入售票厅的人数

(2) 上框为P(S)、下框为V(S)

![image-20240104130558119](https://media.opennet.top/i/2024/01/04/kt7a1g-0.png)

```c
semaphore plate=1, apple=0, orange=0;
void father(){
	while(true){
        wait(plate);//等待获取盘子
        放苹果;
        signal(apple);//通知吃苹果
    }
}
void mother(){
	while(true){
        wait(plate);
        xxx;
        signal(banana);
    }
}
void son(){
    while(true){
        wait(orange);//等待吃橘子
        吃橘子;
        signal(plate);//通知父母拿盘子
    }
}
void daughter(){
    while(true){
        wait(apple);
        xxx;
        signal(plate);
    }
}
```



![image-20240104130617572](https://media.opennet.top/i/2024/01/04/ktbk6h-0.png)

有P1，P2，…，Pm等m个生产者进程和CA，CB两个消费者进程。它们共享可存放一个产品的缓冲区BUFFER。序号为奇数的生产者进程生产的产品供CA消费，而序号为偶数的生产者进程生产的产品供CB消费，CA或CB一旦取出产品，则各生产者均有权申请向BUFFER存放产品。试用PV操作正确实现进程的并发执行.

```c
semaphore buffCA=0, buffCB=0, buff=1;

void P(int i){
	while(true){
        生产;
        wait(buff);
        将产品放入缓冲区;
        if(i%2==1) signal(buffCA);
        else signal(buffCB);
    }
}

void CA(){
    while(true){
        wait(buffCA);
        从缓冲区取出产品;
        signal(buff);
        消费;
    }
}

void CB(){
    while(true){
        wait(buffCB);
        从缓冲区取出产品;
        signal(buff);
        消费;
    }
}
```



## 第 5 章 存储器管理

###  5.1 存储器的层次结构

![image-20231130162140267](https://media.opennet.top/i/2023/11/30/qs02wf-0.png)

### 5.2 程序的装入与链接

![image-20231130162414052](https://media.opennet.top/i/2023/11/30/qtegqa-0.png)

![image-20231130162438207](https://media.opennet.top/i/2023/11/30/qts8h3-0.png)

#### 5.2.1 地址绑定和内存保护

![image-20231130162659828](https://media.opennet.top/i/2023/11/30/qv3rym-0.png)

![image-20231130162710358](https://media.opennet.top/i/2023/11/30/qv6drg-0.png)

![image-20231130163013731](https://media.opennet.top/i/2023/11/30/qwyxig-0.png)

![image-20231130163025075](https://media.opennet.top/i/2023/11/30/qxan22-0.png)

#### 5.2.2 程序的装入

![image-20231130163422110](https://media.opennet.top/i/2023/11/30/qzod0x-0.png)

![image-20231130163446758](https://media.opennet.top/i/2023/11/30/qzs6po-0.png)

#### 5.2.3 程序的链接

![image-20231130164337657](https://media.opennet.top/i/2023/11/30/r53unh-0.png)

### 5.3 对换与覆盖

![image-20240105142331866](https://media.opennet.top/i/2024/01/05/nf2km8-0.png)

#### 5.3.3 进程的换出和换入

![image-20240105142552415](https://media.opennet.top/i/2024/01/05/ngdvpf-0.png)

![image-20240105142601232](https://media.opennet.top/i/2024/01/05/ngfsxj-0.png)

### 5.4 连续分配存储管理方式

![image-20231130164658425](https://media.opennet.top/i/2023/11/30/r701ex-0.png)

#### 5.4.1 单一连续分配

![image-20231130165847623](https://media.opennet.top/i/2023/11/30/re2wqz-0.png)

#### 5.4.2 固定分区分配

![image-20231130170016336](https://media.opennet.top/i/2023/11/30/revsmo-0.png)

#### 5.4.3 动态分区分配 ※

![image-20231130201128978](https://media.opennet.top/i/2023/11/30/x84it2-0.png)

![image-20231130201145659](https://media.opennet.top/i/2023/11/30/x89z14-0.png)

![image-20231130201213265](https://media.opennet.top/i/2023/11/30/x8g87n-0.png)

#### 5.4.4 动态重定位分区分配

![image-20231130201442256](https://media.opennet.top/i/2023/11/30/xa1h0l-0.png)

![image-20231130202526991](https://media.opennet.top/i/2023/11/30/xghrde-0.png)

![image-20231130202554629](https://media.opennet.top/i/2023/11/30/xgn6rv-0.png)

#### 题目

某系统采用动态分区分配方式管理内存，内存空间为640K，高端40K用来存放操作系统。在内存分配时，系统优先使用空闲区低端的空间。对下列的请求序列：作业l申请130K、作业2申请60K、作业3申请100K、作业2释放60K、作业4申请200K、作业3释放100K、作业1释放130K、作业5申请140K、作业6申请60K、作业7申请50K、作业6释放60K，请分别画图表示出使用首次适应算法和最佳适应算法进行内存分配和回收后内存的实际使用情况。

> 实际过程不用那么复杂，草稿纸上模拟一下算法，很快能得出答案

![Screenshot_2024_01_04_18_55_39_15_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/04/ukuisq-0.jpg)

![Screenshot_2024_01_04_18_55_48_90_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/04/ul0jn7-0.jpg)

### 5.5 分页存储管理方式

![image-20231130202730865](https://media.opennet.top/i/2023/11/30/xhoogb-0.png)

#### 5.5.1 分页存储管理的基本方法 ※

![image-20231130203621940](https://media.opennet.top/i/2023/11/30/xn0i3v-0.png)

![image-20231130203649832](https://media.opennet.top/i/2023/11/30/xn5f2w-0.png)

#### 5.5.2 地址变换机构 ※

![image-20231130204241884](https://media.opennet.top/i/2023/11/30/xqp1rp-0.png)

![image-20231130204325833](https://media.opennet.top/i/2023/11/30/xr5zig-0.png)

![image-20231130204700125](https://media.opennet.top/i/2023/11/30/xt66l1-0.png)

![image-20231130205106587](https://media.opennet.top/i/2023/11/30/xvln4r-0.png)

![image-20231130205127799](https://media.opennet.top/i/2023/11/30/xw6byn-0.png)

![image-20231130205217879](https://media.opennet.top/i/2023/11/30/xw8ncn-0.png)

#### 5.5.3 引入快表后的内存有效访问时间*

![image-20231130205800018](https://media.opennet.top/i/2023/11/30/xzqvxv-0.png)

#### 5.5.4 两级页表和多级页表

![image-20231130210312873](https://media.opennet.top/i/2023/11/30/yqmra5-0.png)

![image-20231130210339184](https://media.opennet.top/i/2023/11/30/yqzi7p-0.png)

#### 题目

已知某分页系统，主存容量为64K，页面大小为1K，对一个4页大的作业，其0、1、2、3页分别被分配到主存的2、4、6、7块中。

(1)将十进制的逻辑地址1023、2500、3500、4500转换成物理地址。

(2)以十进制的逻辑地址1023为例画出地址变换过程图。

![image-20240104192250159](https://media.opennet.top/i/2024/01/04/vob7zi-0.png)

### 5.6 分段存储管理方式

#### 5.6.1 分段存储管理方式的引入

![image-20231130210507254](https://media.opennet.top/i/2023/11/30/yrq2di-0.png)

#### 5.6.2 分段系统的基本原理 ※

![image-20231130211125158](https://media.opennet.top/i/2023/11/30/yvno4p-0.png)

![image-20231130211204353](https://media.opennet.top/i/2023/11/30/yvvd9u-0.png)

![image-20231130211214196](https://media.opennet.top/i/2023/11/30/yvy0xf-0.png)

![image-20231130211424071](https://media.opennet.top/i/2023/11/30/yxgjrj-0.png)

#### 5.6.3 信息共享

![image-20231130211732739](https://media.opennet.top/i/2023/11/30/yzawdh-0.png)

#### 题目

![Screenshot_2024_01_04_19_27_04_76_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/04/vr5ikg-0.jpg)

### 5.7 段页式存储管理方式

![image-20231130214437553](https://media.opennet.top/i/2023/11/30/zfedjj-0.png)

![image-20231130214458861](https://media.opennet.top/i/2023/11/30/zfjf3o-0.png)

![image-20231130214521737](https://media.opennet.top/i/2023/11/30/zfn6ec-0.png)

## 第 6 章 虚拟存储器

### 6.1 虚拟存储器概述

#### 6.1.1 传统存储器和局部性原理

![image-20231130215220741](https://media.opennet.top/i/2023/11/30/zk2jg4-0.png)

#### 6.1.2 虚拟存储器的定义和特征

![image-20231130215723043](https://media.opennet.top/i/2023/11/30/zn1dny-0.png)

![image-20231130220451754](https://media.opennet.top/i/2023/11/30/10f69a4-0.png)

#### 6.1.3 虚拟存储器的实现方法

![image-20231130220608632](https://media.opennet.top/i/2023/11/30/10fv8py-0.png)

### 6.2 请求分页存储管理方式

![image-20231130220738546](https://media.opennet.top/i/2023/11/30/10gvtpx-0.png)

#### 6.2.1 请求分页中的硬件支持

![image-20231130220824600](https://media.opennet.top/i/2023/11/30/10hemjp-0.png)

![image-20231130220839885](https://media.opennet.top/i/2023/11/30/10hh1v3-0.png)

![image-20231130221243272](https://media.opennet.top/i/2023/11/30/10jw16f-0.png)

![image-20231130221345294](https://media.opennet.top/i/2023/11/30/10khjlq-0.png)

![image-20231130221354192](https://media.opennet.top/i/2023/11/30/10kjil6-0.png)

![image-20231130221404838](https://media.opennet.top/i/2023/11/30/10klvbi-0.png)

#### 6.2.2 请求分页中的内存分配

![image-20231130221647860](https://media.opennet.top/i/2023/11/30/10mbkb4-0.png)

![image-20231130222029661](https://media.opennet.top/i/2023/11/30/10olex5-0.png)

![image-20231130222101470](https://media.opennet.top/i/2023/11/30/10oqt00-0.png)

![image-20231130222110043](https://media.opennet.top/i/2023/11/30/10osp3e-0.png)

#### 6.2.3 页面调入策略

![image-20231130222232729](https://media.opennet.top/i/2023/11/30/10psd82-0.png)

![image-20231130222520248](https://media.opennet.top/i/2023/11/30/10r983j-0.png)

![image-20231130222617425](https://media.opennet.top/i/2023/11/30/10rtuwd-0.png)

### 6.3 页面置换算法

![image-20231130223933597](https://media.opennet.top/i/2023/11/30/10zwj29-0.png)

#### 6.3.1 最佳 先进先出 ※

![image-20231130224313998](https://media.opennet.top/i/2023/11/30/111xpnb-0.png)

![image-20231130224411521](https://media.opennet.top/i/2023/11/30/112je69-0.png)

![image-20231130224427335](https://media.opennet.top/i/2023/11/30/112u848-0.png)

#### 6.3.2 最近最久未使用 最少使用 ※

![image-20231130224648015](https://media.opennet.top/i/2023/11/30/1146827-0.png)

![image-20231130224741105](https://media.opennet.top/i/2023/11/30/114qxyh-0.png)

#### 6.3.3 Clock 页面置换算法

![image-20231130225223614](https://media.opennet.top/i/2023/11/30/117lfy5-0.png)

![image-20231130225244288](https://media.opennet.top/i/2023/11/30/117qft0-0.png)

![image-20231130225415039](https://media.opennet.top/i/2023/11/30/118hqrd-0.png)

![image-20231130225449742](https://media.opennet.top/i/2023/11/30/118xduq-0.png)

#### 6.3.5 请求分页系统的内存有效访问时间

![image-20231130225621077](https://media.opennet.top/i/2023/11/30/119ztfa-0.png)

#### 题目

在一个请求分页系统中，假如一个作业的页面走向为4，3，2，1，4，3，5，4，3，2，1，5，目前它还没有任何页装入内存，当分配给该作业的物理块数目M为3时，请分别计算采用OPT、LRU和FIFO页面淘汰算法时访问过程中所发生的缺页次数和缺页率，并比较所得的结果。

![在这里插入图片描述](https://media.opennet.top/i/2024/01/04/wbkgip-0.png)

FIFO：共发生 9次缺页中断 缺页率=9/12=75%
LRU：共发生 10次缺页中断 缺页率=10/12=83.3%
OPT：共发生 7次缺页中断 缺页率=7/12=58.3%

### 6.4 抖动与工作集

#### 6.4.1 抖动

![image-20231130225838063](https://media.opennet.top/i/2023/11/30/11b8zmh-0.png)

#### 6.4.2 工作集

![image-20231130225956932](https://media.opennet.top/i/2023/11/30/11byt1n-0.png)

### 6.5 请求分段存储管理方式

#### 6.5.1 请求分段中的硬件支持

![image-20240105151611825](https://media.opennet.top/i/2024/01/05/oy2qik-0.png)

![image-20240105151720879](https://media.opennet.top/i/2024/01/05/oyq4la-0.png)

![image-20240105151740737](https://media.opennet.top/i/2024/01/05/oz3067-0.png)

![image-20240105151801138](https://media.opennet.top/i/2024/01/05/oz7gmu-0.png)

#### 6.5.2 共享和保护

![image-20240105152138606](https://media.opennet.top/i/2024/01/05/p1gcif-0.png)

![image-20240105152158703](https://media.opennet.top/i/2024/01/05/p1kjwy-0.png)

## 第 7 章 输入/输出系统

### 7.5 与设备无关的I/O软件

#### 7.5.3 设备分配与回收 ※

![image-20240104235627417](https://media.opennet.top/i/2024/01/04/12ukfj5-0.png)

![image-20240104235638714](https://media.opennet.top/i/2024/01/04/12umqom-0.png)

![image-20240104235648513](https://media.opennet.top/i/2024/01/04/12up19z-0.png)

![image-20240104235657814](https://media.opennet.top/i/2024/01/04/12ur5gv-0.png)

![image-20240104235705113](https://media.opennet.top/i/2024/01/04/12usjd0-0.png)

#### 题目

简述设备分配与回收过程。

![Screenshot_2024_01_04_23_59_43_07_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/04/12wnmio-0.jpg)

#### 7.5.4 逻辑设备名映射到物理设备名 ※

![image-20240105120147479](https://media.opennet.top/i/2024/01/05/j36eps-0.png)

![image-20240105120244511](https://media.opennet.top/i/2024/01/05/j3r73h-0.png)

### 7.6 用户层的I/O软件

#### 7.6.2 假脱机系统 SPOOLing ※

![image-20240104232544455](https://media.opennet.top/i/2024/01/04/12c7fbl-0.png)

![image-20240104232554403](https://media.opennet.top/i/2024/01/04/12c9gdy-0.png)

![image-20240104232606784](https://media.opennet.top/i/2024/01/04/12cc2pp-0.png)

#### 题目

以打印机为例说明SPOOLing的工作原理，系统如何利用SPOOLing技术将打印机模拟为虚拟打印机。

### 7.7 缓冲区管理

#### 7.7.1 缓存和缓冲

![image-20240105125355014](https://media.opennet.top/i/2024/01/05/kmi2ub-0.png)

![image-20240105125505881](https://media.opennet.top/i/2024/01/05/kmncf0-0.png)

#### 7.7.2 单缓冲 双缓冲 ※

![image-20240105125821933](https://media.opennet.top/i/2024/01/05/kojefn-0.png)

![image-20240105130140693](https://media.opennet.top/i/2024/01/05/kqo2ia-0.png)

![image-20240105130239900](https://media.opennet.top/i/2024/01/05/kr9ql6-0.png)

#### 7.7.3 环形缓冲 ※

![image-20240105130456233](https://media.opennet.top/i/2024/01/05/ksjs48-0.png)

#### 7.7.4 缓冲池 ※

![image-20240105131114240](https://media.opennet.top/i/2024/01/05/lk1ni7-0.png)

![image-20240105131128926](https://media.opennet.top/i/2024/01/05/lkdf5h-0.png)

### 7.8 磁盘性能和调度

#### 7.8.1 概述

![image-20240104211827784](https://media.opennet.top/i/2024/01/04/ywvba7-0.png)

![image-20240104211837217](https://media.opennet.top/i/2024/01/04/ywx3a6-0.png)

![image-20240104211848062](https://media.opennet.top/i/2024/01/04/ywzhvi-0.png)

![image-20240104205547206](https://media.opennet.top/i/2024/01/04/xvgwyb-0.png)

![image-20240104205557839](https://media.opennet.top/i/2024/01/04/xvjf2j-0.png)

#### 7.8.2 先来先服务 最短寻道时间优先 ※

![image-20240104205625727](https://media.opennet.top/i/2024/01/04/xvxy6v-0.png)

![image-20240104205702561](https://media.opennet.top/i/2024/01/04/xw5vb6-0.png)

#### 7.8.3 扫描 循环扫描 ※

![image-20240104210013247](https://media.opennet.top/i/2024/01/04/xy09po-0.png)

![image-20240104210022412](https://media.opennet.top/i/2024/01/04/xyb0yj-0.png)

#### 题目

假设磁盘有200个磁道，磁道请求对列中是一些随机请求，它们按照到达的次序分别处于55、58、39、18、90、160、150、38、184号磁道上，当前磁头在100号磁道上，并向磁道号增加的方向上移动。请给出按FCFS、SSTF、SCAN及CSCAN算法进行磁盘调度时满足请求的次序，并计算出它们的平均寻道长度。

![Screenshot_2024_01_04_21_14_23_14_a6a4b4a15f5a4604d9f3d59bae0c772c](https://media.opennet.top/i/2024/01/04/yum7kf-0.jpg)

假定磁盘转速为20ms/圈，磁盘格式化时每个磁道被划分成10个扇区，今有10个逻辑记录（每个记录的大小刚好与扇区大小相等）存放在同一个磁道上，处理程序每次从磁盘读出一个计录后要花4ms进行处理，现要求顺序处理这10个记录，若磁头现在正处于首个逻辑记录的始点位置。请问：

（1）按逆时针方向安排10个逻辑记录（磁盘顺时针方向转），处理程序处理完这10个记录所花费的时间是多少？

（2）按最优化分布重新安排这10个逻辑记录，写出记录的安排，并计算出所需要处理的时间。

 [提示]数据处理时间＝磁盘访问时间＋数据实际处理时间，而磁盘访问时间＝寻道时间＋旋转延迟时间＋数据传输时间。本题通过对旋转延迟时间的优化来提高访问磁盘数据的速度。

注意，此题的（1）有网上认为答案是 `6+(12+2+4)*9 = 168ms`

![image-20240104213631180](https://media.opennet.top/i/2024/01/04/z7m002-0.png)

## 第 8 章 文件管理

### 8.1 文件和文件系统

#### 8.1.1 文件、记录和数据项

![image-20240105103925229](https://media.opennet.top/i/2024/01/05/h265ot-0.png)

#### 8.1.2 文件类型

系统文件、用户文件、库文件

源文件、目标文件、可执行文件

可执行文件、只读文件、读写文件

普通文件、目录文件、特殊文件

#### 8.1.3 文件系统的层次结构

![image-20240105104535424](https://media.opennet.top/i/2024/01/05/h61lf8-0.png)

对象：文件、目录、磁盘存储空间

软件集合：

![image-20240105104718813](https://media.opennet.top/i/2024/01/05/h6w8wf-0.png)

![image-20240105104826875](https://media.opennet.top/i/2024/01/05/h7jng0-0.png)

文件系统接口：命令接口、程序接口

#### 8.1.4 文件操作

![image-20240105105207455](https://media.opennet.top/i/2024/01/05/h9syhn-0.png)

![image-20240105105227188](https://media.opennet.top/i/2024/01/05/h9xcfk-0.png)

![image-20240105105239169](https://media.opennet.top/i/2024/01/05/ha89g6-0.png)

### 8.2 文件的逻辑结构

#### 8.2.1 无结构文件

![image-20240105105500608](https://media.opennet.top/i/2024/01/05/hbjr7t-0.png)

#### 8.2.2 顺序文件

![image-20240105105553355](https://media.opennet.top/i/2024/01/05/hc3q4f-0.png)

#### 8.2.3 索引文件

可以与外存的索引分配一起看

![image-20240105110648692](https://media.opennet.top/i/2024/01/05/himds7-0.png)

#### 8.2.4 索引顺序文件

分块查找

![image-20240105111023302](https://media.opennet.top/i/2024/01/05/i8fb8f-0.png)

![image-20240105111036037](https://media.opennet.top/i/2024/01/05/i8qowx-0.png)

#### 8.2.5 直接文件或哈希文件

![image-20240105111141918](https://media.opennet.top/i/2024/01/05/i9dggy-0.png)

### 8.3 文件目录

#### 8.3.1 文件控制块和索引节点

![image-20240105111556021](https://media.opennet.top/i/2024/01/05/ibu974-0.png)

![image-20240105111847716](https://media.opennet.top/i/2024/01/05/idkkpt-0.png)

![image-20240105111856969](https://media.opennet.top/i/2024/01/05/idmquv-0.png)

#### 8.3.2 简单的文件目录

![image-20240105112806313](https://media.opennet.top/i/2024/01/05/ij1ip2-0.png)

![image-20240105112819035](https://media.opennet.top/i/2024/01/05/ij4cu6-0.png)

![image-20240105112730156](https://media.opennet.top/i/2024/01/05/iiu0hl-0.png)

![image-20240105112842601](https://media.opennet.top/i/2024/01/05/iji2pm-0.png)

![image-20240105112855291](https://media.opennet.top/i/2024/01/05/ijkn9o-0.png)

![image-20240105112925083](https://media.opennet.top/i/2024/01/05/ijr1um-0.png)

#### 8.3.3 树形目录

![image-20240105113019205](https://media.opennet.top/i/2024/01/05/ikb97t-0.png)

![image-20240105113120283](https://media.opennet.top/i/2024/01/05/ikwx9k-0.png)

![image-20240105113131712](https://media.opennet.top/i/2024/01/05/il7wli-0.png)

#### 8.3.4 无环图目录

![image-20240105113241660](https://media.opennet.top/i/2024/01/05/ilvl8d-0.png)

![image-20240105113250690](https://media.opennet.top/i/2024/01/05/ilxhlx-0.png)

#### 8.3.5 目录查询

分为线性检索和Hash方法

![image-20240105113513760](https://media.opennet.top/i/2024/01/05/in975q-0.png)

![image-20240105113532717](https://media.opennet.top/i/2024/01/05/inlwg3-0.png)

## 第 9 章 磁盘存储器管理

### 9.1 外存的组织方式

#### 9.1.1 连续分配 ※

![image-20240105101103915](https://media.opennet.top/i/2024/01/05/gldjb2-0.png)

![image-20240105101116235](https://media.opennet.top/i/2024/01/05/glg5yt-0.png)

![image-20240105101124535](https://media.opennet.top/i/2024/01/05/glhyhj-0.png)

#### 9.1.2 链接分配 ※

![image-20240105101304376](https://media.opennet.top/i/2024/01/05/gmkiql-0.png)

![image-20240105101323341](https://media.opennet.top/i/2024/01/05/gmoguj-0.png)

![image-20240105101336271](https://media.opennet.top/i/2024/01/05/gmzyty-0.png)

![image-20240105101526972](https://media.opennet.top/i/2024/01/05/gnwaa9-0.png)

#### 9.2.3 索引分配 ※

将每个文件的块号放在一个物理块中

![image-20240105102004010](https://media.opennet.top/i/2024/01/05/gqqjpy-0.png)

![image-20240105101620826](https://media.opennet.top/i/2024/01/05/gogcut-0.png)

![image-20240105102025066](https://media.opennet.top/i/2024/01/05/gqv2wn-0.png)

![image-20240105102145285](https://media.opennet.top/i/2024/01/05/grtbez-0.png)

![image-20240105102201519](https://media.opennet.top/i/2024/01/05/grx0kx-0.png)

![image-20240105102208948](https://media.opennet.top/i/2024/01/05/gryhkw-0.png)

#### 题目

假定盘块的大小为1KB，硬盘的大小为500MB，采用显示链接分配方式时，其FAT需占用多少存储空间？

答：

FAT 的每个表项对应于磁盘的一个盘块，其中用来存放分配给文件的下一个盘块的块号，故FAT 的表项数目由物理盘块数决定，而表项的长度则由磁盘系统的最大盘块号决定(即它必须能存放最大的盘块号)。

为了地址转换的方便，**FAT表项的长度通常取半个字节的整数倍**，所以必要时还必须由最大盘块号获得的 FAT 表项长度作一些调整。

由题意可知，该硬盘共有 500K 个盘块，故 FAT 中共有 500K 个表项；如果盘块从1开始编号，为了能保存最大的盘块号 500K，**该 FAT 表项最少需要19 位，将它扩展为半个字节的整数倍后，可知每个FAT表项需 20 位**，即 2.5 个字节。

因此，FAT需占用的存储空间的大小为：2.5 * 500K = 1250KB

### 9.2 文件存储空间的管理

#### 9.2.1 空闲区表 空闲链表 ※

![image-20240105094714376](https://media.opennet.top/i/2024/01/05/fjbz7u-0.png)

![image-20240105094723384](https://media.opennet.top/i/2024/01/05/fjdwmu-0.png)

![image-20240105095117614](https://media.opennet.top/i/2024/01/05/flqivk-0.png)

#### 9.2.2 位示图法 ※

![image-20240105095256512](https://media.opennet.top/i/2024/01/05/fmstvp-0.png)

![image-20240105095306287](https://media.opennet.top/i/2024/01/05/fmuw8g-0.png)

#### 9.2.3 成组链接法 ※

![image-20240105095611984](https://media.opennet.top/i/2024/01/05/fooieu-0.png)

#### 题目

有一计算机系统利用图1所示的位示图（行号、列号都从0开始编号）来管理空闲盘块。如果盘块从1开始编号，每个盘块的大小为1KB。

（1）现要为文件分配两个盘块，试说明分配过程。

（2）若要释放磁盘的第300块，应如何处理？

![Screenshot_2024_01_05_09_59_24_37_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/05/fr0ek6-0.jpg)

![Screenshot_2024_01_05_09_59_35_02_8b7aa5be40a89c6a7df806c347da652a](https://media.opennet.top/i/2024/01/05/fr25ch-0.jpg)
