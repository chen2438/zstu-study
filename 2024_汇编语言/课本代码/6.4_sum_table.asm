;��6.4 ������MAIN�͹���PROADD��ͬһԴ�ļ��У�Ҫ���ù���PROADD�ۼ������е�����Ԫ�أ�
;���Ѻͣ�����������Ŀ����ԣ��͵�ָ���Ĵ洢��Ԫ��ȥ��  ��ͨ����ַ��
 
data  segment
      ary     dw  1,2,3,4,5,6,7,8,9,10     ;1+2+3....+10=55d=37h
      count   dw  10                       ;���鳤��
      sum     dw  ?                        ;��������sum 
      table   dw  3 dup(?)                 ;��ַ��
data  ends

code  segment
main  proc    far
      assume  cs:code,ds:data   
      
      push    ds                           ;ds,0��ջ��Ϊ����DOS��׼��
      sub     ax, ax
      push    ax 
      
      mov     ax, data                     ;�ε�ַ----�μĴ��� 
      mov     ds, ax 
      
      mov    table,   offset  ary
      mov    table+2, offset  count
      mov    table+4, offset  sum          ; ������ַ��
      mov    bx,      offset  table        ; ��ַ��ĵ�ַ->bx
      call   proadd                      

      
      ret
main  endp

;proadd�ӳ���   
proadd  proc  near
        push  ax         ;ax,cx,si����
        push  cx
        push  si 
        push  di    
        
        mov   si, [bx]
        mov   di, [bx+2]
        mov   cx, [di]
        mov   di, [bx+4]
        xor   ax, ax
next:    
        add   ax, [si]
        add   si, 2
        loop  next
        mov   [di],ax
        pop   di
        pop   si
        pop   cx
        pop   ax
        ret
proadd  endp

code  ends
   end     main  
   
