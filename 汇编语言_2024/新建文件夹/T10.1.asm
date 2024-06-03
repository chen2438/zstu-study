

data segment
    x db 0
    y db 0
    z db 0
    w db 0

code segment
; 子过程 readInt，从键盘输入一个无符号整数到寄存器 AL
readInt proc
    mov ax, 0          ; 初始化 AX 为 0
    mov cx, 0          ; 初始化 CX 为 0

read_loop:
    mov ah, 01h        ; BIOS 中断服务，读取一个字符
    int 21h
    cmp al, 0Dh        ; 检查是否为回车键
    je end_read        ; 如果是回车键，结束读取
    sub al, '0'        ; 转换字符到数字
    mov bl, al         ; 保存当前数字
    mov ax, cx         ; 将当前累积值移动到 AX
    shl ax, 1          ; AX = AX * 2
    shl ax, 1          ; AX = AX * 4
    shl ax, 1          ; AX = AX * 8
    add ax, cx         ; AX = AX * 10
    add ax, bx         ; AX = AX + 当前数字
    mov cx, ax         ; 保存累积值到 CX
    jmp read_loop      ; 继续读取下一个字符

end_read:
    mov ax, cx         ; 将累积值移动到 AX
    ret
readInt endp

; 子过程 writeInt，把寄存器 AX 的值以十进制无符号整数的格式输出到显示器
writeInt proc
    mov cx, 10         ; 设置除数为 10
    mov bx, 0          ; 初始化 BX 为 0
    mov dx, 0          ; 初始化 DX 为 0

write_loop:
    xor dx, dx         ; 清空 DX
    div cx             ; AX / 10，商在 AX，余数在 DX
    push dx            ; 将余数压入堆栈
    inc bx             ; 计数器加 1
    test ax, ax        ; 检查 AX 是否为 0
    jnz write_loop     ; 如果 AX 不为 0，继续循环

print_digits:
    pop dx             ; 从堆栈中弹出余数
    add dl, '0'        ; 转换数字到字符
    mov ah, 02h        ; BIOS 中断服务，显示字符
    int 21h
    dec bx             ; 计数器减 1
    jnz print_digits   ; 如果计数器不为 0，继续循环

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