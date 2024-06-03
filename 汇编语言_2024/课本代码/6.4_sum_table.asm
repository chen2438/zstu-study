;例6.4 主程序MAIN和过程PROADD在同一源文件中，要求用过程PROADD累加数组中的所有元素，
;并把和（不考虑溢出的可能性）送到指定的存储单元中去。  （通过地址表）
 
data  segment
      ary     dw  1,2,3,4,5,6,7,8,9,10     ;1+2+3....+10=55d=37h
      count   dw  10                       ;数组长度
      sum     dw  ?                        ;结果存放在sum 
      table   dw  3 dup(?)                 ;地址表
data  ends

code  segment
main  proc    far
      assume  cs:code,ds:data   
      
      push    ds                           ;ds,0进栈，为返回DOS做准备
      sub     ax, ax
      push    ax 
      
      mov     ax, data                     ;段地址----段寄存器 
      mov     ds, ax 
      
      mov    table,   offset  ary
      mov    table+2, offset  count
      mov    table+4, offset  sum          ; 建立地址表
      mov    bx,      offset  table        ; 地址表的地址->bx
      call   proadd                      

      
      ret
main  endp

;proadd子程序   
proadd  proc  near
        push  ax         ;ax,cx,si备份
        push  cx
        push  si 
        push  di    
        
        mov   si, [bx]
        mov   di, [bx+2]
        mov   cx, [di]
        mov   di, [bx+4]
        xor   ax, ax
next:    
        add   ax, [si]
        add   si, 2
        loop  next
        mov   [di],ax
        pop   di
        pop   si
        pop   cx
        pop   ax
        ret
proadd  endp

code  ends
   end     main  
   
