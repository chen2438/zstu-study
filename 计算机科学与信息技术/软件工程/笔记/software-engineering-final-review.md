---
description: 发布于 2024-01-05
categories:
- study
date: 2024-01-05
slug: software-engineering-final-review
title: 软件工程 期末复习
updated: 2024-01-07
tags: 
- study
- software-engineering
copyright: false
---

# 软件工程 期末复习

zstu 浙江理工大学 2023学年第1学期 软件工程

> 带有参考标记 `※` 的章节建议优先阅读
>
> 题目的答案不保证完全正确

```
考前关键词速记

目录：需求获取、需求分析、软件设计、体系结构、人机交互、详细设计、实现、结构化开发、测试、维护、持续集成、度量、管理
生存周期：需求、设计、编码、测试、运行、退役
对应：需求规约、需求模型、体系结构、详细设计、源程序、可执行代码
软件危机：需求获取、需求分析不准确；缺乏项目管理
瀑布：可行性、需求、设计、编码、测试、运行、退役
适合小规模、需求稳定
优点：利于体系结构、利于管理、规范化
缺点：确定需求、时间长、缺陷隐藏
极限编程：完整团队、增量规划、客户参与、简单设计、结对编程、测试驱动、适时重构、持续集成、集体所有
适合小型软件、原型

UML静态：包、类、对象
UML行为：顺序、通信、状态、活动
用例与软件需求的关系：用例是功能性软件需求的主体部分
用例用椭圆、包含用虚线，连接不用箭头
类的组合实心，聚合空心，关联不用箭头
顺序图的对象用矩形

需求分析过程：优先级、用例、模型评审、原型
需求优先级因素：价值、成本、风险
优先级：架构、需求、风险
用例分析过程：精化领域概念模型、设置分析类、构思协作关系、分析类图
分析类：边界、控制、实体
用例：动作序列；交互图：消息；分析类：职责（响应消息）；设计元素：方法
快速原型：探索性、实验性、进化性

设计元素：子系统、构建、类
设计模型：体系结构、用户界面、用例、数据、子系统/构建/类
质量要素：正确、充分、优化、简单

内聚：偶然 逻辑 时间；过程 通信；顺序 功能
耦合：非直接 数据/控制 外部 公共 内容
高内聚低耦合优点：结构简单、可复用、可修改、可维护、并行开发
信息隐藏优点：并行开发、便于测试、便于维护

体系结构：组件、连接件、约束
视图：逻辑、开发、物理、运行、数据
设计模式：以复用为目的，良好定义的设计经验
分层：松耦合、可复用、可替换、标准化。性能损耗大
管道：可升级、更换过滤器构件。只适合批处理
黑板：知识源可升级、更换、复用。性能差，开发测试难

体系结构初创：基于需求、参考已有体系结构、选取体系结构
逻辑体系过程：搜索设计资产、设计技术支撑、确立设计元素、整合设计元素

纵向复用：公共性领域之间进行软部件复用
领域分析：根据领域的特征预测软部件可复用性
领域分析过程：发现可复用实体、抽象化、分类、建立体系结构

界面设计：屏幕内容的表示、屏幕之间跳转关系的表示
界面元素：静态、动态、用户输入、用户命令

数据流图：外部实体矩形，转换圆形，数据流实心箭头，数据源双横线

测试：需求测试、设计测试、代码【单元测试、集成测试】、确认测试、系统测试、回归测试
确认测试：软件是否满足需求说明书
黑盒测试：等价分类、边界值分析、对比测试

非结构化维护：读代码
结构化维护：读文档、读设计、修改设计、修改代码、回归测试
可维护性因素：开发方法：设计、编码、测试；开发环境

持续集成：代码集成、编译、测试、质量分析、发布
持续集成过程：提交代码、触发集成、脚本程序 管道 主工具 从工具、发送通知
持续集成价值：风险、成本、效率、更新、环境、可视化

初始级：没有软件过程管理
可重复级：基本的软件过程管理
已定义级：软件过程的标准化、文档化
已管理级：软件过程的定量管理
优化级：软件过程的维护和更新
```

## 第 1 章 软件与软件工程

### 1.1 软件的概念

#### 1.1.1 软件的组成

