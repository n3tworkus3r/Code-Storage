.486
.model flat, stdcall
option casemap :none 
include windows.inc
include kernel32.inc
includelib kernel32.lib 
include masm32.inc
includelib masm32.lib

.data
	inputA db "Input a: ", 0     
	inputB db "Input b: ", 0  
	stringA db 100 dup (" ")
	stringB db 100  dup (" ")   
	ent db 10

.data?  
	number dd ?
 	first dd ?
 	second dd ?
	inputHandle dd ?    
	outputHandle dd ?
	numberOfChars dd ?

.code
entryPoint:
	
	push STD_INPUT_HANDLE     
	call GetStdHandle         
	mov inputHandle, EAX      
	
	push STD_OUTPUT_HANDLE
	call GetStdHandle
	mov outputHandle, EAX  
       
	; Вывод сообщения о вводе числа А
	push NULL
	push offset numberOfChars
	push 9
	push offset inputA
	push outputHandle
	call WriteConsole
		 
        push NULL                         ;   Чтение  клавиатуры строки, при этом длина
	push offset numberOfChars         ; прочитанной строки записывается в переменную 
	push 1000                         ; numberOfChars
	push offset stringA          
	push inputHandle
	call ReadConsole                 
	
       	mov EDX, offset stringA           ; Сохранение адреса прочитанной строки
       	mov EAX, numberOfChars            ; Сохранение длины прочитанной строки
       	mov byte ptr [ EDX + EAX - 2], 0  ; Запись завершающего 0 в конец строки, при этом вычитание 2 из адреса необходимо для 
					  ; Отбрасывания символов с кодами 13 и 10 в конце строки, помещаемых в буфер после нажатия Enter
       	push offset stringA
	call atodw                        ;  Преобразует строку с завешающим нулевым символом, содержащую запись
	mov first, EAX                    ; целого беззнакового числа в 10-тичной СС, в 32-битное целое число
	
	; Вывод сообщения о вводе числа B
	push NULL
	push offset numberOfChars
	push 9
	push offset inputB
	push outputHandle
	call WriteConsole
	
       	push NULL                 
	push offset numberOfChars 
	push 100                   
	push offset stringB
	push inputHandle         
	call ReadConsole   
       	
      	mov EDX, offset stringB           ; Сохранение адреса прочитанной строки
       	mov EAX, numberOfChars            ; Сохранение длины прочитанной строки
       	mov byte ptr [ EDX + EAX - 2], 0  ; Запись завершающего 0 в конец строки, при этом вычитание 2 из адреса необходимо для 
					  ; Отбрасывания символов с кодами 13 и 10 в конце строки, помещаемых в буфер после нажатия Enter	                   
	
	push offset stringB
	call atodw     	                  ;  Преобразует строку с завешающим нулевым символом, содержащую запись
	mov second, EAX                   ; целого беззнакового числа в 10-тичной СС, в 32-битное целое число    
	
;######################### SUM #########################     

	mov EAX, first
        add EAX, second	
        mov ECX, EAX  
        
      	
      	push offset number
      	push ECX
      	call dwtoa
      	
      	push offset number
      	call lstrlen
	
	push NULL                 
	push offset numberOfChars 
	push EAX
	push offset number
	push outputHandle         
	call WriteConsole
	   
	push NULL                 
	push offset numberOfChars 
	push 1
	push offset ent
	push outputHandle         
	call WriteConsole  
	
;######################### DIFFERENCE ######################### 

	mov EAX, first
	sub EAX, second
	mov ECX,EAX
	
	push offset number
	push ECX
	call dwtoa
	
	push offset number
	call lstrlen 
	
       	push NULL                 
	push offset numberOfChars 
	push EAX
	push offset number
	push outputHandle         
	call WriteConsole
	
	push NULL                 
	push offset numberOfChars 
	push 1
	push offset ent
	push outputHandle         
	call WriteConsole      
	
;######################### MULTIPLICATION #########################

	mov EAX, first
	mul second

	
	push offset number
	push EAX
	call dwtoa
	
	push offset number
	call lstrlen 
	
       	push NULL                 
	push offset numberOfChars 
	push EAX
	push offset number
	push outputHandle         
	call WriteConsole 

	push NULL                 
	push offset numberOfChars 
	push 1
	push offset ent
	push outputHandle         
	call WriteConsole 
 
	
;######################### DIVISION #########################    

	mov EAX, first
	mov EDX, 0
	div second
	
	push offset number
	push EAX
	call dwtoa
	
	push offset number
	call lstrlen 
	
       	push NULL                 
	push offset numberOfChars 
	push EAX
	push offset number
	push outputHandle         
	call WriteConsole
   	
;######################### END PROCESS #########################
        
	push 3000h
	call Sleep
	
	push 0
	call ExitProcess

end entryPoint