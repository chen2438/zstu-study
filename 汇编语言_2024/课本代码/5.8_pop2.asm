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
    mov dx,1                      
    mov di,cx                ;
    mov bx,0
loop2:
    mov ax,a[bx]             
    cmp ax,a[bx+2]           ;比较两个相邻内存单元
    jge cotinue              ;>=时跳转到cotinue
    xchg ax,a[bx+2]          ;<时交换两个数
    mov a[bx],ax
    sub dx,dx                ;有交换时bx设置为0
    
cotinue:
    add bx,2
    loop loop2
    
    mov cx,di
    cmp dx,0
    loopz loop1
    
    mov ax,4ch
    int 21h        

program ends
end start