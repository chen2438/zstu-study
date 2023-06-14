---
description: 发布于 2023-06-14
categories:
- study
date: 2023-06-14
slug: compilation-principle-final-review
title: 编译原理（双语） 期末复习
updated: 
tags: 
- study
- compilation-principle
copyright: false 
---

# 编译原理（双语） 期末复习

## 概论

![概论_page-0001](https://media.opennet.top/i/2023/06/11/6485e65a80573.jpg)

## 词法分析

`lexical analysis` 又称为 `scanning`

### 正则表达式

`regular expressions`

#### 概念

![image-20230611170324153](https://media.opennet.top/i/2023/06/11/64858ddfb8b47.png)

![image-20230611170355605](https://media.opennet.top/i/2023/06/11/64858dfd4f0d1.png)

#### 题：解释正则式

![IMG_1043](https://media.opennet.top/i/2023/06/11/64858eddc7cc5.png)

#### 题：检查匹配

![IMG_1044](https://media.opennet.top/i/2023/06/11/64858f4d6d99e.png)

### 有限自动机

`finite automata`

#### DFA

![image-20230611171229082](https://media.opennet.top/i/2023/06/11/64858ffe599a9.png)

#### NFA

![image-20230611171250140](https://media.opennet.top/i/2023/06/11/64859013b55bf.png)

#### 正则表达式到NFA

![image-20230611171520002](https://media.opennet.top/i/2023/06/11/648590a9cde02.png)

#### NFA到DFA

![image-20230611171715281](https://media.opennet.top/i/2023/06/11/6485911cb21a2.png)

#### 最小化DFA

![image-20230611171756983](https://media.opennet.top/i/2023/06/11/6485914777baa.png)

#### 题：正则->NFA->DFA

![IMG_1045](https://media.opennet.top/i/2023/06/11/6485c9ec63915.png)

![image-20230611212740620](https://media.opennet.top/i/2023/06/11/6485cbcd32c1d.png)

![image-20230611212802157](https://media.opennet.top/i/2023/06/11/6485cbe298362.png)

#### 题：最小化DFA

![image-20230611212910712](https://media.opennet.top/i/2023/06/11/6485cc2829a8e.png)

![image-20230611212944045](https://media.opennet.top/i/2023/06/11/6485cc48a833f.png)

## 语法分析

### 上下文无关文法

#### 概念

![image-20230611213529270](https://media.opennet.top/i/2023/06/11/6485cda1f09e3.png)

#### 最左推导 最右推导

![image-20230611213722860](https://media.opennet.top/i/2023/06/11/6485ce13b63ec.png)

#### 分析树

![image-20230611213828786](https://media.opennet.top/i/2023/06/11/6485ce559465e.png)

#### 题：列出文法信息

![IMG_1046](https://media.opennet.top/i/2023/06/11/6485cf22022c0.png)

#### 题：最左推导、最右推导

![IMG_1047](https://media.opennet.top/i/2023/06/11/6485cfebb79ca.png)

#### 题：分析树、抽象语法树

![image-20230611214657297](https://media.opennet.top/i/2023/06/11/6485d051bbb38.png)

![image-20230611214712986](https://media.opennet.top/i/2023/06/11/6485d06164a75.png)

## 自底向下分析

### LL(1)文法

#### First集

First集是指对于给定的文法符号，它可能推导出的第一个终结符的集合。

- 对于一个非终结符A，First(A)表示A能够推导出的所有可能的第一个终结符的集合。

- 对于一个产生式，First集也可以用于表示该产生式右侧推导出的所有可能的第一个终结符的集合。

First(E) 找E变成的产生式的第一个非终结符的集合

![image-20230611215315240](https://media.opennet.top/i/2023/06/11/6485d1cc43267.png)

#### Follow集

Follow集是指对于给定的非终结符，它在句子中可能紧跟在其后的终结符的集合。对于一个非终结符A，Follow(A)表示在任何一个句子中，A后面可能出现的终结符的集合。

Follow(E) 找E后面可能跟哪些非终结符，如果E在产生式的最后，那么找这个式子的左部后面可能跟哪些非终结符。Follow集里不可能有ε。注意$符号（或#号）

![image-20230611145800173](https://media.opennet.top/i/2023/06/11/64857079b9633.png)

![image-20230611215409138](https://media.opennet.top/i/2023/06/11/6485d2022d17a.png)

#### Select集

Select集是用于确定某个产生式是否应该被应用的条件。对于一个产生式P，Select(P)表示当满足某些条件时，产生式P应该被应用。Select集可以通过First集和Follow集计算得出。Select集合里不可能有ε。

对于一个产生式 E -> α，Select(E -> α) = First(α) = First(产生式右部)

如果α可以为ε，Select(E -> α) = First(α) - ε + Follow(E) = First(产生式右部) - ε + Follow(产生式左部)

![IMG_1037](https://media.opennet.top/i/2023/06/11/648574bdd1659.png)

#### 判定定理

![IMG_1048](https://media.opennet.top/i/2023/06/11/6485d50e77dec.png)

#### 消除左递归

![image-20230611143701096](https://media.opennet.top/i/2023/06/11/64856b8fb9409.png)

![image-20230611143751418](https://media.opennet.top/i/2023/06/11/64856bc170971.png)

#### 提取左公因子

![image-20230611221037238](https://media.opennet.top/i/2023/06/11/6485d5dda51ae.png)

#### 二义性

![image-20230611221524169](https://media.opennet.top/i/2023/06/11/6485d6fd17945.png)

文法的二义性是指一个句子在该文法下有两个或多个不同的推导树。消除文法的二义性对于语法分析过程非常重要，因为它可以确保句子具有唯一的语法结构，从而避免歧义。以下是一些常用的方法来消除文法的二义性：

1. 重新定义文法规则：
    尝试通过重新定义文法规则来消除二义性。这可以包括合并某些规则、拆分规则、重新排列规则等。目标是确保每个句子在新文法下只有一个唯一的推导树。
2. 引入优先级和结合性：
    为文法中的运算符定义优先级和结合性规则。优先级规则确定了哪些运算符应该优先计算，而结合性规则确定了具有相同优先级的运算符的计算顺序。通过为文法中的运算符分配优先级和结合性，可以消除由于运算符顺序不明确导致的二义性。
3. 采用左递归或右递归：
    根据需要，可以将文法规则改写为左递归或右递归的形式。左递归适用于左结合的运算符，而右递归适用于右结合的运算符。通过将文法规则改写为适当的递归形式，可以消除由于运算符结合性不明确导致的二义性。

#### 分析表

可以在Select集合的基础上构建，也可以直接构建

![image-20230611215649470](https://media.opennet.top/i/2023/06/11/6485d2a3030fe.png)

#### 分析过程

注意，替换时要反着压入parsing stack

反着压才可以利用select集的定义，让新串与input匹配

![image-20230611215848652](https://media.opennet.top/i/2023/06/11/6485d31a37dd8.png)

#### 题：LL(1)分析表

![IMG_1042](https://media.opennet.top/i/2023/06/11/64857e169742a.png)

#### 题：LL(1)分析过程

![IMG_1040](https://media.opennet.top/i/2023/06/11/64857dab10195.png)

## 自底向上分析

### LR(0)文法

#### 构造分析表

![IMG_1051](https://media.opennet.top/i/2023/06/11/6485d96f2415e.jpg)

![IMG_1052](https://media.opennet.top/i/2023/06/11/6485d984339df.jpg)

### SLR(1)文法

#### 构造分析表

![IMG_1053](https://media.opennet.top/i/2023/06/11/6485db3789a92.jpg)

![IMG_1054](https://media.opennet.top/i/2023/06/11/6485db41cb9e8.jpg)

#### 题：SRL(1)文法综合

![image-20230611223622633](https://media.opennet.top/i/2023/06/11/6485dbe708722.png)

![image-20230611223639043](https://media.opennet.top/i/2023/06/11/6485dbf763466.png)

![image-20230611223707153](https://media.opennet.top/i/2023/06/11/6485dc1357f39.png)

![image-20230611223732250](https://media.opennet.top/i/2023/06/11/6485dc2c9fe5c.png)

![image-20230611223757990](https://media.opennet.top/i/2023/06/11/6485dc45eda6c.png)

![image-20230611223810441](https://media.opennet.top/i/2023/06/11/6485dc52abd1f.png)

### LR(1)文法

#### 构造分析表

![IMG_1055](https://media.opennet.top/i/2023/06/11/6485e088eeb41.jpg)

![IMG_1056](https://media.opennet.top/i/2023/06/11/6485e09dd3726.jpg)

### LALR(1)文法

#### 构造分析表

![IMG_1057](https://media.opennet.top/i/2023/06/11/6485e0f2a54c2.jpg)

#### 题：LALR(1)文法综合

注：a, b小题是LR(1), c, d小题是LALR(1)

![image-20230611230127314](https://media.opennet.top/i/2023/06/11/6485e1c7835a1.png)

![image-20230611230224328](https://media.opennet.top/i/2023/06/11/6485e20062e38.png)

![image-20230611230239749](https://media.opennet.top/i/2023/06/11/6485e2103fc36.png)

![image-20230611230321045](https://media.opennet.top/i/2023/06/11/6485e2393ff67.png)

![image-20230611230359060](https://media.opennet.top/i/2023/06/11/6485e25f48f1d.png)

![image-20230611230419537](https://media.opennet.top/i/2023/06/11/6485e273ad1a6.png)

![image-20230611230439670](https://media.opennet.top/i/2023/06/11/6485e287b8a5b.png)

e. 使用 LALR(1) 解析而不是一般的 LR(1) 解析的结果是，在存在错误的情况下，可能会在声明错误之前进行一些虚假的规约。

## 语义分析

### 属性文法

#### 构造属性文法

![image-20230611232331757](https://media.opennet.top/i/2023/06/11/6485e6f49349f.png)

#### 分析树

![image-20230611232651970](https://media.opennet.top/i/2023/06/11/6485e7bc7c05e.png)

#### 题：构造属性文法

![image-20230611160617641](https://media.opennet.top/i/2023/06/11/6485807bea01e.png)

![image-20230611232909323](https://media.opennet.top/i/2023/06/11/6485e84714503.png)

#### 题：分析树

![image-20230611233014416](https://media.opennet.top/i/2023/06/11/6485e887d398e.png)

#### 题：有数据类型的文法

![image-20230611233329428](https://media.opennet.top/i/2023/06/11/6485e94d6cb83.png)

#### 题：有不同进制的文法

注意 if 语句错误判断

![image-20230611233719848](https://media.opennet.top/i/2023/06/11/6485ea316ca06.png)

![image-20230611233906486](https://media.opennet.top/i/2023/06/11/6485ea9c3aba9.png)



