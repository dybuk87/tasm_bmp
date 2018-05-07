allocate proc   ;we: bx=paragraf

     ;±± rezerwacja miejsca w pamieci
	mov ah,48h
	int 21h		
  jnc oook
   mov ah,09h
   mov dx,offset oom_string
   int 21h
   mov ah,4ch
   int 21h
  oook:
 ret
endp

freemem proc    ;we: es:-segm        
	push ax
	mov ah,49h
	int 21h		
	pop ax
 ret
endp

rezerwuj_pamiec PROC
	pusha

	mov ah,4Ah
	; es jest zaadowane odpowiednio juz na poczatku
	mov bx,512*1024/16	; rezerwacja 512KB na program
	int 21h	
        jnc okkk
         mov ah,09h
         mov dx,offset oom_string
         int 21h
         mov ah,4ch
         int 21h          
        okkk:
	popa
ret
endp

oom_string DB "Za malo pamieci$"