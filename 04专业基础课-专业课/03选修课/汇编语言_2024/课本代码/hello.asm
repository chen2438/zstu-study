  ; ����������ʾ�ַ��� "hello world."

data SEGMENT    ; �������ݶ�
; ������� message��pkey
    x DW 0x1234  ; ����x��ֵΪ0x1234��ʮ���Ƶ�4660��  
    y DW 0x5678  ; ����y��ֵΪ0x5678��ʮ���Ƶ�22136��  
    z DW 0xABCD  ; ����z��ֵΪ0xABCD��ʮ���Ƶ�43981��
data ENDS

stack SEGMENT stack   ; �����ջ��
DW   128  dup(0)
stack ENDS

code SEGMENT   ; ��������
assume CS:code,DS:data,SS:stack   ;�����μĴ����Ͷ���
start:
; data������ʾ�öεĶε�ַ����ֵ�����ݶμĴ���DS
MOV AX, data
MOV DS, AX


MOV AX��Y                    
IMUL Z
MOV CX��AC
MOV BX��DX
MOV AX��X
CWD
ADD AX��CX
ADC DX��BX
SUB AX��158
SBB DX��0
IDIV X

code ENDS

END start ; ENDαָ��ָ����ΪԴ����ĩβ����ָ�����������start���


