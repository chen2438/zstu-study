;例6.9 把一个十六进制数转换成十进制数的程序，要求把从键盘输入的0~FFFFH的
;十六进制正数转换为十进制数并在屏幕上显示出来。 (通过寄存器传送参数）

hexidec segment
    assume cs:hexidec
main proc far 
    
start: push ds
       sub  ax,ax
       push ax
           
repeat: call hexibin ;键盘输入十六转换为二进制数
        call crlf    ;回车换行
        call binidec ;二进制转换为十进制
        call crlf    ;回车换行
        jmp  repeat  ;重复 
        ret
main endp

;子过程，键盘输入16进制转换为二进制数存入bx (通过bx寄存器传送参数）
hexibin proc near
        mov bx,0     ;bx清零，初始化
newchar:
      mov  ah, 1         ;调用21H中断1号指令，在显示器输入数据
      int  21h           ;输入的数据在 al寄存器中
      sub  al, 30h
      jl   exit          ; <0 退出
      cmp  al, 10
      jl   add_to
      sub  al, 27h       ; ‘a’~‘f’
      cmp  al, 0ah
      jl   exit          ; <‘a’ 退出
      cmp  al, 10h
      jge  exit          ; >’f’ 退出
add_to: 
      mov   cl, 4
      shl   bx, cl
      mov   ah, 0
      add   bx, ax
      jmp   newchar

exit: 
      ret
hexibin endp

;子程序，bx二进制数转换为十进制数输出 (通过cx寄存器传送参数）
binidec  proc near
         mov cx,10000d
         call dec_div
         mov cx,1000d
         call dec_div
         mov cx,100d 
         call dec_div 
         mov cx,10d 
         call dec_div
         mov cx,1d
         call dec_div
        
         ret               
binidec  endp   

dec_div  proc  near
         mov   ax, bx
         mov   dx, 0
         div   cx         ;被除数默认在DX:AX中,商在AX中，余数在DX中
         mov   bx, dx
         mov   dl, al
         add   dl, 30h
         mov   ah, 2      ;调用21H中断2号指令，在显示器显示dl数据
         int   21h
         ret
dec_div  endp


;子程序，回车换行  
crlf    proc  near
        
        mov dl,0dh  ;回车ASCII码0dh赋值给dl
        mov ah,2
        int 21h     ;调用int21h 2号功能，显示dl
        
        mov dl,0ah  ;换行ASCII码0ah赋值给dl
        mov ah,2
        int 21h     ;调用int21h 2号功能，显示dl
        ret
crlf endp

hexidec ends
     end start