---
description: 发布于 2023-06-15
categories:
- study
date: 2023-06-15
slug: computer-composition-principles-final-review
title: 计算机组成原理 期末复习
updated: 
tags: 
- study
- computer-composition-principles
copyright: false
---

# 计算机组成原理 期末复习

## 第 1 章 计算机系统概论

### 1.1 计算机的诞生和发展

#### 冯诺依曼体系

![image-20230607165641366](https://media.opennet.top/i/2023/06/10/64840208c56cd.png)

### 1.2 计算机的硬件

#### 指令

![image-20230607165824790](https://media.opennet.top/i/2023/06/10/6484020ea6ceb.png)

#### 硬件组成

组成计算机的基本部件有中央处理器（CPU，运算器和控制器）、存储器和输入输出设备。

![image-20230607170750475](https://media.opennet.top/i/2023/06/10/64840217c4f92.png)

![image-20230607170810009](https://media.opennet.top/i/2023/06/10/6484021d8f079.png)

![image-20230607170822369](https://media.opennet.top/i/2023/06/10/64840224717c8.png)

![image-20230607170837148](https://media.opennet.top/i/2023/06/10/6484023b9bb74.png)

#### 计算机系统分类

![image-20230607171049560](https://media.opennet.top/i/2023/06/10/6484023eaf783.png)

### 1.2 计算机的软件

#### 机器语言 汇编语言 高级语言

![image-20230607171347026](https://media.opennet.top/i/2023/06/10/6484023e596cf.png)

![image-20230607171401487](https://media.opennet.top/i/2023/06/10/6484023ec8fab.png)

![image-20230607171449256](https://media.opennet.top/i/2023/06/10/6484023f30a0b.png)

#### 操作系统

![image-20230607171507702](https://media.opennet.top/i/2023/06/10/6484023f3ca83.png)

## 第 2 章 计算机的逻辑部件

### 2.1 组合逻辑电路

#### 三态电路

![image-20230607172819879](https://media.opennet.top/i/2023/06/10/6484023f62111.png)

![image-20230607172904608](https://media.opennet.top/i/2023/06/10/648402401e48c.png)

![image-20230607172919296](https://media.opennet.top/i/2023/06/10/6484024089645.png)

![image-20230607172947303](https://media.opennet.top/i/2023/06/10/64840241b87fc.png)

#### 异或门的应用

（1）原码/反码输出电路

（2）半加器

（3）数码比较器

（4）奇偶检测电路

![image-20230607182047074](https://media.opennet.top/i/2023/06/10/648402424c1e2.png)

![image-20230607182058683](https://media.opennet.top/i/2023/06/10/648402428313b.png)

#### 加法器

![image-20230607185134310](https://media.opennet.top/i/2023/06/10/648402433c733.png)

![image-20230607185153106](https://media.opennet.top/i/2023/06/10/6484024696594.png)

![image-20230607185428777](https://media.opennet.top/i/2023/06/10/6484024770802.png)

![image-20230607185456195](https://media.opennet.top/i/2023/06/10/6484024801618.png)

![image-20230607185507418](https://media.opennet.top/i/2023/06/10/648402490cbeb.png)

#### 题：加法器

![image-20230615185945201](https://media.opennet.top/i/2023/06/15/648aef221fc45.png)

#### 译码器

![image-20230607190036229](https://media.opennet.top/i/2023/06/10/6484024945f67.png)

![image-20230607190105952](https://media.opennet.top/i/2023/06/10/6484024a1eba3.png)

#### 数据选择器

![image-20230607190212807](https://media.opennet.top/i/2023/06/10/6484024a1ded0.png)

![image-20230607190230662](https://media.opennet.top/i/2023/06/10/6484024a652c9.png)

### 2.2 时序逻辑电路

#### 触发器

电位触发器 锁存器 可以组成暂存器

边沿触发器 D触发器 可以组成寄存器、计数器、移位寄存器

主从触发器 JK触发器 可以组成计数器

#### 寄存器 移位寄存器

![image-20230607193107306](https://media.opennet.top/i/2023/06/10/6484024ad8e7e.png)

#### 计数器

![image-20230607193217615](https://media.opennet.top/i/2023/06/10/6484024aef4f0.png)

### 2.3 阵列逻辑电路

#### 只读存储器 ROM

用于存储固定信息，如监控程序、函数和常数

由地址译码器（与阵列）和存储单元（或阵列）构成

![image-20230607193836138](https://media.opennet.top/i/2023/06/10/6484024c261b8.png)

![image-20230607193846862](https://media.opennet.top/i/2023/06/10/6484024ca1bd7.png)

#### 可编程序逻辑阵列 PLA

由与阵列、或阵列组成，都可编程

采用熔丝工艺

#### 可编程序阵列逻辑 PAL

与阵列可编程，或阵列不可编程

采用熔丝工艺

#### 通用阵列逻辑 GAL

![image-20230607194312234](https://media.opennet.top/i/2023/06/10/6484024d9fcff.png)

#### 门阵列 GA 宏单元阵列 MCA

![image-20230607194540894](https://media.opennet.top/i/2023/06/10/6484024e35f59.png)

#### 现场可编程门阵列 FPGA

![image-20230607194611856](https://media.opennet.top/i/2023/06/10/6484024e79ae7.png)

## 第 3 章 运算方法和运算部件

### 3.1 数据的表示方法和转换

#### 进制转换

N转十：位值原理

十转N：整数部分，短除法（除N取余）；小数部分，乘N取整

十进制可以精确表示二进制，二进制不能精确表示十进制

#### 题：进制转换

![image-20230614200124751](https://media.opennet.top/i/2023/06/14/6489ac1414061.png)

#### 编码

![image-20230614192824150](https://media.opennet.top/i/2023/06/14/6489a457e3cb2.png)

![image-20230614193152080](https://media.opennet.top/i/2023/06/14/6489a527c0f2e.png)

### 3.2 数据表示和加减法

#### 数据表示

![image-20230614193418186](https://media.opennet.top/i/2023/06/14/6489a5b95eb01.png)

![image-20230614193439326](https://media.opennet.top/i/2023/06/14/6489a5cecc31d.png)

![image-20230614193556387](https://media.opennet.top/i/2023/06/14/6489a61bb66e2.png)

![image-20230614193854463](https://media.opennet.top/i/2023/06/14/6489a6cdd64a7.png)

#### 题：数据表示

![image-20230614201324241](https://media.opennet.top/i/2023/06/14/6489aee3d6306.png)

![image-20230614201535324](https://media.opennet.top/i/2023/06/14/6489af66da0c7.png)

补码右移时要计入符号位，即移动符号位的值，但是符号位本身保持不变。左移时，如果符号位改变，则发生溢出。

#### 溢出检查

![image-20230614194148161](https://media.opennet.top/i/2023/06/14/6489a77b7481c.png)

![image-20230614194157792](https://media.opennet.top/i/2023/06/14/6489a78505d3e.png)

#### 浮点数

规格化就是尾数除了符号位之外的最高位一定为1

![image-20230614195227441](https://media.opennet.top/i/2023/06/14/6489a9fb02ca3.png)

![image-20230614195255931](https://media.opennet.top/i/2023/06/14/6489aa1780ea0.png)

### 3.3 二进制乘法

#### 原码一位乘

![image-20230615141050992](https://media.opennet.top/i/2023/06/15/648aab6d1b657.png)

![image-20230615141517570](https://media.opennet.top/i/2023/06/15/648aac7a000fe.png)

#### 补码一位乘

补码的X符号位加入运算

若Y<0，最后加[-X]补

![image-20230615142011463](https://media.opennet.top/i/2023/06/15/648aad9cca9c2.png)

![image-20230615142028835](https://media.opennet.top/i/2023/06/15/648aadae1f92a.png)

![image-20230615142041707](https://media.opennet.top/i/2023/06/15/648aadbb7cdb2.png)

![image-20230615142057634](https://media.opennet.top/i/2023/06/15/648aadcba9337.png)

#### 补码一位乘：布斯公式

布斯法，Y的符号位也参加运算，单符号位，Y最后补0（Y左右两边都要补数字）

部分积 + [(Y_(i+1)-Y_i*X]补

注意，不需要全部右移完毕，在下题中右移4次就结束。

![image-20230615142905797](https://media.opennet.top/i/2023/06/15/648aafb448e40.png)

### 3.4 二进制除法

#### 原码一位除：加减交替法

商带符号位，多一位

![image-20230615143349242](https://media.opennet.top/i/2023/06/15/648ab0cf92cb7.png)

![image-20230615143410945](https://media.opennet.top/i/2023/06/15/648ab0e3c4333.png)

![image-20230615143426774](https://media.opennet.top/i/2023/06/15/648ab0f40f0a7.png)

![image-20230615143530244](https://media.opennet.top/i/2023/06/15/648ab135333f3.png)

### 3.5 浮点数运算

#### 浮点数加减法

![image-20230615143739104](https://media.opennet.top/i/2023/06/15/648ab1b4cdc1e.png)

#### 浮点数乘除法

![image-20230615144029337](https://media.opennet.top/i/2023/06/15/648ab25ea1cad.png)

![image-20230615144119113](https://media.opennet.top/i/2023/06/15/648ab29094bec.png)

![image-20230615144150752](https://media.opennet.top/i/2023/06/15/648ab2b041dbf.png)

### 3.7 数据校验码

#### 奇偶校验码

![image-20230612173337972](https://media.opennet.top/i/2023/06/12/6486e67392074.png)

#### 海明码

![image-20230612173538127](https://media.opennet.top/i/2023/06/12/6486e6eb3b697.png)

![image-20230612173721814](https://media.opennet.top/i/2023/06/12/6486e7530a3ae.png)

![image-20230612173841843](https://media.opennet.top/i/2023/06/12/6486e7a2bfffb.png)

![image-20230612174530119](https://media.opennet.top/i/2023/06/12/6486e93b6bea9.png)

#### 题：海明码

![image-20230612174701997](https://media.opennet.top/i/2023/06/12/6486e996bfc4c.png)

![image-20230612174715992](https://media.opennet.top/i/2023/06/12/6486e9a4d82b4.png)

![image-20230612174736386](https://media.opennet.top/i/2023/06/12/6486e9b992635.png)

![image-20230612174746610](https://media.opennet.top/i/2023/06/12/6486e9c356d36.png)

## 第 4 章 主存储器

### 4.1 主存储器分类、技术指标和基本操作

#### 存储器的分类

![image-20230612180111080](https://media.opennet.top/i/2023/06/12/6486ece84b4eb.png)

#### 主存储器的技术指标

![image-20230612180458207](https://media.opennet.top/i/2023/06/12/6486edcb1e586.png)

### 4.2 读/写存储器

都是易失性存储器，断电丢数据

SRAM 速度快，体积大，功率大

DRAM 便宜，容量大

![image-20230612183303359](https://media.opennet.top/i/2023/06/12/6486f46084365.png)

#### 静态随机存储器 SRAM

双稳态触发器

![image-20230612181013337](https://media.opennet.top/i/2023/06/12/6486ef061a19c.png)

#### 动态随机存储器 DRAM

![image-20230612181628763](https://media.opennet.top/i/2023/06/12/6486f07d5e228.png)

![image-20230612183409542](https://media.opennet.top/i/2023/06/12/6486f4a1edec8.png)

![image-20230612183423013](https://media.opennet.top/i/2023/06/12/6486f4b014191.png)

![image-20230612181611037](https://media.opennet.top/i/2023/06/12/6486f06be3f37.png)

### 4.3 非易失性半导体存储器

#### 只读存储器 ROM

#### 可编程 只读存储器 PROM

熔丝，一次性编程

#### 可擦可编程 只读存储器 EPROM

编程次数不受限制，电写，紫外线擦除

#### 可电擦可编程序 只读存储器 E^2PROM

电擦，电写，次数10万次

#### 快擦除读写存储器 Flash Memory

即闪存

### 4.4 容量扩展

#### 位扩展

![image-20230612231350059](https://media.opennet.top/i/2023/06/12/6487362eedf99.png)

#### 字扩展

![image-20230612231427930](https://media.opennet.top/i/2023/06/12/648736548d4c3.png)

![image-20230612231449966](https://media.opennet.top/i/2023/06/12/6487366a53973.png)

#### 字位同时扩展

![image-20230612183633855](https://media.opennet.top/i/2023/06/12/6486f532a2b28.png)

![image-20230612183643755](https://media.opennet.top/i/2023/06/12/6486f53c967ac.png)

## 第 5 章 指令系统

### 5.2.2 指令操作码的扩展技术

![image-20230612232646566](https://media.opennet.top/i/2023/06/12/64873937810fa.png)

![image-20230612232832094](https://media.opennet.top/i/2023/06/12/648739a09466c.png)

## 第 6 章 中央处理器

### 6.1 控制器

#### 控制器的组成

![image-20230613191339675](https://media.opennet.top/i/2023/06/13/64884f671923c.png)

![image-20230613191352928](https://media.opennet.top/i/2023/06/13/64884f73d5cef.png)

![image-20230613191449545](https://media.opennet.top/i/2023/06/13/64884faca566c.png)

![image-20230613191605568](https://media.opennet.top/i/2023/06/13/64884ff8b00d5.png)

#### 数据通路

![image-20230613194520458](https://media.opennet.top/i/2023/06/13/648856d376677.png)

![image-20230613194551391](https://media.opennet.top/i/2023/06/13/648856f260002.png)

![image-20230613194626374](https://media.opennet.top/i/2023/06/13/64885715b0668.png)

![image-20230613194640518](https://media.opennet.top/i/2023/06/13/64885723a718e.png)

#### 题：数据通路

![image-20230613193600723](https://media.opennet.top/i/2023/06/13/648854a412066.png)

![image-20230613193617016](https://media.opennet.top/i/2023/06/13/648854b55ed72.png)

### 6.2 微程序

控存，控制存储器，ROM

![image-20230613202529411](https://media.opennet.top/i/2023/06/13/6488603d0146d.png)

![image-20230613202919075](https://media.opennet.top/i/2023/06/13/6488612251712.png)

### 6.3 微程序设计

#### 微程序控制字段的编译法

![image-20230613203100993](https://media.opennet.top/i/2023/06/13/648861883b8ef.png)

![image-20230613203235258](https://media.opennet.top/i/2023/06/13/648861e6130ec.png)

#### 题：微指令控制字段格式设计

![image-20230613210528548](https://media.opennet.top/i/2023/06/13/6488699b6aeaa.png)

![image-20230613210553584](https://media.opennet.top/i/2023/06/13/648869b47f3b0.png)

![IMG_1061](https://media.opennet.top/i/2023/06/13/6488695f2b8ca.png)

#### 微指令格式

![image-20230613203641650](https://media.opennet.top/i/2023/06/13/648862dcc71b4.png)

![image-20230613203700945](https://media.opennet.top/i/2023/06/13/648862f04b75d.png)

### 6.5 流水线

#### CPU 性能公式

![扫描件_时间=执行程序所需的时钟周期数时钟周期时_1](https://media.opennet.top/i/2023/06/13/64886e3ae4c7b.jpg)

#### 题：CPU 性能

![image-20230613212638076](https://media.opennet.top/i/2023/06/13/64886e90f10b4.png)

#### 流水线阻塞

流水线阻塞是指在流水线处理器中，由于某些原因导致流水线暂停或减速，从而影响处理器性能。流水线阻塞的主要原因有**数据相关、程序转移和中断请求**。下面分别解释这三种情况及其解决方法：

1. **数据相关**（Data Dependency）：
数据相关是指一个指令需要等待前一个或多个指令完成数据操作才能执行。这种情况下，流水线需要暂停，等待所需数据准备好。数据相关主要包括RAW（Read After Write，先写后读）、WAR（Write After Read，先读后写）和WAW（Write After Write，先写后写）。

解决方法：
- 指令调度：对指令进行重新排序，使得数据相关的指令之间有足够的间隔，以便在等待数据时处理其他指令。
- 数据前推（Data Forwarding）：将上一级流水线段的计算结果直接传递给下一级流水线段，而不是等待寄存器更新。
- 寄存器重命名：通过使用更多的寄存器来消除WAW和WAR相关。

2. **程序转移**（Control Dependency）：
程序转移是指流水线处理器遇到分支指令（如条件跳转、循环等）时，需要等待分支指令执行完毕才能确定下一条指令的地址。这会导致流水线暂停，等待新指令地址。

解决方法：
- 预测分支（Branch Prediction）：通过硬件或软件预测分支的结果，提前获取下一条指令的地址，以减少等待时间。
- 延迟分支（Delayed Branching）：将分支指令后面的无关指令（与分支无关）提前执行，以减少流水线暂停时间。
- 分支目标缓冲（Branch Target Buffer，BTB）：缓存分支指令的目标地址，以加速分支指令的执行。

3. **中断请求**（Interrupt Request）：
中断请求是指处理器在执行指令过程中收到外部或内部的中断信号，需要暂停当前任务，切换到中断服务程序。这会导致流水线暂停，等待中断处理完成。

解决方法：
- 中断屏蔽：在处理关键任务时，暂时屏蔽低优先级的中断请求，以减少流水线阻塞。
- 优先级设置：为不同类型的中断设置优先级，确保高优先级中断能够及时处理，降低流水线阻塞的影响。
- 硬件支持：使用硬件支持的中断处理机制，如嵌套中断向量表（Nested Interrupt Vector Table），加速中断处理过程，减少流水线阻塞时间。

## 第 7 章 存储系统

### 7.1 存储系统的层次结构

![image-20230612180804234](https://media.opennet.top/i/2023/06/12/6486ee8520e6e.png)

![image-20230612180813773](https://media.opennet.top/i/2023/06/12/6486ee8e51c85.png)

### 7.2 高速缓冲存储器 cache

#### cache 工作原理

![image-20230613230625432](https://media.opennet.top/i/2023/06/13/648885f469c68.png)

![image-20230613230645489](https://media.opennet.top/i/2023/06/13/648886094373a.png)

![image-20230613230655991](https://media.opennet.top/i/2023/06/13/64888612d25c6.png)

![image-20230613230706849](https://media.opennet.top/i/2023/06/13/6488861d830b3.png)

#### 题：cache 命中率

![image-20230614104637854](https://media.opennet.top/i/2023/06/14/64892a0e4c20a.png)

![IMG_1062](https://media.opennet.top/i/2023/06/14/64892a6889f3c.png)

![image-20230615190103726](https://media.opennet.top/i/2023/06/15/648aef7065ca6.png)

#### cache 地址映像

![image-20230613231159775](https://media.opennet.top/i/2023/06/13/64888742388ec.png)

![image-20230613231232404](https://media.opennet.top/i/2023/06/13/648887632a313.png)

![image-20230613231327068](https://media.opennet.top/i/2023/06/13/64888799b34a8.png)

![image-20230613231404841](https://media.opennet.top/i/2023/06/13/648887bf81e18.png)

![image-20230613231415190](https://media.opennet.top/i/2023/06/13/648887c9d2d26.png)

![image-20230613231426275](https://media.opennet.top/i/2023/06/13/648887d4dc642.png)

![image-20230613231438350](https://media.opennet.top/i/2023/06/13/648887e0dd62f.png)

![image-20230613231450563](https://media.opennet.top/i/2023/06/13/648887ed7be3b.png)

#### 题：地址映像

注：存储块数 != 块数

区号：RAM地址位数 - cache地址位数

组号：cache总存储块数 / 块数

（块数：几路组相联就是几块数，一般为4；cache总存储块数 = cache总容量 / 一存储块的容量）

块号：log(块数)，一般为2

块内地址：log(块的字数)

![image-20230615191331643](https://media.opennet.top/i/2023/06/15/648af25cacdad.png)

#### cache 替换算法

![image-20230614115044965](https://media.opennet.top/i/2023/06/14/648939154f05f.png)

#### 题：替换算法

m表示未命中，h表示命中

请求的页面从下往上顶掉最上方的页面，当请求的页面原本就在缓存中时视为命中。

~~LRU：命中时仍然执行不命中时的操作（请求的页面从下往上顶掉最上方的页面）~~

LRU：命中时把命中的块放到最下方，其他块顺次上移

FIFO：命中时不执行操作

![image-20230614115248697](https://media.opennet.top/i/2023/06/14/64893991195ac.png)

![image-20230614115259962](https://media.opennet.top/i/2023/06/14/6489399c422d7.png)
