LoadBmp proc  ;ds:dx = adres nazwy  
              ;wy: ax <- uchwyt pamieci ebx<-ResX; ecx<-ResY edx<-size of img
  mov al,02d     ; al<-02h
  call OpenFile  ;Otwoz plik
  mov handlef,ax  ;zapisz uchwyt pliku 

  mov bx,ax      ;uchwyt do bx
  mov cx,54d     ;do cx rozmiar naglowka
  lea dx, head   ;naglowek
  call ReadFile  ;wczytaj naglowek
 
  mov cx,1024d   ;do cx rozmiar palety
  lea dx, pal    ;paleta
  call ReadFile  ;wczytaj palete
  
  lea di, pal    ;paleta
  call setPal    ;ustaw palete

  mov eax,[head.ResX]
  mov ebx,[Head.ResY]
  mul ebx
  mov edx,eax
  push edx
  mov ebx,eax
  sub ebx,[head.resX]
  xor edi,edi
  mov di,bx
  shr eax,4
  mov bx,ax     ;do bx ilosc paragrafow
  inc bx
  call allocate    ;przydziel pamiec
  push ax
 
  mov ebx,[head.ResX]
  shr ebx,4
  inc bx
  call allocate
  mov bufor,ax

  pop ax
  push es
   mov es,ax       ;es<->nowy blok 
   mov ecx,[head.ResY]
   mov eax,[head.resX]
  pbmp:
   push cx
   mov bx,handlef
   mov ecx,eax
   push ds 
    mov ds,bufor
    xor dx,dx
   call ReadFile    ;ds:dx -> wyjscie danych
     push di
      mov ecx,eax
      mov si,dx
      rep movsb
     pop di
   push eax
   push bx
   push dx
    mov bx,4
    div bx
    cmp dx,0
    je omindop
     mov cx,1
     sub cx,dx
     xor dx,dx
     call ReadFile
    omindop:
   pop dx
   pop bx
   pop eax
   pop ds 
      sub edi,eax
   pop cx
   dec cx
  cmp cx,0
  jne pbmp
  push es
  mov es,bufor
  call freemem
  pop es
  mov ax,es
  pop  es
  mov ebx,[head.ResX]
  mov ecx,[Head.ResY]
  pop edx
 ret 
endp

blit proc ;ds:si=surce  di=dest bitmap
 push es
  mov ecx,ds:[si+6]
  mov ebx,ds:[si+2]
  mov edx,ds:[di+2]
  mov ax,ds:[di]
  mov es,ax
  xor edi,edi
  mov ax,ds:[si]
  xor si,si
  push ds
  mov ds,ax 
 ph:
  push ecx 
   mov ecx,ebx
   push di
      rep movsb ;(ds:si->es:di)  
   pop di
   add edi,edx
  pop ecx
 loop ph
  pop ds 
 pop es  
 ret
endp 

nagl  struc             ;naglowek pliku bmp = 54 bajty
  Imgtype  DW ?
  FileSize DD ?
  res1     DW ?  ;=0
  res2     DW ?  ;=0
  offbit   DD ?
  SizeNinf DD ?
  ResX     DD ?
  ResY     DD ?
  NRPlanes DW ?  ;=1
  bpp      DW ?
compresion DD ?
  ISize    DD ?
  DpiX     DD ?
  DPiY     DD ?
  ColUse   DD ?
  NrCol    DD ?
 ends

BITMAP struc
  handle DW ?
  IResX   DD 0
  IResY   DD 0
  ImgSize DD 0
 ends

head    nagl <?>
bufor   DW    ?
pal     DB 1024 dup(?)
handlef DW    ?
ekran   BITMAP <0a000h,320d,200d,64000d>