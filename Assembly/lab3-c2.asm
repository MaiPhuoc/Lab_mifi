.model small
.stack 100h
.data

    rows    equ 3 
    columns equ 4
    
    a   db  1,2,3,4
        db  5,6,7,8
        db  9,10,11,12
    
    sum dw ?  
 
.code

 
    mov ax, @data
    mov ds, ax
    
    xor ax,ax
    xor bx,bx
    xor cx,cx   ; clear register
    
    mov bx, rows
    mov cx, columns 
    
    cmp bx,cx  
    jg next
    xchg bx,cx ; cx = min(row, colomns)  
next:
    xor bx,bx
    xor si,si
lap:
    add al,byte ptr a[bx][si]
    adc ah,0  
    add bx,columns
    inc si
    loop lap
    mov sum, ax
 
    mov ah, 4ch
    int 21h
end