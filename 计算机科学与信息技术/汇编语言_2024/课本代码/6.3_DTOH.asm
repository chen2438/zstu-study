;例6.3：十进制到十六进制的转换程序。程序要求从键盘取得一个十进制数，
;然后把该数以十六进制形式在屏幕上显示出来。（通过寄存器传送参数） 

decihex segment
    assume cs:decihex
main proc far
repeat: call decibin ;键盘输入转换为二进制数
        call crlf    ;回车换行
        call binihex ;二进制转换为十六进制
        call crlf    ;回车换行
        jmp  repeat  ;重复
main endp

;子过程，键盘输入转换为二进制数存入bx （通过 bx 寄存器传送参数）
decibin proc near
        mov bx,0     ;bx清零，初始化
newchar:
        mov ah,1
        int 21h      ;调用21号中断1号指令，键盘输入al
        
        sub al,30h   ;ASCII转换为二进制
        jl  exit     ;al<0退出
        cmp al,9d    
        jg  exit     ;al>9退出
        cbw          ;al扩展到ax 
        
        xchg ax,bx
        mov  cx,10d
        mul  cx      ;cx=cx*ax
        xchg ax,bx  
        add  bx,ax
        jmp  newchar
exit:
        ret
decibin endp

;子程序，bx二进制数转换为十六进制数输出 （通过 bx 寄存器传送参数）
binihex  proc near
        mov ch,4    ;设置计数器
rotate:
        mov cl,4    ;设置移位位数
        rol bx,cl   ;bx循环左移4位，将最高位移到低四位
        mov al,bl   ;bx低8位赋值给al
        and al,0fh  ;将al前四位清零
        add al,30h  ;al数据转换为ASCII码
        cmp al,3ah  ;判断al是否大于9
        jl  printit
        add al,7h   ;转换成相应的a~f小写字母，大写+27H
printit:
        mov dl,al   ;将ASCII赋值给dl
        mov ah,2
        int 21h     ;调用21h中断2号指令，在显示器上输出dl
        
        dec ch      ;计数器减一
        jnz rotate  ;计数器不为零跳转到rotate再次转换
        
        ret               
binihex  endp

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

decihex ends
     end main