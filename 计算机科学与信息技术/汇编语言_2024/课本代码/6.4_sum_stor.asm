;��6.4 ������MAIN�͹���PROADD��ͬһԴ�ļ��У�Ҫ���ù���PROADD�ۼ������е�����Ԫ�أ�
;���Ѻͣ�����������Ŀ����ԣ��͵�ָ���Ĵ洢��Ԫ��ȥ�� 
 
data  segment
      ary     dw  1,2,3,4,5,6,7,8,9,10     ;1+2+3....+10=55d=37h
      count   dw  10                       ;���鳤��
      sum     dw  ?                        ;��������sum
data  ends

code  segment
main  proc    far
      assume  cs:code,ds:data   
      
      push    ds                           ;ds,0��ջ��Ϊ����DOS��׼��
      sub     ax, ax
      push    ax 
      
      mov     ax, data                     ;�ε�ַ----�μĴ��� 
      mov     ds, ax                        
      
      call    proadd 
      
      ret
main  endp

;proadd�ӳ���   
proadd  proc  near
        push  ax         ;ax,cx,si����
        push  cx
        push  si     
        
        lea   si, ary     ;�����׵�ַ����si
        mov   cx, count   ;���鳤����Ϊѭ����������cx
        xor   ax, ax      ;ax��Ϊ�ۼ�������
        
next:   add   ax, [si]    ;ax�ۼ�����  ������浽sum
        add   si, 2
        loop  next         
        mov   sum,ax       
        
        pop   si
        pop   cx
        pop   ax  
        
        ret
proadd  endp 

code  ends
   end     main  
   
