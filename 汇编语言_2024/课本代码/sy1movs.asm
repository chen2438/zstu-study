data segment
    SOURCE_BUFFER db 20 dup ('A')
data ends

extra segment
    DEST_BUFFER db 20 dup(0)
extra ends

program segment
 ;   main proc far
        assume cs:program,ds:data,es:extra
        
start:
;   push ds
;   sub  ax,ax
;   push ax
    
    mov ax,data
    mov ds,ax
	
	mov ax,extra
    mov es,ax
	
	lea si,SOURCE_BUFFER
	lea di,DEST_BUFFER
	mov cx,20
	cld
	rep movsb	
		
	
MOV AH,4CH
INT 21H
    

;    ret
; main endp
    
program ends
    end start