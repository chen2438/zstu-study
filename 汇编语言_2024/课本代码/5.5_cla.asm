;例5.5：有数组 x(x1,x2,……,x10) 和 y(y1,y2,……,y10)，
;       编程计算 z(z1,z2,……,z10)

datarea segment
         x  dw  1,2,11,12,88,3,90,4,2,1     ;初始化X,Y,Z
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
    
         mov   bx, 0              ;设置数组指针
         mov   cx, 10             ;设置循环次数
         mov   dx, logic_rule     ;将逻辑尺赋值给dx
next:    mov   ax, x[bx]
         shl   dx, 1
         jc    subtract
         add   ax, y[bx]
         jmp   short  result       ; 向前引用
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