![image-20231230190514637](https://media.opennet.top/i/2023/12/30/uqest7-0.png)

#### 1.1.2 软件生存周期

![image-20240107121220364](https://media.opennet.top/i/2024/01/07/jx1gg6-0.png)

### 1.2 软件工程

#### 1.2.1 定义

![image-20231230190748487](https://media.opennet.top/i/2023/12/30/vfuq48-0.png)

#### 1.2.2 发展 ※

**软件危机 ※**

需求获取和需求分析不准确、缺乏项目过程管理

![image-20231230191047347](https://media.opennet.top/i/2023/12/30/vhn189-0.png)

![image-20231230191057270](https://media.opennet.top/i/2023/12/30/vhqzwr-0.png)

#### 1.2.3 目标和原则

![image-20231230192604594](https://media.opennet.top/i/2023/12/30/vqnuu0-0.png)

原则：抽象、信息隐藏、模块化、局部化、一致性、完全性、可验证性

#### 1.2.4 软件开发的方法

结构化方法、面向对象方法、形式化开发方法

### 1.3 过程模型

#### 1.3.1 瀑布 ※

![image-20230912104030427](https://media.opennet.top/i/2023/09/12/h7dm3k-0.png)

![image-20230912104333700](https://media.opennet.top/i/2023/09/12/h96l0c-0.png)

![image-20230912104226942](https://media.opennet.top/i/2023/09/12/h8jift-0.png)

![image-20230912104350695](https://media.opennet.top/i/2023/09/12/h9a4lv-0.png)

![image-20230912104408215](https://media.opennet.top/i/2023/09/12/h9md1h-0.png)

![image-20230912104422990](https://media.opennet.top/i/2023/09/12/h9pmlu-0.png)

![image-20230912104459805](https://media.opennet.top/i/2023/09/12/ha66ug-0.png)

![image-20230912104512884](https://media.opennet.top/i/2023/09/12/ha8yk7-0.png)

![image-20230912104533467](https://media.opennet.top/i/2023/09/12/had90c-0.png)

![image-20230912104652706](https://media.opennet.top/i/2023/09/12/hb2ujc-0.png)

#### 1.3.2 增量

![image-20231230193429664](https://media.opennet.top/i/2023/12/30/vvkuei-0.png)

![image-20231230193438994](https://media.opennet.top/i/2023/12/30/vvmuqo-0.png)

#### 1.3.3 原型建造

![image-20231230193813307](https://media.opennet.top/i/2023/12/30/vxuzjz-0.png)

![image-20231230193825428](https://media.opennet.top/i/2023/12/30/vxxiet-0.png)

![image-20231230193858029](https://media.opennet.top/i/2023/12/30/vyd5bm-0.png)

#### 1.3.4 螺旋

![image-20231230194005659](https://media.opennet.top/i/2023/12/30/vz0e36-0.png)

![image-20231230194013478](https://media.opennet.top/i/2023/12/30/vz247e-0.png)

![image-20231230194808672](https://media.opennet.top/i/2023/12/30/w3sock-0.png)

![image-20231230194817122](https://media.opennet.top/i/2023/12/30/w3ucin-0.png)

#### 1.3.5 基于构建

![image-20231230195013081](https://media.opennet.top/i/2023/12/30/w50a7e-0.png)

![image-20231230195026142](https://media.opennet.top/i/2023/12/30/w536u7-0.png)

#### 题目

![image-20231231170955840](https://media.opennet.top/i/2023/12/31/s5yotz-0.png)

![image-20240101193439187](https://media.opennet.top/i/2024/01/01/vvjfm7-0.png)

### 1.4 敏捷开发 ※

#### 1.4.1 原则

![image-20231230195755187](https://media.opennet.top/i/2023/12/30/w9o3u5-0.png)

#### 1.4.2 极限编程

极限编程是遵循敏捷开发原则的软件过程。

![image-20231230202113452](https://media.opennet.top/i/2023/12/30/xb9xce-0.png)

![image-20231230202132398](https://media.opennet.top/i/2023/12/30/xbe2yf-0.png)

#### 1.4.3 应用

![image-20231230205509532](https://media.opennet.top/i/2023/12/30/xvjfvs-0.png)

#### 题目

![image-20231231214310825](https://media.opennet.top/i/2023/12/31/zbub10-0.png)

## 第 2 章 UML 与 RUP 统一过程

### 2.2 面向对象的软件开发方法

#### 2.2.1 概念 ※

略

#### 题目

![image-20240102130633424](https://media.opennet.top/i/2024/01/02/ktr7dg-0.png)

为了在对象obj1与对象obj2之间消息传递，面向对象的程序设计机制提供如下4种手段：

（1） 引用全局对象。obj1直接引用作为全局对象的obj2。

（2） 通过参数传递。obj2作为obj1的某项操作中的实在参数。

（3） 引用局部对象。在obj1的某项操作的函数体中创建或获取obj2

（4） 通过类的成员变量。obj2作为obj1所属类的属性的取值。

前三种类型的连接具有**暂时性**，obj1与obj2之间的连接仅在obj1的某项操作的执行过程中建立，操作完成后连接即告终结。这种暂时性连接用UML 的依赖关系表示。对**最后一种具有稳定性的连接关系**，需要进一步分析。如果参与连接的两个类在现实世界中存在“皮之不存，毛将焉附”的部分整体关系，则用UML 的构成关系表示。否则，如果它们在现实世界中仍存在“多个整体对象可共享同一部件对象”的部分整体关系，则用UML 的普通聚合关系表示。如果以上两种假设均不成立，则原连接关系精化成UML中普通的关联关系。

![image-20240102130216484](https://media.opennet.top/i/2024/01/02/kr9w7m-0.png)

### 2.3 UML 概述

![image-20231231232504135](https://media.opennet.top/i/2023/12/31/12c695n-0.png)

![image-20231231232514505](https://media.opennet.top/i/2023/12/31/12c7r74-0.png)

### 题目

![image-20231231232634181](https://media.opennet.top/i/2023/12/31/12cxclw-0.png)

![image-20240102115815682](https://media.opennet.top/i/2024/01/02/j1cj51-0.png)

## 第 3 章 需求工程概述

![image-20240101184813093](https://media.opennet.top/i/2024/01/01/ug6ned-0.png)

### 题目

![image-20240105152810609](https://media.opennet.top/i/2024/01/05/p57c73-0.png)

### 3.1 概念

#### 3.1.1 分类

![image-20240101185004139](https://media.opennet.top/i/2024/01/01/uhbnra-0.png)

#### 题目

![image-20240102115248724](https://media.opennet.top/i/2024/01/02/ixz0yu-0.png)



## 第 4 章 需求获取

![image-20231230205848218](https://media.opennet.top/i/2023/12/30/xxrozv-0.png)

### 题目

![image-20240105153251053](https://media.opennet.top/i/2024/01/05/p82cp1-0.png)

![image-20240105153318948](https://media.opennet.top/i/2024/01/05/p88cw9-0.png)

### 4.1 需求表示

#### 4.1.1 用例 ※

重点关注用例与软件需求的关系

![image-20231230210213268](https://media.opennet.top/i/2023/12/30/xzonwg-0.png)

![image-20231230210230066](https://media.opennet.top/i/2023/12/30/xzseud-0.png)

![image-20231230210254848](https://media.opennet.top/i/2023/12/30/y0755m-0.png)

![image-20240102171210303](https://media.opennet.top/i/2024/01/02/s75jmx-0.png)

#### 4.1.2 用例图 ※

![image-20231230210426423](https://media.opennet.top/i/2023/12/30/y0ygis-0.png)

![image-20231230210553532](https://media.opennet.top/i/2023/12/30/y1y622-0.png)

![image-20231230211241964](https://media.opennet.top/i/2023/12/30/ytv8vq-0.png)

![image-20231230212940052](https://media.opennet.top/i/2023/12/30/z3zuho-0.png)

#### 4.1.3 用例的表示 ※

![image-20231230213220512](https://media.opennet.top/i/2023/12/30/z5ej8s-0.png)

![image-20231230213240201](https://media.opennet.top/i/2023/12/30/z5iqlu-0.png)

#### 4.1.4 类图 ※

![image-20231230213419100](https://media.opennet.top/i/2023/12/30/z6liay-0.png)

![image-20231230214744083](https://media.opennet.top/i/2023/12/30/zepun4-0.png)

![image-20231230214832142](https://media.opennet.top/i/2023/12/30/zf0601-0.png)

![image-20231230215915757](https://media.opennet.top/i/2023/12/30/zlg9du-0.png)

![image-20231230215941652](https://media.opennet.top/i/2023/12/30/zlubqt-0.png)

![image-20231230220305879](https://media.opennet.top/i/2023/12/30/znrwjr-0.png)

![image-20231230220314486](https://media.opennet.top/i/2023/12/30/zntmof-0.png)

#### 4.1.5 活动图

![image-20231230221536711](https://media.opennet.top/i/2023/12/30/10ix2nb-0.png)

![image-20231230221556761](https://media.opennet.top/i/2023/12/30/10j9s5t-0.png)

![image-20231230221608361](https://media.opennet.top/i/2023/12/30/10jchbh-0.png)

![image-20231230221619662](https://media.opennet.top/i/2023/12/30/10jf1jj-0.png)

![image-20231230221627495](https://media.opennet.top/i/2023/12/30/10jgfgg-0.png)

#### 题目

![image-20231231212302180](https://media.opennet.top/i/2023/12/31/z00o89-0.png)

![image-20231231231154679](https://media.opennet.top/i/2023/12/31/124d5bs-0.png)

![image-20231231231212305](https://media.opennet.top/i/2023/12/31/124gryj-0.png)

![image-20240101194641571](https://media.opennet.top/i/2024/01/01/w2paot-0.png)

![image-20240102115437115](https://media.opennet.top/i/2024/01/02/iz3dnq-0.png)

注意 14 题不要选择 B

![image-20240102120847569](https://media.opennet.top/i/2024/01/02/jvauo0-0.png)

![image-20240102162431837](https://media.opennet.top/i/2024/01/02/qqw1mu-0.png)

![image-20240102162514379](https://media.opennet.top/i/2024/01/02/qrdvv0-0.png)

![](https://media.opennet.top/i/2024/01/02/rem8rg-0.png)

![](https://media.opennet.top/i/2024/01/02/s4gsll-0.png)

![image-20240105154712156](https://media.opennet.top/i/2024/01/05/pgj9yq-0.png)

![image-20240105154721120](https://media.opennet.top/i/2024/01/05/pgl87d-0.png)

![image-20240105154744033](https://media.opennet.top/i/2024/01/05/pgyinp-0.png)

### 4.5 精化用例

![image-20240102164925530](https://media.opennet.top/i/2024/01/02/r5qjac-0.png)

#### 4.5.1 交互动作序列

![image-20240102165411715](https://media.opennet.top/i/2024/01/02/r8n2cv-0.png)

![image-20240102165438484](https://media.opennet.top/i/2024/01/02/r8sgae-0.png)

![image-20240102165453967](https://media.opennet.top/i/2024/01/02/r8vw6n-0.png)

![image-20240102165503333](https://media.opennet.top/i/2024/01/02/r96g5q-0.png)

![image-20240102165730388](https://media.opennet.top/i/2024/01/02/raj38l-0.png)

#### 4.5.3 构建完整用例

![image-20240102165827957](https://media.opennet.top/i/2024/01/02/rb3xco-0.png)

![image-20240102165840195](https://media.opennet.top/i/2024/01/02/rb6qws-0.png)

#### 4.5.4 精化用例图 ※

![image-20240102170019428](https://media.opennet.top/i/2024/01/02/rc9265-0.png)

#### 题目

![image-20240102170340951](https://media.opennet.top/i/2024/01/02/re5uwp-0.png)

![image-20240102170709537](https://media.opennet.top/i/2024/01/02/s46d0j-0.png)

## 第 5 章 需求分析

![image-20231231224624067](https://media.opennet.top/i/2023/12/31/111b364-0.png)

![image-20231231224705373](https://media.opennet.top/i/2023/12/31/111qatl-0.png)

### 5.1 分析模型的表示

#### 5.1.1 顺序图 ※

![image-20231231225018286](https://media.opennet.top/i/2023/12/31/113ld8b-0.png)

![image-20231231225911369](https://media.opennet.top/i/2023/12/31/118wuiw-0.png)

![image-20231231225919730](https://media.opennet.top/i/2023/12/31/118yewo-0.png)

![image-20231231225932400](https://media.opennet.top/i/2023/12/31/1191cn5-0.png)

![image-20231231225940999](https://media.opennet.top/i/2023/12/31/11939k8-0.png)

![image-20231231225953056](https://media.opennet.top/i/2023/12/31/119eczq-0.png)

![image-20231231230001055](https://media.opennet.top/i/2023/12/31/119ft2d-0.png)

![image-20231231230010743](https://media.opennet.top/i/2023/12/31/119hyrr-0.png)

![image-20231231230019139](https://media.opennet.top/i/2023/12/31/119k0e3-0.png)

![image-20231231230026736](https://media.opennet.top/i/2023/12/31/119leu1-0.png)

#### 题目

![image-20231231230252631](https://media.opennet.top/i/2023/12/31/11b6ek6-0.png)

![](https://media.opennet.top/i/2024/01/02/retgle-0.png)

![](https://media.opennet.top/i/2024/01/02/s4tinb-0.png)

### 5.2 过程模型

![image-20240102124608915](https://media.opennet.top/i/2024/01/02/khped0-0.png)

### 5.3 需求优先级分析

#### 5.3.1 确定优先级 ※

价值、成本、风险

![image-20240102124901473](https://media.opennet.top/i/2024/01/02/kj7prq-0.png)

![image-20240102124914041](https://media.opennet.top/i/2024/01/02/kjivfs-0.png)

![image-20240102124926412](https://media.opennet.top/i/2024/01/02/kjlia0-0.png)

#### 5.3.2 编排优先顺序 ※

架构、需求、风险

![image-20240102125034990](https://media.opennet.top/i/2024/01/02/kk8r66-0.png)

### 5.4 用例分析

![image-20240102153607336](https://media.opennet.top/i/2024/01/02/pacnrt-0.png)

![image-20240102153651981](https://media.opennet.top/i/2024/01/02/pam36v-0.png)

#### 5.4.1 精化领域概念模型

![image-20240102153756892](https://media.opennet.top/i/2024/01/02/pb8tvq-0.png)

![image-20240102153808631](https://media.opennet.top/i/2024/01/02/pbjvc5-0.png)

#### 5.4.2 设置分析类 ※

![image-20240102153951534](https://media.opennet.top/i/2024/01/02/pceea2-0.png)

![image-20240102160411390](https://media.opennet.top/i/2024/01/02/pr1o66-0.png)

![image-20240102160515676](https://media.opennet.top/i/2024/01/02/prnzq9-0.png)

![image-20240102160643343](https://media.opennet.top/i/2024/01/02/psfmsz-0.png)

![image-20240102160927206](https://media.opennet.top/i/2024/01/02/qhxopa-0.png)

![image-20240102160940221](https://media.opennet.top/i/2024/01/02/qi0hrw-0.png)

![image-20240102160948400](https://media.opennet.top/i/2024/01/02/qi2772-0.png)

![image-20240102161101800](https://media.opennet.top/i/2024/01/02/qiqlwo-0.png)

#### 5.4.4 导出分析类图 ※

职责：响应消息

事件->消息->职责->函数方法

![image-20240102161236457](https://media.opennet.top/i/2024/01/02/qjrvmg-0.png)

![image-20240102161252161](https://media.opennet.top/i/2024/01/02/qjvb2p-0.png)

![image-20240102161332628](https://media.opennet.top/i/2024/01/02/qkcpaq-0.png)

#### 题目

![image-20240102161653539](https://media.opennet.top/i/2024/01/02/qm9dei-0.png)

![image-20240102162528247](https://media.opennet.top/i/2024/01/02/qrgmqq-0.png)

![](https://media.opennet.top/i/2024/01/02/rf5u69-0.png)

![](https://media.opennet.top/i/2024/01/02/s4vrd2-0.png)

### 5.5 快速原型 ※

参考 1.3.3。探索性原型不涉及软件的具体实现方法

![image-20231231213916307](https://media.opennet.top/i/2023/12/31/z9hwq1-0.png)

### 题目

![image-20231231213955526](https://media.opennet.top/i/2023/12/31/z9yqjw-0.png)

## 第 6 章 软件设计概论

![image-20231231171416383](https://media.opennet.top/i/2023/12/31/s8h0x8-0.png)

![image-20231231171423967](https://media.opennet.top/i/2023/12/31/s8ijt2-0.png)

### 6.1 概念

#### 6.1.1 软件设计模型 ※

设计元素就是模块

![image-20231231171742361](https://media.opennet.top/i/2023/12/31/saesul-0.png)

![image-20231231171755220](https://media.opennet.top/i/2023/12/31/saq60z-0.png)

#### 6.1.2 质量要素 ※

正确性、充分性、优化性、简单性

### 6.2 软件设计的基本原则

#### 6.2.1 抽象与逐步求精 ※

抽象：自顶向下设计

![image-20231231172109119](https://media.opennet.top/i/2023/12/31/scldsc-0.png)

#### 6.2.2 模块化 ※

![image-20231231172459149](https://media.opennet.top/i/2023/12/31/sewxyh-0.png)

![image-20231231172508639](https://media.opennet.top/i/2023/12/31/sez0re-0.png)

![image-20231231211022016](https://media.opennet.top/i/2023/12/31/ys9igy-0.png)

![image-20231231211036025](https://media.opennet.top/i/2023/12/31/yscrzp-0.png)

优点：简单、可复用、可修改、可维护、并行开发

![image-20231231211149182](https://media.opennet.top/i/2023/12/31/yt9m5e-0.png)

#### 6.2.3 信息隐藏 ※

优点：并行开发、便于测试、便于维护

![image-20231231211607853](https://media.opennet.top/i/2023/12/31/yvspus-0.png)

#### 6.2.4 关注点分离 ※

聚焦某个关注点

![image-20231231212021927](https://media.opennet.top/i/2023/12/31/yy7pso-0.png)

#### 题目

![image-20231231212120655](https://media.opennet.top/i/2023/12/31/yysxxh-0.png)

![image-20231231214107435](https://media.opennet.top/i/2023/12/31/zang38-0.png)

![image-20240102130949175](https://media.opennet.top/i/2024/01/02/ljgdc0-0.png)

![image-20240101002430562](https://media.opennet.top/i/2024/01/01/acweo-0.png)

![image-20240105153447177](https://media.opennet.top/i/2024/01/05/p98o2p-0.png)

![image-20240101194105451](https://media.opennet.top/i/2024/01/01/vzia98-0.png)

![image-20240102115710678](https://media.opennet.top/i/2024/01/02/j0q1v0-0.png)

## 第 7 章 软件体系结构设计

![image-20231231230712026](https://media.opennet.top/i/2023/12/31/121hoiz-0.png)

![image-20231231214533133](https://media.opennet.top/i/2023/12/31/zd6a6k-0.png)

### 题目

![image-20231231214600051](https://media.opennet.top/i/2023/12/31/zdk5qb-0.png)

![image-20231231230730999](https://media.opennet.top/i/2023/12/31/121llfn-0.png)

### 7.1 概念

#### 7.1.1 定义 ※

![image-20240102162823862](https://media.opennet.top/i/2024/01/02/qt80a1-0.png)

#### 7.1.2 体系结构视图 ※

![image-20240102163008276](https://media.opennet.top/i/2024/01/02/qubzpf-0.png)

#### 题目

![image-20231231235213396](https://media.opennet.top/i/2023/12/31/12saht1-0.png)

### 7.2 表示

#### 7.2.1 包图

![image-20240107144943458](https://media.opennet.top/i/2024/01/07/nu9y60-0.png)

#### 7.2.2 构建图

![image-20240107145003512](https://media.opennet.top/i/2024/01/07/nummvw-0.png)

### 7.4 设计模式

#### 7.4.1 定义

设计模式：以设计复用为目的、良好定义的设计经验

![image-20240102174259811](https://media.opennet.top/i/2024/01/02/spb78r-0.png)

#### 7.4.2 通用模式 ※

分层：松耦合、可复用、可替换、标准化。性能损耗大

管道：可升级、更换过滤器构件。只适合批处理

![image-20240102174447479](https://media.opennet.top/i/2024/01/02/sqfhb6-0.png)

![image-20240102174456784](https://media.opennet.top/i/2024/01/02/sqhi6r-0.png)

![image-20240102174540529](https://media.opennet.top/i/2024/01/02/sqzg4y-0.png)

![image-20240102174600698](https://media.opennet.top/i/2024/01/02/sr3ne7-0.png)

![image-20240102174928460](https://media.opennet.top/i/2024/01/02/stalgv-0.png)

![image-20240102175002766](https://media.opennet.top/i/2024/01/02/sthwqx-0.png)

![image-20240102175217259](https://media.opennet.top/i/2024/01/02/sv0ka0-0.png)

![image-20240102175226642](https://media.opennet.top/i/2024/01/02/sv2a3x-0.png)

### 7.5 概念设计

![image-20240102175343027](https://media.opennet.top/i/2024/01/02/svrlk2-0.png)

#### 7.5.2 体系结构初创 ※

![image-20240102175520035](https://media.opennet.top/i/2024/01/02/swtbxx-0.png)

![image-20240102175528083](https://media.opennet.top/i/2024/01/02/swuqm6-0.png)

![image-20240102175537496](https://media.opennet.top/i/2024/01/02/swwlmx-0.png)

### 7.6 体系结构精化

![image-20231231235127872](https://media.opennet.top/i/2023/12/31/12rs0ns-0.png)

#### 7.6.1 逻辑视图体系结构

![image-20240102163334223](https://media.opennet.top/i/2024/01/02/qw9kib-0.png)

#### 7.6.2 开发视图体系结构

![image-20240102163431284](https://media.opennet.top/i/2024/01/02/qwubnv-0.png)

#### 题目

![image-20240102163546570](https://media.opennet.top/i/2024/01/02/qxj18l-0.png)

### 7.7 基于构件的体系结构设计

#### 7.7.1 概述 ※

重点关注纵向复用、领域分析

![image-20240102175945279](https://media.opennet.top/i/2024/01/02/szc1fy-0.png)

![image-20240102180306711](https://media.opennet.top/i/2024/01/02/t1hwn7-0.png)

#### 7.7.2 构建创立 ※

领域分析：发现可复用实体、抽象化、分类、建立体系结构

![image-20240102180339031](https://media.opennet.top/i/2024/01/02/t1os56-0.png)

![image-20240102180718028](https://media.opennet.top/i/2024/01/02/trrnyl-0.png)

#### 7.7.3 构建复用

![image-20240102180929503](https://media.opennet.top/i/2024/01/02/tt0moc-0.png)

## 第 8 章 人机交互设计

### 8.3 用户界面设计模型的表示 ※

屏幕：窗口、对话框、网页

界面设计：屏幕内容的表示、屏幕之间跳转关系的表示

界面元素：静态、动态、用户输入、用户命令

![image-20231231213221297](https://media.opennet.top/i/2023/12/31/z5d59y-0.png)

![](https://media.opennet.top/i/2023/12/31/z5v3a7-0.png)

### 题目

![image-20231231213342028](https://media.opennet.top/i/2023/12/31/z62lkc-0.png)

![image-20231231235300300](https://media.opennet.top/i/2023/12/31/12ssyzo-0.png)

## 第 11 章 结构化软件开发

### 11.1 数据流

#### 11.1.1 数据流图与数据字典 ※

![image-20240102121750526](https://media.opennet.top/i/2024/01/02/k0oop1-0.png)

![image-20240102121757804](https://media.opennet.top/i/2024/01/02/k0q4r7-0.png)

![image-20240102121809639](https://media.opennet.top/i/2024/01/02/k11d1a-0.png)

![image-20240102121930387](https://media.opennet.top/i/2024/01/02/k1r76s-0.png)

![image-20240102121936811](https://media.opennet.top/i/2024/01/02/k1skul-0.png)

#### 11.1.4 基于数据流的分析方法 ※

![image-20240102122154035](https://media.opennet.top/i/2024/01/02/k333t0-0.png)

![image-20240102122205100](https://media.opennet.top/i/2024/01/02/k3e7ih-0.png)

![image-20240102122224343](https://media.opennet.top/i/2024/01/02/k3i8r9-0.png)

#### 题目

![image-20240102124144465](https://media.opennet.top/i/2024/01/02/kextxi-0.png)

![image-20240102170932983](https://media.opennet.top/i/2024/01/02/s5ht4w-0.png)

![image-20240105154856580](https://media.opennet.top/i/2024/01/05/phmlkm-0.png)

### 11.2 面向数据流的设计方法

#### 11.2.1 概念和过程

![image-20240102122700612](https://media.opennet.top/i/2024/01/02/k63qpb-0.png)

![image-20240102122913960](https://media.opennet.top/i/2024/01/02/k7m5tz-0.png)

#### 11.2.2 变换分析 ※

![image-20240102123313020](https://media.opennet.top/i/2024/01/02/k9zsai-0.png)

![image-20240102123356119](https://media.opennet.top/i/2024/01/02/ka8vkb-0.png)

![image-20240102123445373](https://media.opennet.top/i/2024/01/02/karzg0-0.png)

![image-20240102123454967](https://media.opennet.top/i/2024/01/02/kau5hd-0.png)

![image-20240102123147455](https://media.opennet.top/i/2024/01/02/k9034e-0.png)

#### 11.2.3 事务分析 ※

![image-20240102123630100](https://media.opennet.top/i/2024/01/02/kbvp21-0.png)

![image-20240102123640491](https://media.opennet.top/i/2024/01/02/kbxprf-0.png)

![image-20240102123709247](https://media.opennet.top/i/2024/01/02/kccfze-0.png)

![image-20240102123717506](https://media.opennet.top/i/2024/01/02/kce7x7-0.png)

#### 题目

![image-20240102170633104](https://media.opennet.top/i/2024/01/02/rfwnec-0.png)

## 第 12 章 软件测试

### 12.1 概念

![image-20231231215355068](https://media.opennet.top/i/2023/12/31/zialzf-0.png)

#### 12.1.1 任务

![image-20231231215425765](https://media.opennet.top/i/2023/12/31/zihwwm-0.png)

#### 12.1.2 信息流程

![image-20231231220212566](https://media.opennet.top/i/2023/12/31/zn5zt7-0.png)

#### 12.1.3 测试用例设计 ※

![image-20231231220558470](https://media.opennet.top/i/2023/12/31/zpglrr-0.png)

![image-20231231220616190](https://media.opennet.top/i/2023/12/31/zpkirt-0.png)

#### 题目

![image-20240102131034323](https://media.opennet.top/i/2024/01/02/ljynfu-0.png)

![image-20240102115634205](https://media.opennet.top/i/2024/01/02/j09o9g-0.png)

### 12.2 过程模型

![image-20240101184327621](https://media.opennet.top/i/2024/01/01/udaknf-0.png)

![image-20240101184631870](https://media.opennet.top/i/2024/01/01/uf3r9g-0.png)

### 题目

![image-20240101184653390](https://media.opennet.top/i/2024/01/01/uf8brb-0.png)

![image-20240105153629079](https://media.opennet.top/i/2024/01/05/pa2yve-0.png)

![image-20240102163652300](https://media.opennet.top/i/2024/01/02/qy5h0t-0.png)

### 12.3 测试方法

#### 12.3.1 白盒测试

![image-20240101190058055](https://media.opennet.top/i/2024/01/01/unu7ey-0.png)

#### 12.3.2 黑盒测试 ※

等价分类、边界值分析、对比测试

![image-20240101190453036](https://media.opennet.top/i/2024/01/01/upyb7o-0.png)

![image-20240101190429811](https://media.opennet.top/i/2024/01/01/upt1wf-0.png)

#### 题目

![image-20231231220723381](https://media.opennet.top/i/2023/12/31/10e0u4t-0.png)

![image-20240101001759381](https://media.opennet.top/i/2024/01/01/6lkqj-0.png)

第 2 题的最佳答案应当是 B，而不是 A

![image-20240101193942960](https://media.opennet.top/i/2024/01/01/vyjl4a-0.png)

![image-20240102161754828](https://media.opennet.top/i/2024/01/02/qmv0lj-0.png)

![image-20240102170547515](https://media.opennet.top/i/2024/01/02/rfe73v-0.png)

![image-20240102170855515](https://media.opennet.top/i/2024/01/02/s51asc-0.png)

![image-20240105154816885](https://media.opennet.top/i/2024/01/05/ph5qh7-0.png)

![image-20240105154829850](https://media.opennet.top/i/2024/01/05/ph8989-0.png)

### 12.4 测试策略

![image-20231231163526497](https://media.opennet.top/i/2023/12/31/qxhskp-0.png)

#### 12.4.1 单元测试

![image-20231231163614698](https://media.opennet.top/i/2023/12/31/qy0zx8-0.png)

#### 12.4.2 集成测试

![image-20231231163722142](https://media.opennet.top/i/2023/12/31/qynx17-0.png)

![image-20231231163732272](https://media.opennet.top/i/2023/12/31/qypuj9-0.png)

增量式集成分为自顶向下集成和自底向上集成

#### 12.4.3 确认测试

![image-20231231164349558](https://media.opennet.top/i/2023/12/31/r2movx-0.png)

#### 12.4.4 系统测试

![image-20231231164442628](https://media.opennet.top/i/2023/12/31/r2y060-0.png)

![image-20231231164451985](https://media.opennet.top/i/2023/12/31/r38j35-0.png)

#### 题目

![image-20231231164259460](https://media.opennet.top/i/2023/12/31/r23c8e-0.png)

## 第 13 章 软件维护

### 13.1 概念

![image-20240101194325290](https://media.opennet.top/i/2024/01/01/w0tiss-0.png)

![image-20240101194339301](https://media.opennet.top/i/2024/01/01/w0we8c-0.png)

### 题目

![image-20240101194405675](https://media.opennet.top/i/2024/01/01/w1aq9h-0.png)

### 13.2 过程模型

#### 13.2.1 结构化与非结构化的维护 ※

![image-20240102183436418](https://media.opennet.top/i/2024/01/02/u7xzll-0.png)

![image-20240102183445565](https://media.opennet.top/i/2024/01/02/u7zqkc-0.png)

### 13.3 可维护性

![image-20240102183846614](https://media.opennet.top/i/2024/01/02/uadni0-0.png)

![image-20240102183857149](https://media.opennet.top/i/2024/01/02/uafyys-0.png)

![image-20240102183903380](https://media.opennet.top/i/2024/01/02/uahesx-0.png)

## 第 14 章 持续集成

### 14.1 概述

#### 14.1.1 概念 ※

![image-20240101192107119](https://media.opennet.top/i/2024/01/01/vnlvgi-0.png)

![image-20240101192120548](https://media.opennet.top/i/2024/01/01/vnow3t-0.png)

![image-20240101192128061](https://media.opennet.top/i/2024/01/01/vnqokc-0.png)

![image-20240101192136281](https://media.opennet.top/i/2024/01/01/vnsaf7-0.png)

#### 14.1.2 过程和管道 ※

![image-20240101193139645](https://media.opennet.top/i/2024/01/01/vtrsbl-0.png)

![image-20240101193148866](https://media.opennet.top/i/2024/01/01/vtteds-0.png)

#### 14.1.3 价值 ※

风险、成本、效率、更新、环境、可视化

![image-20240101193301183](https://media.opennet.top/i/2024/01/01/vuq2wi-0.png)

#### 题目

![image-20240101193326523](https://media.opennet.top/i/2024/01/01/vuv77i-0.png)

（1）提交代码：一个或多个开发人员将新代码提交至VCS。

（2）触发集成：按照预先配置的“推”或“拉”方式触发管道中首个动作。

（3）执行集成：从工具执行由开发人员根据项目需要开发的**脚本程序**来完成相应的集成动作。在**管道**中每个动作完成后，主工具自动触发下一动作对应的从工具开始执行，直至到达管道的末尾，或者当前动作宣告失败。

（4）发送通知：可以对主、从工具进行配置以支持向代码提交者（或项目其他成员）发送集成过程中的进展及错误概述信息。

## 第 15 章 软件度量与估算

### 15.2 软件规模度量

![image-20240102162014707](https://media.opennet.top/i/2024/01/02/qoedkf-0.png)

### 题目

![image-20240102162034543](https://media.opennet.top/i/2024/01/02/qoivup-0.png)

### 15.4 软件质量度量

#### 15.4.1 软件质量的概念

![image-20240101191044056](https://media.opennet.top/i/2024/01/01/vha629-0.png)

![image-20240101191317202](https://media.opennet.top/i/2024/01/01/viwif3-0.png)

![image-20240101191325032](https://media.opennet.top/i/2024/01/01/viy90w-0.png)

#### 题目

![image-20240101191502867](https://media.opennet.top/i/2024/01/01/vk06fw-0.png)

(1)正确性：软件满足需求规约及完成用户目标的程度。

(2)可用性。学习和使用软件的难易程度，

(3)可靠性。软件完成预期功能，成功运行的概率。软件可靠性反映了软件无故障工作的状况。

(4)有效性。软件系统利用计算机的时间资源和空间资源完成系统功能的能力。

(5)可维护性。软件制品交付用户使用后，能够对它进行修改，以便改正潜伏的缺陷、改进性能和其他属性，使软件制品适应环境的变化等等。

(6)可复用性。软构件可以在多种场合应用的程度称为构件的可复用性。

## 第 16 章 软件项目管理与过程改进

### 16.7 软件配置管理

![image-20231231162449759](https://media.opennet.top/i/2023/12/31/qrblbf-0.png)

#### 16.7.1 概念

基线可以理解为一个配置文件 `conf.ini`

![image-20231231162636779](https://media.opennet.top/i/2023/12/31/qs76cy-0.png)

#### 16.7.2 任务

![image-20231231163022740](https://media.opennet.top/i/2023/12/31/quhr51-0.png)

#### 题目

![image-20231231162557724](https://media.opennet.top/i/2023/12/31/qryojc-0.png)

![image-20231231162657911](https://media.opennet.top/i/2023/12/31/qsk8kc-0.png)

### 16.8 软件过程改进

#### 16.8.1 概念

![image-20231231165804449](https://media.opennet.top/i/2023/12/31/rb250n-0.png)

![image-20231231165815323](https://media.opennet.top/i/2023/12/31/rb4bac-0.png)

#### 16.8.2 能力成熟度模型 CMM ※

初始级：没有软件过程管理

可重复级：基本的软件过程管理

已定义级：软件过程的标准化、文档化

已管理级：软件过程的定量管理

优化级：软件过程的维护和更新

![image-20231231165258815](https://media.opennet.top/i/2023/12/31/r81ixv-0.png)

![image-20231231170557367](https://media.opennet.top/i/2023/12/31/rfs3rx-0.png)

![image-20231231170614415](https://media.opennet.top/i/2023/12/31/rfvmbb-0.png)

![image-20231231170653674](https://media.opennet.top/i/2023/12/31/s465ua-0.png)

![image-20231231170723835](https://media.opennet.top/i/2023/12/31/s4cjwo-0.png)

![image-20231231170751812](https://media.opennet.top/i/2023/12/31/s4qxhz-0.png)

#### 题目

![image-20231231170835610](https://media.opennet.top/i/2023/12/31/s50bh0-0.png)