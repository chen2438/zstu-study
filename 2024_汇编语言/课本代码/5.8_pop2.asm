data segment
    a dw 100,30,78,99,15,-1,66,45,189,255   
                
data ends       

program segment
    assume cs:program,ds:data
start:
    mov ax,data
    mov ds,ax

    mov cx,10                ;10������������Ƚ�9��
    dec cx
loop1: 
    mov dx,1                      
    mov di,cx                ;
    mov bx,0
loop2:
    mov ax,a[bx]             
    cmp ax,a[bx+2]           ;�Ƚ����������ڴ浥Ԫ
    jge cotinue              ;>=ʱ��ת��cotinue
    xchg ax,a[bx+2]          ;<ʱ����������
    mov a[bx],ax
    sub dx,dx                ;�н���ʱbx����Ϊ0
    
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