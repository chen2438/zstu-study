 datarea segment                      ;建立一个数据段
    x          dw ?
    array_head dw 3,5,15,23,37,49,52,65,78,99
    array_end  dw 105
        n      dw 32 
datarea ends   

prognam segment   
main proc far                       ;将主程序定义为远过程，实现程序返回操作系统    
    assume cs:prognam,ds:datarea
start:
    push ds
    sub  ax,ax
    push ax
    
    mov ax,datarea                   ;将数据段地址赋给ds寄存器
    mov ds,ax
    
    mov ax,n                         ;将n赋值给ax寄存器
    mov array_head-2,0ffffh 
    mov si,0

compare: 
    cmp array_end[si],ax
    jle insert                       ;小于等于时跳转
    mov bx,array_end[si]
    mov array_end[si+2],bx
    sub si,2
    jmp short compare

insert:
    mov array_end[si+2],ax
    ret
   main endp

;    mov ah,4ch
;    int 21h  

prognam ends
    end start