 datarea segment                      ;����һ�����ݶ�
    x          dw ?
    array_head dw 3,5,15,23,37,49,52,65,78,99
    array_end  dw 105
        n      dw 32 
datarea ends   

prognam segment   
main proc far                       ;����������ΪԶ���̣�ʵ�ֳ��򷵻ز���ϵͳ    
    assume cs:prognam,ds:datarea
start:
    push ds
    sub  ax,ax
    push ax
    
    mov ax,datarea                   ;�����ݶε�ַ����ds�Ĵ���
    mov ds,ax
    
    mov ax,n                         ;��n��ֵ��ax�Ĵ���
    mov array_head-2,0ffffh 
    mov si,0

compare: 
    cmp array_end[si],ax
    jle insert                       ;С�ڵ���ʱ��ת
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