;例5.9：在附加段中，有一个按从小到大顺序排列的无符号数数组，其首地址存放在DI寄存器中，
;       数组中的第一个单元存放着数组长度。在AX中有一个无符号数，
;       要求在数组中查找（AX），如找到，则使CF=0,并且在SI中给出该元素在数组中的偏移地址；如未找到，则使CF=1.
dseg SEGMENT
    array    DW 12,11,22,33,44,55,66,77,88,99,111,222,333 
    number   DW 55
    low_idx  DW ?
    high_idx DW ?
dseg ENDS

cseg SEGMENT
   ;b_search PROC near  
   b_search PROC far  
        assume CS:cseg,DS:dseg,ES:dseg
 start:       
        ;将PSP的起始逻辑地址压入堆栈，即将“INT 20H”指令的地址压入堆栈
        ;由于EXE文件装入内存时DS和ES都是指向PSP的，因此用指令“PUSH  DS”就可以实现将PSP段地址压入堆栈的操作。     
        PUSH DS      ;把ds和0入栈，为最后的ret指令准备返回地址。
        MOV AX,0     ;即返回地址为 ds:0, 返回psp，该处是指令“INT 20H"
        PUSH AX
        
        MOV  AX,dseg
        MOV  DS,AX
        MOV  ES,AX
        ;POP  AX
        
        LEA  DI,array       ;数组首地址赋值给DI寄存器
        MOV  AX,number      ;在数组中查找55，将55赋值给AX
         
        CMP  AX,ES:[DI+2]   ;判断数组第一个元素是否等于(AX)
        JA   chk_last
        LEA  SI,ES:[DI+2]
        JE   exit
        STC 
        JMP  exit 
        
   chk_last:
        MOV SI,ES:[DI]        
        SHL SI,1            ;SI乘2，等同于SAL
        ADD SI,DI
        CMP AX,ES:[SI]      ;判断数组最后一个元素是否等于(AX)
        JB  search
        JE  exit
        STC
        JMP exit
   
   search:
        MOV low_idx,1        ;low_idx 放最小数下标
        MOV BX,ES:[DI]
        MOV high_idx,BX      ;high_idx放最大数下标
        MOV BX,DI
    
    mid:
        MOV CX,low_idx       ;CX放最小数下标
        MOV DX,high_idx      ;DX放最大数下标
        CMP CX,DX            ;如CX比DX大，说明最小数的下标移动到最大的后面去了
        JA  no_match         ;查找失败
        ADD CX,DX            ;CX=CX+DX
        SHR CX,1             ;CX除2
        MOV SI,CX            ;SI=CX
        SHL SI,1             ;SI乘2 ，SI是比对元素在数组中的偏移地址
  compare:                  
        CMP AX,ES:[BX+SI]    ;比较AX与当前中间元素ES:[BX+SI]
        JE  exit
        JA  higher           ;(AX)>中间元素ES:[BX+SI] 跳转到标签 higer
        DEC CX               ;(AX)<中间元素ES:[BX+SI] CX=CX-1,向上移动一个元素
        MOV high_idx,CX      ;high_idx=CX,用CX更新high_idx
        JMP mid              ;跳转到 mid
   higher:
        INC CX               ;CX=CX+1,向下移动一个元素
        MOV low_idx,CX       ;low_idx=CX,用CX更新low_idx
        JMP mid
  no_match:
        STC
  exit:
        ;POP DS  不需要
        RET  
            
;      MOV AH,4CH
;      INT 21H
        
   b_search ENDP 
    
  cseg ENDS

    END   start