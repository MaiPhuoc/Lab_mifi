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
    mov bx, ax
    and bx, 1b   
    add dx,bx
    shr ax,1     
    loop begi       n_loop
    
    mov ax,4c00h
    int 21h
    end