   
   data segment
cnt db 0	;количество слов
tmplen1 db 0	;длина слова 1
tmplen2 db 0 ;длина слова 2
cmp_str1 db 255 dup(?)	;строка для сравнения 1
cmp_str2 db 255 dup(?)	;строка для сравнения 2
str_arr db 1000 dup(?) ;наш массив слов
indx_arr db 1000 dup(?)	;массив смещений слов и их длин
mlen db 064h	;максимальная длинна слова
alen db ?	;фактическая длина
strng db 255 dup(?)	
ln db 13,10,'$' 
flag db 0	;флаг неравенства двух слов
tmp dw ?	;временная переменная для мусора
end_of_indx_arr dw ?	;смещение конца массива indx_arr
data ends
code segment
assume cs:code,ds:data
;---------процедура сравнения двух слов--------
compare proc far
CLD	;сравнение слева на право
xor cx,cx
mov cl,tmplen1	;если длина слова 1 
cmp cl,tmplen2	;больше длины слова 2
ja CmpLbl1
CmpLbl2:lea di,cmp_str1	
lea si,cmp_str2
repe cmpsb	;сравниваем cmp_str1 и cmp_str2
jae ext_cmp	;если длины равны и вторая больше первой то флаг не изменяется 
mov flag,1	;иначе меняем флаг
ext_cmp:ret	
CmpLbl1:mov cl,tmplen2	;то в cx заносится меньшая	
jmp CmpLbl2	
compare endp
;-------процедура чтения слов в массив-----------
read proc far
lea bx,indx_arr
strt:mov ah,0Ah	
lea dx,mlen
int 21h	;считываем слово
mov ah,09h	
lea dx,ln
int 21h	;символы начала строки и смещения влево
mov cl,alen
jcxz ext	;пустая строка?если да,то идем на ext	
lea si,strng	;в si адрес смещения введенного слова	
inc di	
mov byte ptr [bx],cl	;в indx_arr помещаем длину слова
mov word ptr [bx+1],di ;туда же адрес смещения на само слово
add bx,3	;переходим в indx_arr на три байта вперед
rep movsb	;копируем введенную строку из string в массив str_arr	
mov byte ptr[di],'$' ;для дальнейшего вывода через 09h заполняем следующий за каждым словом байт '$'
add cnt,1	;увеличиваем счетчик слов
jmp strt ;читаем новое слово
ext:
xor di,di	
mov end_of_indx_arr	,bx	;запоминаем смещение последнего элемента в indx_arr
sub end_of_indx_arr,3
ret
read endp
;-----------процедура сортировки массива-------------------
sort proc far
xor cx,cx
lea di,cmp_str1	
mov si,[bx+1]	;в si смещение на строку 1.
mov word ptr ax,[bx+1]	;в ах смещение строки 1
mov byte ptr cl,[bx]	;в cl длина строки 1
mov tmplen1,cl	;в темп длина строки 1
rep movsb	;копируем слово из массива в cmp_str1
add bl,3	;переходим на следующее слово
lea di,cmp_str2;	
mov si,[bx+1]	;в si смещение на строку 2.
push ax	;сохраняем смещение строки 1
mov ax,word ptr [bx+1]	;записываем в ax смещение строки 2
mov tmp,ax	;записываем в tmp смещение строки 2
pop ax	;возвращаем смещение строки 1
mov byte ptr cl,[bx]	;в cl длина второй строки
mov tmplen2,cl	;в tmplen2 длина второй строки
rep movsb	;копируем следующее слово из массива в cmp_str2	
call compare	;процедура сравнения
cmp flag,1	;флаг неравенства
je SrtLbl1	;если 1 то меняем смещения местами
ext_srt:	;выход
mov flag,0	;обнуляем флаг до следующего сравнения
ret
SrtLbl1:
push ax	;сохраняем смещение строки 1
xor ax,ax
mov al,tmplen1	;в al длина строки 1
mov [bx],al	;во второе слово длина строки 1 
pop ax	;возвращаем смещение строки 1
mov word ptr [bx+1],ax	;заносим смещение строки 1 за место смещения строки 2
sub bx,3	;сдвигаем bx на три байта обратно к адресу первой строки
xor ax,ax
mov al,tmplen2	;в al длина второй строки
mov [bx],al	;записывается длина второй строки в длину первой
mov ax,tmp	;в ax смещение второй строки
mov word ptr [bx+1],ax	;заносим смещение строки 2 на место строки 1
add bx,3	;возвращаем смещение массива indx_arr обратно
jmp ext_srt
sort endp
;-----------main-------------------
main:mov ax,data
mov ds,ax
mov es,ax
xor bx,bx
lea di,str_arr	;в di смещение массива слов
call read	;чтение слов в массив
mov cl,cnt	;в cl кол-во слов в массиве
cycle2:
push cx	
lea bx,indx_arr	;в bx смещение на массив смещений слов и длин
mov cx,end_of_indx_arr	;в cx адрес последнего эл-та indx_arr
cycle1:cmp cx,bx	;если смещение текущего эл-та indx_arr=последнему в indx_arr	
je Main_loop_lbl	;то начинаем цикл заново с первого эл-та
push cx	;если не равно
call sort	;то вызываем сортировку
pop cx
jmp cycle1
Main_loop_lbl:
pop cx
loop cycle2	;пвторяем вызов сортировки n*(n-1) раз, где n-кол-во эл-тов
main_ext:
xor ax,ax
xor cx,cx
mov cl,cnt
lea bx,indx_arr
;-------вывод на экран------------------
cycle3:
mov ah,09h
push cx
mov word ptr dx,[bx+1]
int 21h	;вывод слова
mov ah,09h
lea dx,ln	;вывод 0Dh,0Ah
int 21h
add bx,3	;переход на следующее слово
pop cx
loop cycle3	;до тех пор пока слова не кончатся(cx=0)
mov ax,4c00h
int 21h
code ends
end main