;��6.3��ʮ���Ƶ�ʮ�����Ƶ�ת�����򡣳���Ҫ��Ӽ���ȡ��һ��ʮ��������
;Ȼ��Ѹ�����ʮ��������ʽ����Ļ����ʾ��������ͨ���Ĵ������Ͳ����� 

decihex segment
    assume cs:decihex
main proc far
repeat: call decibin ;��������ת��Ϊ��������
        call crlf    ;�س�����
        call binihex ;������ת��Ϊʮ������
        call crlf    ;�س�����
        jmp  repeat  ;�ظ�
main endp

;�ӹ��̣���������ת��Ϊ������������bx ��ͨ�� bx �Ĵ������Ͳ�����
decibin proc near
        mov bx,0     ;bx���㣬��ʼ��
newchar:
        mov ah,1
        int 21h      ;����21���ж�1��ָ���������al
        
        sub al,30h   ;ASCIIת��Ϊ������
        jl  exit     ;al<0�˳�
        cmp al,9d    
        jg  exit     ;al>9�˳�
        cbw          ;al��չ��ax 
        
        xchg ax,bx
        mov  cx,10d
        mul  cx      ;cx=cx*ax
        xchg ax,bx  
        add  bx,ax
        jmp  newchar
exit:
        ret
decibin endp

;�ӳ���bx��������ת��Ϊʮ����������� ��ͨ�� bx �Ĵ������Ͳ�����
binihex  proc near
        mov ch,4    ;���ü�����
rotate:
        mov cl,4    ;������λλ��
        rol bx,cl   ;bxѭ������4λ�������λ�Ƶ�����λ
        mov al,bl   ;bx��8λ��ֵ��al
        and al,0fh  ;��alǰ��λ����
        add al,30h  ;al����ת��ΪASCII��
        cmp al,3ah  ;�ж�al�Ƿ����9
        jl  printit
        add al,7h   ;ת������Ӧ��a~fСд��ĸ����д+27H
printit:
        mov dl,al   ;��ASCII��ֵ��dl
        mov ah,2
        int 21h     ;����21h�ж�2��ָ�����ʾ�������dl
        
        dec ch      ;��������һ
        jnz rotate  ;��������Ϊ����ת��rotate�ٴ�ת��
        
        ret               
binihex  endp

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

decihex ends
     end main