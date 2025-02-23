 frame   struc
        save_bp      dw   ?
        save_cs_ip   dw   2 dup(?)
        n            dw   ?
        result_addr  dw   ?
frame   ends

data    segment
        n_v          dw   3
        result       dw   ?
data    ends

stack   segment stack
        dw   128     dup (?)
        tos  label   word
stack   ends

code  segment
main  proc  far
      assume  cs:code, ds:data, ss:stack
start:
      mov   ax, stack
      mov   ss, ax
      mov   sp, offset tos
      push  ds
      sub   ax, ax
      push  ax
      mov   ax, data
      mov   ds, ax
      mov   bx, offset result
      push  bx
      mov   bx, n_v
      push  bx

      call  far ptr  fact

      ret
main  endp
code  ends

code1  segment
       assume  cs:code1
fact  proc  far
       push  bp
       mov   bp, sp
       push  bx
       push  ax

       mov   bx, [bp].result_addr
       mov   ax, [bp].n
       cmp   ax, 0
       je    done
       push  bx
       dec   ax
       push  ax
       call far ptr fact
       mov   bx, [bp].result_addr
       mov   ax, [bx]
       mul   [bp].n
       jmp   short  return
done:  mov   ax,1
return:
       mov   [bx], ax
       pop   ax
       pop   bx
       pop   bp
       ret   4
fact  endp
code1  ends

end start