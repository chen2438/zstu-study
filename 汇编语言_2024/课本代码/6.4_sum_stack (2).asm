;��6.4 ������MAIN�͹���PROADD��ͬһԴ�ļ��У�Ҫ���ù���PROADD�ۼ������е�����Ԫ�أ�
;���Ѻͣ�����������Ŀ����ԣ��͵�ָ���Ĵ洢��Ԫ��ȥ��  ��ͨ����ջ��
 
data   segment
       ary    dw  1,2,3,4,5,6,7,8,9,10
       count  dw  10
       sum    dw  ?   
       
       addr   dd  ?
data   ends

stack  segment   
              dw  100    dup (?)
             tos  label  word
stack  ends


code1 segment
main  proc    far
      assume  cs:code1, ds:data, ss:stack
start:
      mov     ax,  stack
      mov     ss,  ax
      mov     sp,  offset  tos 
      
      push    ds
      sub     ax,  ax
      push    ax   
      
      mov     ax,  data
      mov     ds,  ax    
      
      mov     bx,  offset  ary
      push    bx
      mov     bx,  offset  count
      push    bx
      mov     bx,  offset  sum
      push    bx   
      
      mov     word  ptr addr,offset proadd     ;proaddƫ�Ƶ�ַ����addr���ֽ�    
      mov     word  ptr addr+2,seg proadd     ;proaddƫ�Ƶ�ַ����addr���ֽ�
      call    dword ptr addr

   ret
main  endp
code1 ends

code2    segment
  assume cs:code2

proadd   proc  far

  push  bp
  mov   bp, sp

  push  ax
  push  cx
  push  si
  push  di

  mov   si,[bp+0ah]
  mov   di,[bp+8]
  mov   cx,[di]
  mov   di,[bp+6]
 
  xor   ax,  ax
next:
  add   ax,  [si]
  add   si,  2
  loop  next
  mov   [di],ax

  pop   di
  pop   si
  pop   cx
  pop   ax

  pop   bp

  ret   6

proadd  endp   

code2    ends
         end start
