 .model  small
    .stack  100h
    .data   
    a   dw  1100100001100110b
    .code
    mov ax,@data
    mov ds,ax
    mov ax,a
    mov cx,16    ; 16 bit
    mov dx,0     ; this register will receive the result
    begin_loop:
    test ax,1      ; check the last bit
    jnz number_1   ; if 1
    dec cx  
    shr ax,1       ; check the next bit
    jnz begin_loop ; if not 1
    number_1:
    inc dx
    dec cx 
    shr ax,1
    jnz begin_loop
    mov ax,4c00h
    int 21h
    end