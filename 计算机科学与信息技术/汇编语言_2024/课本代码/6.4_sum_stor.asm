;例6.4 主程序MAIN和过程PROADD在同一源文件中，要求用过程PROADD累加数组中的所有元素，
;并把和（不考虑溢出的可能性）送到指定的存储单元中去。 
 
data  segment
      ary     dw  1,2,3,4,5,6,7,8,9,10     ;1+2+3....+10=55d=37h
      count   dw  10                       ;数组长度
      sum     dw  ?                        ;结果存放在sum
data  ends

code  segment
main  proc    far
      assume  cs:code,ds:data   
      
      push    ds                           ;ds,0进栈，为返回DOS做准备
      sub     ax, ax
      push    ax 
      
      mov     ax, data                     ;段地址----段寄存器 
      mov     ds, ax                        
      
      call    proadd 
      
      ret
main  endp

;proadd子程序   
proadd  proc  near
        push  ax         ;ax,cx,si备份
        push  cx
        push  si     
        
        lea   si, ary     ;数组首地址付给si
        mov   cx, count   ;数组长度作为循环次数付给cx
        xor   ax, ax      ;ax作为累加器清零
        
next:   add   ax, [si]    ;ax累加数组  结果保存到sum
        add   si, 2
        loop  next         
        mov   sum,ax       
        
        pop   si
        pop   cx
        pop   ax  
        
        ret
proadd  endp 

code  ends
   end     main  
   
