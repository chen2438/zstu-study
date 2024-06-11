
data segment
    x db 0
    y db 0
    z db 0
    w db 0
    buffer db 6 dup(0) ; 用于存储输入的字符串，假设最大输入长度为5位数

code segment
; 子过程 readInt，从键盘输入一个无符号整数到寄存器 AX
readInt proc
    mov si, offset buffer ; 将缓冲区地址存入 SI
    mov cx, 0             ; 初始化计数器

read_loop:
    mov ah, 01h           ; BIOS 中断服务，读取一个字符
    int 21h
    cmp al, 0Dh           ; 检查是否为回车键
    je end_read           ; 如果是回车键，结束读取
    sub al, '0'           ; 转换字符到数字
    stosb                 ; 将数字存入缓冲区
    inc cx                ; 计数器加 1
    jmp read_loop         ; 继续读取下一个字符

end_read:
    mov si, offset buffer ; 重置 SI 指向缓冲区起始位置
    mov ax, 0             ; 初始化 AX 为 0

convert_loop:
    lodsb                 ; 从缓冲区读取一个字节
    sub al, '0'           ; 转换字符到数字
    mov bx, 10
    mul bx                ; AX = AX * 10
    add ax, ax            ; AX = AX + 当前数字
    loop convert_loop     ; 循环，直到 CX 为 0

    ret
readInt endp

; 子过程 writeInt，把寄存器 AX 的值以十进制无符号整数的格式输出到显示器
writeInt proc
    mov cx, 10            ; 设置除数为 10
    mov bx, 0             ; 初始化 BX 为 0
    mov dx, 0             ; 初始化 DX 为 0

write_loop:
    xor dx, dx            ; 清空 DX
    div cx                ; AX / 10，商在 AX，余数在 DX
    push dx               ; 将余数压入堆栈
    inc bx                ; 计数器加 1
    test ax, ax           ; 检查 AX 是否为 0
    jnz write_loop        ; 如果 AX 不为 0，继续循环

print_digits:
    pop dx                ; 从堆栈中弹出余数
    add dl, '0'           ; 转换数字到字符
    mov ah, 02h           ; BIOS 中断服务，显示字符
    int 21h
    dec bx                ; 计数器减 1
    jnz print_digits      ; 如果计数器不为 0，继续循环

    ret
writeInt endp

crlf    proc  near
        
        mov dl,0dh  ;回车ASCII码0dh赋值给dl
        mov ah,2
        int 21h     ;调用int21h 2号功能，显示dl
        
        mov dl,0ah  ;换行ASCII码0ah赋值给dl
        mov ah,2
        int 21h     ;调用int21h 2号功能，显示dl
        ret
crlf endp

; 主过程 main
main proc
    mov ax, @data
    mov ds, ax

    ; 输入 x
    call readInt
    mov x, al
    call crlf
    
    ; 输入 y
    call readInt
    mov y, al
    call crlf

    ; 输入 z
    call readInt
    mov z, al
    call crlf

    ; 计算表达式 w = x + y + 24 - z
    mov al, x
    add al, y
    add al, 24
    sub al, z
    mov w, al

    ; 输出 w
    mov bl, w
    call writeInt

    ; 结束程序
    mov ax, 4C00h
    int 21h
main endp

end main