;��5.5�������� x(x1,x2,����,x10) �� y(y1,y2,����,y10)��
;       ��̼��� z(z1,z2,����,z10)

datarea segment
         x  dw  1,2,11,12,88,3,90,4,2,1     ;��ʼ��X,Y,Z
         y  dw  9,8,1,2,78,7,80,6,8,9
         z  dw  10 dup(?) 
logic_rule  dw  0011101000000000B  
datarea ends

prognam segment   

main proc far
    assume cs:prognam,ds:datarea  
start: 
         push ds
         sub ax,ax
         push ax
            
         mov ax,datarea
         mov ds,ax
    
         mov   bx, 0              ;��������ָ��
         mov   cx, 10             ;����ѭ������
         mov   dx, logic_rule     ;���߼��߸�ֵ��dx
next:    mov   ax, x[bx]
         shl   dx, 1
         jc    subtract
         add   ax, y[bx]
         jmp   short  result       ; ��ǰ����
subtract:   
         sub   ax, y[bx]
result:  mov   z[bx], ax
         add   bx, 2
         loop  next
        
      ;  mov ah, 4ch
      ;  int 21h     
      
      ret
  main endp

prognam ends
      end start         