;��5.9���ڸ��Ӷ��У���һ������С����˳�����е��޷��������飬���׵�ַ�����DI�Ĵ����У�
;       �����еĵ�һ����Ԫ��������鳤�ȡ���AX����һ���޷�������
;       Ҫ���������в��ң�AX�������ҵ�����ʹCF=0,������SI�и�����Ԫ���������е�ƫ�Ƶ�ַ����δ�ҵ�����ʹCF=1.
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
        ;��PSP����ʼ�߼���ַѹ���ջ��������INT 20H��ָ��ĵ�ַѹ���ջ
        ;����EXE�ļ�װ���ڴ�ʱDS��ES����ָ��PSP�ģ������ָ�PUSH  DS���Ϳ���ʵ�ֽ�PSP�ε�ַѹ���ջ�Ĳ�����     
        PUSH DS      ;��ds��0��ջ��Ϊ����retָ��׼�����ص�ַ��
        MOV AX,0     ;�����ص�ַΪ ds:0, ����psp���ô���ָ�INT 20H"
        PUSH AX
        
        MOV  AX,dseg
        MOV  DS,AX
        MOV  ES,AX
        ;POP  AX
        
        LEA  DI,array       ;�����׵�ַ��ֵ��DI�Ĵ���
        MOV  AX,number      ;�������в���55����55��ֵ��AX
         
        CMP  AX,ES:[DI+2]   ;�ж������һ��Ԫ���Ƿ����(AX)
        JA   chk_last
        LEA  SI,ES:[DI+2]
        JE   exit
        STC 
        JMP  exit 
        
   chk_last:
        MOV SI,ES:[DI]        
        SHL SI,1            ;SI��2����ͬ��SAL
        ADD SI,DI
        CMP AX,ES:[SI]      ;�ж��������һ��Ԫ���Ƿ����(AX)
        JB  search
        JE  exit
        STC
        JMP exit
   
   search:
        MOV low_idx,1        ;low_idx ����С���±�
        MOV BX,ES:[DI]
        MOV high_idx,BX      ;high_idx��������±�
        MOV BX,DI
    
    mid:
        MOV CX,low_idx       ;CX����С���±�
        MOV DX,high_idx      ;DX��������±�
        CMP CX,DX            ;��CX��DX��˵����С�����±��ƶ������ĺ���ȥ��
        JA  no_match         ;����ʧ��
        ADD CX,DX            ;CX=CX+DX
        SHR CX,1             ;CX��2
        MOV SI,CX            ;SI=CX
        SHL SI,1             ;SI��2 ��SI�Ǳȶ�Ԫ���������е�ƫ�Ƶ�ַ
  compare:                  
        CMP AX,ES:[BX+SI]    ;�Ƚ�AX�뵱ǰ�м�Ԫ��ES:[BX+SI]
        JE  exit
        JA  higher           ;(AX)>�м�Ԫ��ES:[BX+SI] ��ת����ǩ higer
        DEC CX               ;(AX)<�м�Ԫ��ES:[BX+SI] CX=CX-1,�����ƶ�һ��Ԫ��
        MOV high_idx,CX      ;high_idx=CX,��CX����high_idx
        JMP mid              ;��ת�� mid
   higher:
        INC CX               ;CX=CX+1,�����ƶ�һ��Ԫ��
        MOV low_idx,CX       ;low_idx=CX,��CX����low_idx
        JMP mid
  no_match:
        STC
  exit:
        ;POP DS  ����Ҫ
        RET  
            
;      MOV AH,4CH
;      INT 21H
        
   b_search ENDP 
    
  cseg ENDS

    END   start