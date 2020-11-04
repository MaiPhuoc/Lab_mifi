.model small
.stack 100h
.data 
a dw 4
b dw 15
c dw 86
d dw 155
e dw 8 
.code
_start:
  mov ax,@data
  mov ds,ax

  xor dx,dx 
  mov ax,c
  shl ax,1  ; ax = 2*c

  mov bx,d
  sub ax,bx ; ax = 2*c - d
  mul ax    ; ax = (2*c - d)^2  
  mul b     ; ax = b*(2*c - d)^2
  mov cx,ax

  xor dx,dx
  mov ax,e  
  mov bx,3
  mul bx    ; ax = 3*e
  mov bx,ax

  mov ax,a    
  mul ax    ; ax = a^2   
  add ax,cx ; cx = a^2 + b*(2*c - d)^2

  div bx    ; ax = (a^2 + b*(2*c - d)^2)/3e

  mov ax,4c00h
  int 21h
end _start 
