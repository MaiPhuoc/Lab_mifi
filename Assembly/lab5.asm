                TITLE LAB4
    .model  small
    .stack  1000h
    .data   
    str     db 80 dup(0)  ; string to check
    menu    db 'Welcome to my work!',13,10,'    MENU',13,10,'1.Read string.',13,10,'2.String after work.',13,10,'Please press 1 or 2.',13,10,'$'
    inp     db 'Input string:->',13,10,'$'  
    lenw    dw 0 
    leng    dw 0
    ew      db ' ;,'         ; signs to end the word
    crlf    db 13,10,'$'       ; carriage return and linefeed 
    msg     db 13,10,'Result:',13,10,'$'                
    .code
MAIN PROC
    mov ax,@data
    mov ds,ax 
    mov es,ax 
    
START:
    lea dx, menu
    mov ah,9
    int 21h
    
    mov ah,1
    int 21h
    
    cmp al,'1'
    je REA
    
    cmp al,'2'
    je WOR
    
REA:
    lea dx, inp
    mov ah,9
    int 21h 
      
    lea di, str
    call READ_STR 
    jmp START
     
WOR:
    lea dx, crlf
    mov ah,9
    int 21h
    
    lea si, str  ; print input string
    mov bx,leng
    call DISP_STR
           
    xor bx,bx 
    xor ax,ax
    lea si, str
    mov cx, leng    
len_word:  
    cmp byte ptr [si], ' '
    jz word
    cmp byte ptr [si], ';'
    jz word
    cmp byte ptr [si], ','
    jz word  
    cmp byte ptr [si], 0dh
    jz endd
    inc si
    inc bx
    loop len_word    ; save lenw, si tro toi cuoi tu, bx = leng word 

word:
    lea si, str
    mov si, lenw 
    call select      ; sort + swap    
    add lenw, bx
    inc lenw  
    dec cx
    mov si, lenw
    xor bx,bx   
    jmp len_word
     
endd:
    lea si, str
    mov si, lenw 
    call select
    ;last word 
    
    lea dx, msg  ; print result
    mov ah,9
    int 21h
    
    lea si, str  ; print output string
    mov bx,leng
    call DISP_STR
          
    mov ax,4c00h
    int 21h
MAIN ENDP
;********************SELECT********************
 SELECT PROC       ; input SI = offset str, bx = leng, output: SI = offset arrange string
        push bx
        push cx
        push dx
        push si
            dec bx ; N = N - 1
            je END_SORT
            mov dx,si
    SORT_LOOP: 
            mov si,dx
            mov cx,bx
            mov di,si
            mov al,[di]
    FIND_BIG:
            inc si
            cmp [si],al
            jng NEXT
            mov di,si
            mov al,[di]
    NEXT:
            loop FIND_BIG
            call SWAP
            dec bx
            jne SORT_LOOP
    END_SORT:
        pop si
        pop dx
        pop cx
        pop bx
           ret
 SELECT ENDP 
;*******************SWAP*******************
 SWAP PROC
           push ax
            mov al,[si]
            xchg al,[di]
            mov [si],al
           pop ax
           ret
 SWAP ENDP
;****************READ_STR******************
 READ_STR PROC  NEAR    ; input: DI = offset of string; BX: leng of string
    push ax
    push di
    cld
    xor bx,bx
    mov ah,1
    int 21h
  WHILE1:
    cmp al, 0dh; CR?
    je END_WHILE1 ; if right
    cmp al,8h ; backspace?
    jne ELSE1   ; if not, save char
    dec di
    dec bx
    jmp read
  ELSE1:
    stosb
    inc bx
  READ:
    int 21h
    jmp WHILE1
  END_WHILE1:
    stosb 
    inc bx
    mov leng,bx
    pop di
    pop ax
    ret
 READ_STR ENDP 
;*************DISP_STR*******************
DISP_STR PROC NEAR   ; input: SI = offset of string; BX: leng of string 
   push ax
   push bx
   push cx
   push dx
   push si
    mov cx,bx   ;initial count
    jcxz P_EXIT ; end if cx=0
    cld
    mov ah,2
 TOP:
    lodsb
    mov dl,al
    int 21h
    loop top
 P_EXIT:
   pop si
   pop dx
   pop cx
   pop bx
   pop ax
   ret
DISP_STR ENDP
      
  END MAIN      