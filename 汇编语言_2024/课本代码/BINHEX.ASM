program segment           ;建立一个代码段
   main proc far
        assume cs:program ;ds:data   
 start:                   ;程序开始入口     
        push ds           ;ds备份
        sub  ax,ax        ;ax 清零  
        push ax        

        mov bx,0001110011110101B    ;bx初始化  0001 1100 1111 0101B 1CF5
        mov ch,4          ;设计数器为4
 rotate:
        mov cl,4          ;设置移位值为4
        rol bx,cl         ;rol 循环左移4位  (bx)= 1100 1111 0101 0001B
        mov al,bl         ;(al)=0101 0001B
        and al,0fh        ;(al)=0000 0001B
        add al,30h        ;(al)=31H   ASCII 0~9 30H~39H
        
        cmp al,3ah        ;判断al是否为字母A~F  al>3ah 则为字母                             
        jl  printit       ;al<3ah 输出        
        add al,7h         ;al>3ah al为字母 (al)=al+7h ASCII A~F 41H~46H  41H-AH=37H
 printit:
        mov dl,al     
        mov ah,2          ;中断调用 2 号功能，显示dl数据
        int 21h
        
        dec ch
        
        jnz rotate        ;不等于0时跳转
        ret
       main endp      
;      MOV AH,4CH
;      INT 21H                         
program ends                              
    end start