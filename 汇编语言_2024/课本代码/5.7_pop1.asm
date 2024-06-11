;例5.7：有一个首地址为A的N字数组，编制程序使该数组中的数按照从大到小的次序整序。

data segment
    a dw 100,30,78,99,15,-1,66,45,189,255   
                
data ends       

program segment
    assume cs:program,ds:data
start:
    mov ax,data
    mov ds,ax

    mov cx,10                ;10个数排序，排序比较9次
    dec cx
loop1:                       
    mov di,cx                
    mov bx,0
loop2:
    mov ax,a[bx]             
    cmp ax,a[bx+2]           ;比较两个相邻内存单元
    jge cotinue              ;>=时跳转到cotinue
    xchg ax,a[bx+2]          ;<时交换两个数
    mov a[bx],ax
    
cotinue:
    add bx,2
    loop loop2
    
    mov cx,di                ;依次找出最小的数
    loop loop1
    
    mov ah,4ch
    int 21h        

program ends
end start