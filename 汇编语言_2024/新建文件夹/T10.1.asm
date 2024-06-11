

data segment
    x db 0
    y db 0
    z db 0
    w db 0

code segment
; �ӹ��� readInt���Ӽ�������һ���޷����������Ĵ��� AL
readInt proc
    mov ax, 0          ; ��ʼ�� AX Ϊ 0
    mov cx, 0          ; ��ʼ�� CX Ϊ 0

read_loop:
    mov ah, 01h        ; BIOS �жϷ��񣬶�ȡһ���ַ�
    int 21h
    cmp al, 0Dh        ; ����Ƿ�Ϊ�س���
    je end_read        ; ����ǻس�����������ȡ
    sub al, '0'        ; ת���ַ�������
    mov bl, al         ; ���浱ǰ����
    mov ax, cx         ; ����ǰ�ۻ�ֵ�ƶ��� AX
    shl ax, 1          ; AX = AX * 2
    shl ax, 1          ; AX = AX * 4
    shl ax, 1          ; AX = AX * 8
    add ax, cx         ; AX = AX * 10
    add ax, bx         ; AX = AX + ��ǰ����
    mov cx, ax         ; �����ۻ�ֵ�� CX
    jmp read_loop      ; ������ȡ��һ���ַ�

end_read:
    mov ax, cx         ; ���ۻ�ֵ�ƶ��� AX
    ret
readInt endp

; �ӹ��� writeInt���ѼĴ��� AX ��ֵ��ʮ�����޷��������ĸ�ʽ�������ʾ��
writeInt proc
    mov cx, 10         ; ���ó���Ϊ 10
    mov bx, 0          ; ��ʼ�� BX Ϊ 0
    mov dx, 0          ; ��ʼ�� DX Ϊ 0

write_loop:
    xor dx, dx         ; ��� DX
    div cx             ; AX / 10������ AX�������� DX
    push dx            ; ������ѹ���ջ
    inc bx             ; �������� 1
    test ax, ax        ; ��� AX �Ƿ�Ϊ 0
    jnz write_loop     ; ��� AX ��Ϊ 0������ѭ��

print_digits:
    pop dx             ; �Ӷ�ջ�е�������
    add dl, '0'        ; ת�����ֵ��ַ�
    mov ah, 02h        ; BIOS �жϷ�����ʾ�ַ�
    int 21h
    dec bx             ; �������� 1
    jnz print_digits   ; �����������Ϊ 0������ѭ��

    ret
writeInt endp

crlf    proc  near
        
        mov dl,0dh  ;�س�ASCII��0dh��ֵ��dl
        mov ah,2
        int 21h     ;����int21h 2�Ź��ܣ���ʾdl
        
        mov dl,0ah  ;����ASCII��0ah��ֵ��dl
        mov ah,2
        int 21h     ;����int21h 2�Ź��ܣ���ʾdl
        ret
crlf endp

; ������ main
main proc
    mov ax, @data
    mov ds, ax

    ; ���� x
    call readInt
    mov x, al
    
    call crlf
    ; ���� y
    call readInt
    mov y, al
    
    call crlf
    
    ; ���� z
    call readInt
    mov z, al
    
    call crlf
    
    ; ������ʽ w = x + y + 24 - z
    mov al, x
    add al, y
    add al, 24
    sub al, z
    mov w, al

    ; ��� w
    mov bl, w
    call writeInt

    ; ��������
    mov ax, 4C00h
    int 21h
main endp

end main