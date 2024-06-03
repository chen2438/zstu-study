;例5.9：在附加段中，有一个按从小到大顺序排列的无符号数数组，
;       其首地址存放在DI寄存器中，数组中的第一个单元存放着数组长度。
;       在AX中有一个无符号数，要求在数组中查找（AX），如找到，则使CF=0,
;       并且在SI中给出该元素在数组中的偏移地址；如未找到，则使CF=1.
dseg segment
    array    DW 12,11,22,33,44,55,66,77,88,99,111,222,333 
    number   DW 55
    low_idx  DW ?
    high_idx DW ?
dseg ends

cseg segment
   b_search proc far  
        assume cs:cseg,ds:dseg,es:dseg
 start:       
        ;将PSP的起始逻辑地址压入堆栈，即将“INT 20H”指令的地址压入堆栈
        ;由于EXE文件装入内存时DS和ES都是指向PSP的，因此用指令“PUSH  DS”就可以实现将PSP段地址压入堆栈的操作。     
        push ds      ;把ds和0入栈，为最后的ret指令准备返回地址。
        mov ax,0     ;即返回地址为 ds:0, 返回psp，该处是指令“INT 20H"
        push ax
        
        mov  ax,dseg
        mov  ds,ax
        mov  es,ax 
        
        mov di,0
        mov ax,number
 search:
        mov si,[di]
 even_idx:
        test si,1
        jz  add_idx
        inc si
 add_idx:
        add di,si
 compare:
        cmp ax,[di]
        je  all_done
        ja  higher
        cmp si,2
        jne idx_ok
 no_match:
        stc
        jmp exit
 idx_ok:
        shr  si,1
        test si,1
        jz   sub_idx
        inc  si
 sub_idx:
        sub di,si
        jmp short compare
 higher:
        cmp si,2
        je  no_match
        shr si,1
        jmp short even_idx                                                  
 all_done:
        mov si,di
 exit:       
        RET  
            
;      MOV AH,4CH
;      INT 21H
        
   b_search ENDP 
    
  cseg ENDS

    END   start