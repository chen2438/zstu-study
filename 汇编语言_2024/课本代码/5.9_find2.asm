;��5.9���ڸ��Ӷ��У���һ������С����˳�����е��޷��������飬
;       ���׵�ַ�����DI�Ĵ����У������еĵ�һ����Ԫ��������鳤�ȡ�
;       ��AX����һ���޷�������Ҫ���������в��ң�AX�������ҵ�����ʹCF=0,
;       ������SI�и�����Ԫ���������е�ƫ�Ƶ�ַ����δ�ҵ�����ʹCF=1.
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
        ;��PSP����ʼ�߼���ַѹ���ջ��������INT 20H��ָ��ĵ�ַѹ���ջ
        ;����EXE�ļ�װ���ڴ�ʱDS��ES����ָ��PSP�ģ������ָ�PUSH  DS���Ϳ���ʵ�ֽ�PSP�ε�ַѹ���ջ�Ĳ�����     
        push ds      ;��ds��0��ջ��Ϊ����retָ��׼�����ص�ַ��
        mov ax,0     ;�����ص�ַΪ ds:0, ����psp���ô���ָ�INT 20H"
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