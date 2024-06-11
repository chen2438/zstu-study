data segment
    X dw 1122H
	Y dw 3344H
	Z dw ?
data ends

program segment
 ;   main proc far
        assume cs:program,ds:data
        
start:
;   push ds
;   sub  ax,ax
;   push ax
    
    mov ax,data
    mov ds,ax
	
	mov ax,X
	add ax,Y
	mov Z,ax
	
	
	
MOV AH,4CH
INT 21H
    

;    ret
; main endp
    
program ends
    end start