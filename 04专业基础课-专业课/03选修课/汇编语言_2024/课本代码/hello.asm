  ; 程序功能是显示字符串 "hello world."

data SEGMENT    ; 定义数据段
; 定义变量 message和pkey
    x DW 0x1234  ; 假设x的值为0x1234（十进制的4660）  
    y DW 0x5678  ; 假设y的值为0x5678（十进制的22136）  
    z DW 0xABCD  ; 假设z的值为0xABCD（十进制的43981）
data ENDS

stack SEGMENT stack   ; 定义堆栈段
DW   128  dup(0)
stack ENDS

code SEGMENT   ; 定义代码段
assume CS:code,DS:data,SS:stack   ;关联段寄存器和段名
start:
; data段名表示该段的段地址，赋值给数据段寄存器DS
MOV AX, data
MOV DS, AX


MOV AX，Y                    
IMUL Z
MOV CX，AC
MOV BX，DX
MOV AX，X
CWD
ADD AX，CX
ADC DX，BX
SUB AX，158
SBB DX，0
IDIV X

code ENDS

END start ; END伪指令指明此为源程序末尾，并指定程序入口是start标号


