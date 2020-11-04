   
   data segment
cnt db 0	;���������� ����
tmplen1 db 0	;����� ����� 1
tmplen2 db 0 ;����� ����� 2
cmp_str1 db 255 dup(?)	;������ ��� ��������� 1
cmp_str2 db 255 dup(?)	;������ ��� ��������� 2
str_arr db 1000 dup(?) ;��� ������ ����
indx_arr db 1000 dup(?)	;������ �������� ���� � �� ����
mlen db 064h	;������������ ������ �����
alen db ?	;����������� �����
strng db 255 dup(?)	
ln db 13,10,'$' 
flag db 0	;���� ����������� ���� ����
tmp dw ?	;��������� ���������� ��� ������
end_of_indx_arr dw ?	;�������� ����� ������� indx_arr
data ends
code segment
assume cs:code,ds:data
;---------��������� ��������� ���� ����--------
compare proc far
CLD	;��������� ����� �� �����
xor cx,cx
mov cl,tmplen1	;���� ����� ����� 1 
cmp cl,tmplen2	;������ ����� ����� 2
ja CmpLbl1
CmpLbl2:lea di,cmp_str1	
lea si,cmp_str2
repe cmpsb	;���������� cmp_str1 � cmp_str2
jae ext_cmp	;���� ����� ����� � ������ ������ ������ �� ���� �� ���������� 
mov flag,1	;����� ������ ����
ext_cmp:ret	
CmpLbl1:mov cl,tmplen2	;�� � cx ��������� �������	
jmp CmpLbl2	
compare endp
;-------��������� ������ ���� � ������-----------
read proc far
lea bx,indx_arr
strt:mov ah,0Ah	
lea dx,mlen
int 21h	;��������� �����
mov ah,09h	
lea dx,ln
int 21h	;������� ������ ������ � �������� �����
mov cl,alen
jcxz ext	;������ ������?���� ��,�� ���� �� ext	
lea si,strng	;� si ����� �������� ���������� �����	
inc di	
mov byte ptr [bx],cl	;� indx_arr �������� ����� �����
mov word ptr [bx+1],di ;���� �� ����� �������� �� ���� �����
add bx,3	;��������� � indx_arr �� ��� ����� ������
rep movsb	;�������� ��������� ������ �� string � ������ str_arr	
mov byte ptr[di],'$' ;��� ����������� ������ ����� 09h ��������� ��������� �� ������ ������ ���� '$'
add cnt,1	;����������� ������� ����
jmp strt ;������ ����� �����
ext:
xor di,di	
mov end_of_indx_arr	,bx	;���������� �������� ���������� �������� � indx_arr
sub end_of_indx_arr,3
ret
read endp
;-----------��������� ���������� �������-------------------
sort proc far
xor cx,cx
lea di,cmp_str1	
mov si,[bx+1]	;� si �������� �� ������ 1.
mov word ptr ax,[bx+1]	;� �� �������� ������ 1
mov byte ptr cl,[bx]	;� cl ����� ������ 1
mov tmplen1,cl	;� ���� ����� ������ 1
rep movsb	;�������� ����� �� ������� � cmp_str1
add bl,3	;��������� �� ��������� �����
lea di,cmp_str2;	
mov si,[bx+1]	;� si �������� �� ������ 2.
push ax	;��������� �������� ������ 1
mov ax,word ptr [bx+1]	;���������� � ax �������� ������ 2
mov tmp,ax	;���������� � tmp �������� ������ 2
pop ax	;���������� �������� ������ 1
mov byte ptr cl,[bx]	;� cl ����� ������ ������
mov tmplen2,cl	;� tmplen2 ����� ������ ������
rep movsb	;�������� ��������� ����� �� ������� � cmp_str2	
call compare	;��������� ���������
cmp flag,1	;���� �����������
je SrtLbl1	;���� 1 �� ������ �������� �������
ext_srt:	;�����
mov flag,0	;�������� ���� �� ���������� ���������
ret
SrtLbl1:
push ax	;��������� �������� ������ 1
xor ax,ax
mov al,tmplen1	;� al ����� ������ 1
mov [bx],al	;�� ������ ����� ����� ������ 1 
pop ax	;���������� �������� ������ 1
mov word ptr [bx+1],ax	;������� �������� ������ 1 �� ����� �������� ������ 2
sub bx,3	;�������� bx �� ��� ����� ������� � ������ ������ ������
xor ax,ax
mov al,tmplen2	;� al ����� ������ ������
mov [bx],al	;������������ ����� ������ ������ � ����� ������
mov ax,tmp	;� ax �������� ������ ������
mov word ptr [bx+1],ax	;������� �������� ������ 2 �� ����� ������ 1
add bx,3	;���������� �������� ������� indx_arr �������
jmp ext_srt
sort endp
;-----------main-------------------
main:mov ax,data
mov ds,ax
mov es,ax
xor bx,bx
lea di,str_arr	;� di �������� ������� ����
call read	;������ ���� � ������
mov cl,cnt	;� cl ���-�� ���� � �������
cycle2:
push cx	
lea bx,indx_arr	;� bx �������� �� ������ �������� ���� � ����
mov cx,end_of_indx_arr	;� cx ����� ���������� ��-�� indx_arr
cycle1:cmp cx,bx	;���� �������� �������� ��-�� indx_arr=���������� � indx_arr	
je Main_loop_lbl	;�� �������� ���� ������ � ������� ��-��
push cx	;���� �� �����
call sort	;�� �������� ����������
pop cx
jmp cycle1
Main_loop_lbl:
pop cx
loop cycle2	;�������� ����� ���������� n*(n-1) ���, ��� n-���-�� ��-���
main_ext:
xor ax,ax
xor cx,cx
mov cl,cnt
lea bx,indx_arr
;-------����� �� �����------------------
cycle3:
mov ah,09h
push cx
mov word ptr dx,[bx+1]
int 21h	;����� �����
mov ah,09h
lea dx,ln	;����� 0Dh,0Ah
int 21h
add bx,3	;������� �� ��������� �����
pop cx
loop cycle3	;�� ��� ��� ���� ����� �� ��������(cx=0)
mov ax,4c00h
int 21h
code ends
end main