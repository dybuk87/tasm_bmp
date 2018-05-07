.model tiny  ;model pamieci
.386c        ;wymuszenie rejestrow 32 bitowych
.code        ;poczatek segmentu kodu
 org 100h    ;pominiecie 100h bajtow -> potrzebne dla programu typu *.com
 start:    
  call rezerwuj_pamiec  ;rezerwacja pamieci na program 
  mov ax,0013h          
  int 10h               ;ustawienie grafiki 320x200 w 256 kolorack
  mov ax,cs           
  mov ds,ax             ;dane sa w czesci programu
  lea dx,nazwa          ;adres efektywny nazwy pliku bmp do dx
  call LoadBmp          ;wywolaj procedure wczytujaca bmp
  mov [BMP.handle],ax   ;uchwyt pamieci z wczytanego bmp zapisz do bitmapy
  mov [bmp.IResX],ebx   ;to samo z rozdzielczoscia pozioma
  mov [bmp.IResY],ecx   ;i z rozdzielczoscia pionowa
  mov [bmp.ImgSize],edx ;caly rozmiar bmp (roz. pozioma * roz. pionowa)
 
    lea si,bmp          ;si= adres efektywny poczatku bitmapy
    mov di,9d           ;di= 9
    mov ax,9d           ;ax= 9
    mov cx,309d         ;cx= 309
    mov bl,100d         ;bl= 0
    call vline          ;rysuj linie pozioma

    mov di,9d
    mov ax,189d
    mov cx,309d
    mov bl,100d
    call vline          ;j.w

    mov di,9d
    mov ax,9d
    mov cx,189d
    mov bl,100d
    call hline          ;rysuj linie pionowa

    mov di,309d
    mov ax,9d
    mov cx,189d
    mov bl,100d
    call hline          ;j.w 

    mov di,10d
    mov ax,10d
    mov dx,30d
    mov cx,18d
    mov bl,120d
    call rect           ;rysuj prostokat wypelniony

    lea si,bmp          ;do si adres efektywny bmp(zrodla)
    lea di,ekran        ;j.w ale ekranu(celu)
    call blit           ;kopiuj
    mov es,[bmp.handle] ;do es, uchwyt bmp
    call freemem        ;zwolnij pamiec zajeta przez bmp
  pop es                ;do es wartosc ze stosu   stos: 

  mov ah,0
  int 16h               ;czekaj na nacisniencie klawisza
  mov ax,0003h          
  int 10h               ;ustaw tryb tekstowy
   MOV   DX, OFFSET koniec    
   MOV   AH, 09H
   INT   21H
  mov ah,0
  int 16h               ;czekaj na nacisniencie klawisza
  mov ah,4ch            ;
  int 21h               ;wyloncz program
nazwa DB "logo.bmp",0
CR        EQU 13
LF        EQU 10
koniec DB CR,LF, "  That was: "
       DB CR,LF       
       DB CR,LF, "       Graphic unit all in assembler"
       DB CR,LF, "       IT can do: "
       DB CR,LF, "        > Draw points"
       DB CR,LF, "        > draw veritical line and horizontal line "
       DB CR,LF, "        > Draw rectangles"
       DB CR,LF, "        > Read bmp(procedure allocate mem then read bmp and return handle)"
       DB CR,LF, "        > have struc BITMAP in it handle to mem, resX,resY and Size of all"
       DB CR,LF, "        > copy Bitmaps using procedure blit$"

include VGA.inc 
BMP BITMAP <?>
end start
