;��6.9 ��һ��ʮ��������ת����ʮ�������ĳ���Ҫ��ѴӼ��������0~FFFFH��
;ʮ����������ת��Ϊʮ������������Ļ����ʾ������ (ͨ���Ĵ������Ͳ�����

hexidec segment
    assume cs:hexidec
main proc far 
    
start: push ds
       sub  ax,ax
       push ax
           
repeat: call hexibin ;��������ʮ��ת��Ϊ��������
        call crlf    ;�س�����
        call binidec ;������ת��Ϊʮ����
        call crlf    ;�س�����
        jmp  repeat  ;�ظ� 
        ret
main endp

;�ӹ��̣���������16����ת��Ϊ������������bx (ͨ��bx�Ĵ������Ͳ�����
hexibin proc near
        mov bx,0     ;bx���㣬��ʼ��
newchar:
      mov  ah, 1         ;����21H�ж�1��ָ�����ʾ����������
      int  21h           ;����������� al�Ĵ�����
      sub  al, 30h
      jl   exit          ; <0 �˳�
      cmp  al, 10
      jl   add_to
      sub  al, 27h       ; ��a��~��f��
      cmp  al, 0ah
      jl   exit          ; <��a�� �˳�
      cmp  al, 10h
      jge  exit          ; >��f�� �˳�
add_to: 
      mov   cl, 4
      shl   bx, cl
      mov   ah, 0
      add   bx, ax
      jmp   newchar

exit: 
      ret
hexibin endp

;�ӳ���bx��������ת��Ϊʮ��������� (ͨ��cx�Ĵ������Ͳ�����
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
         div   cx         ;������Ĭ����DX:AX��,����AX�У�������DX��
         mov   bx, dx
         mov   dl, al
         add   dl, 30h
         mov   ah, 2      ;����21H�ж�2��ָ�����ʾ����ʾdl����
         int   21h
         ret
dec_div  endp


;�ӳ��򣬻س�����  
crlf    proc  near
        
        mov dl,0dh  ;�س�ASCII��0dh��ֵ��dl
        mov ah,2
        int 21h     ;����int21h 2�Ź��ܣ���ʾdl
        
        mov dl,0ah  ;����ASCII��0ah��ֵ��dl
        mov ah,2
        int 21h     ;����int21h 2�Ź��ܣ���ʾdl
        ret
crlf endp

hexidec ends
     end start