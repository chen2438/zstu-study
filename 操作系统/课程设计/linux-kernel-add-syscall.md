---
description: 发布于 2023-11-26
categories:
- linux
date: 2023-11-26
slug: linux-kernel-add-syscall
title: Linux 内核新增系统调用
updated: 
tags:
- linux
- linux-kernel
copyright: true
---

# Linux 内核新增系统调用

以 Debian 12 为例

## 1 下载并解压 Linux Kernel 源码

在 https://www.kernel.org/ 处下载，以 6.6.2 为例。

```bash
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.6.2.tar.xz
tar -xvf linux-6.6.2.tar.xz
cd linux-6.6.2
```

## 2 添加系统调用函数

新增 `kernel/hello.c` 文件如下：

```c
// kernel/hello.c

#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(hello){
    printk(KERN_INFO "Hello, Linux 6.6.2\n");
    return 0;
}
```

`SYSCALL_DEFINE0`是一个宏，用于定义一个不接受任何参数的系统调用。这个宏处理系统调用的名称和参数数量。在这个例子中，`hello`是系统调用的名称。数字`0`表示这个系统调用不接受任何参数。

`printk`是内核中的一个函数，用于输出日志信息。`KERN_INFO`是日志级别，表示这条信息是一条普通的信息性消息。`"Hello, Linux 6.6.2\n"`则是要输出到内核日志的实际消息。当这个系统调用被执行时，这条消息会被记录在内核日志中，可以用`dmesg`命令查看。

## 3 系统调用表中注册系统调用

对于 x86 架构，修改 `arch/x86/entry/syscalls/syscall_64.tbl` 文件

添加以下内容，注意代码序号，按序存放

```
# For x86_64
335     64      hello                   sys_hello
```

![image-20231126110615447](https://media.opennet.top/i/2023/11/26/i9g99w-0.png)

## 4 在系统调用头文件中声明

修改`include/linux/syscalls.h`，在最后一行`#endif`之前添加以下代码

![image-20231126110755062](https://media.opennet.top/i/2023/11/26/iaiv33-0.png)

```c
// include/linux/syscalls.h

asmlinkage long sys_hello(void);
```

`asmlinkage`是一个宏，它用于告诉编译器该函数的参数不是通过寄存器传递的（这是C调用惯例的常见方式），而是通过系统调用的堆栈传递的。

这是因为用户空间程序通常通过`syscall`指令来进行系统调用，该指令将参数放在寄存器中，而系统调用服务例程（即系统调用的实际实现）需要从堆栈中获取这些参数。

## 5 在 kernel 目录下的 Makefile 中添加引用

修改 `kernel/Makefile`，更新代码如下

在 `obj-y` 的最后添加 `hello.c`

![image-20231126111121382](https://media.opennet.top/i/2023/11/26/icgz28-0.png)

## 6 重新编译并安装内核

安装依赖

```bash
apt install dwarves build-essential libncurses-dev bison flex libssl-dev libelf-dev bc
```

构建之前确保你在 linux-6.6.2 目录下

编译内核需要很长的时间

```bash
make defconfig       # 使用默认配置
# make menuconfig    # 或者自选配置
make -j$(nproc)      # 编译内核
make modules_install # 安装内核模块
make install         # 安装内核
```

在编译内核后出现`Kernel: arch/x86/boot/bzImage is ready  (#1)`表示成功

对于使用 grub 的机器，使用以下命令安装内核，然后重启系统

```bash
update-grub
reboot
```

重启后使用 `uname -a` 检查内核版本，如下表示成功

![image-20231126112149534](https://media.opennet.top/i/2023/11/26/iitla4-0.png)

## 7 测试系统调用

编写 `hello.c` 程序

```c
#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#define SYS_hello 335 // 使用你在syscall_64.tbl中设置的系统调用号

int main(){
    long int ret = syscall(SYS_hello);
    printf("System call returned %ld\n", ret);
    return 0;
}
```

编译运行

```bash
gcc -o hello hello.c
./hello
```

出现 returned 0 表示成功，-1表示失败

![image-20231126112439173](https://media.opennet.top/i/2023/11/26/ikayjm-0.png)

在 dmesg 中查看消息

```bash
dmesg | tail
```

![image-20231126113652523](https://media.opennet.top/i/2023/11/26/irs8bj-0.png)

可以看到输出了 `Hello, Linux 6.6.2`
