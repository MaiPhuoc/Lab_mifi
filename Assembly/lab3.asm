.model small
.stack 100h
.data
    rows    equ 4 
    columns equ 3
    
    a   db  1,2,3,4
        db  5,6,7,8
        db  9,10,1,12
 
    sum dw ?
 
.code 
    mov ax, @data
    mov ds, ax
 
    xor bx, bx  ; index of row
    xor ax, ax  ; result
    xor dx, dx     

c_external:
    mov cx, rows 
    push  cx  
    mov cx, columns 
    xor si, si  
 
; ************************************************************************************  
        c_internal: 
        
        cmp dx, si  
        je summ     
        jne next    
    
        summ:
        add al, byte ptr a[bx][si] 
        adc ah, 0
        
        next:
        inc si      
        
        loop c_internal
; ************************************************************************************
    pop cx 
    inc dx  
    add bx,columns
    cmp dx, rows
    je exit     
loop c_external
    exit:
    mov sum, ax
 
    mov ah, 4ch
    int 21h
end