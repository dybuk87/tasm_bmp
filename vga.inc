SetPal proc  ;ds:di= offset pal
 push cx
 push dx
 push ax
 mov cx,256d
 mov dx,03c8h
 mov al,0
 out dx,al
 mov dx,03c9h
 pet:
  mov al,ds:[di+2]
  shr al,2
  out dx,al 

  mov al,ds:[di+1]
  shr al,2
  out dx,al 

  mov al,ds:[di+0]
  shr al,2
  out dx,al 

  add di,4
 loop pet
 pop ax
 pop dx
 pop cx
 ret
endp

plot proc ; ds:si= adres  bitmapy   di=x ax=y bl=c
 push es
 push ecx
  mov ecx,ds:[si+2]
  mul cx
  add di,ax
  mov ax,ds:[si]
  mov es,ax
  mov es:[di],bl
 pop ecx
 pop es
 ret
endp 

vline proc ;ds:si = adres bitmapy di=x cx=x2 ax=y bl=c 
 push es
 push edx
  mov edx,ds:[si+2]
  mul dx
  sub cx,di
  inc cx
  add di,ax
 mov ax,ds:[si]
 mov es,ax
 mov al,bl
 rep stosb
 pop edx
 pop es
 ret
endp

hline proc ;ds:si = adres bitmapy di=x cx=y2 ax=y bl=c 
 push es
 push edx
  sub cx,ax
  inc cx
  mov edx,ds:[si+2]
  mul dx
  add di,ax
 mov ax,ds:[si]
 mov es,ax
 mov edx,ds:[si+2]
 pehline:
  mov es:[di],bl
  add di,dx
 loop peHline
 pop edx
 pop es
 ret
endp

rect proc ;ds:si = adres bitmapy; di=x ax=y dx=w cx=h bl=c
 push es
 push edx
  mov edx,ds:[si+2]
  mul dx         
 pop edx
 add di,ax     
  mov ax,ds:[si]
  mov es,ax
 mov al,bl
  mov ebx,ds:[si+2]
 pwys:
  push cx
   mov cx,dx
   push di
    rep stosb
   pop di
   add edi,ebx
  pop cx
 loop pwys
 pop es
 ret
endp

include file.inc
include mem.inc
include bitmaps.inc