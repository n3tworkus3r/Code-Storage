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
	input_string db 10 dup ("3*a - (a + b)/2 =  "), 0
	denuminator db 2  
	ent db 10

.data?  

	addition dd ?
 	divide dd ? 
 	multiply dd ?
 	final dd ?
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
	           
	
	push NULL
	push offset numberOfChars
	push 18
	push offset input_string
	push outputHandle
	call WriteConsole     
	
;########################## (a + b) ##########################  

  	mov EAX, first
        add EAX, second	
 	
 	mov addition, EAX 			   ; Копируем из регистра EAX в переменную a   
	                
;######################### (a + b)/2 ######################### 

	mov EAX, addition
	div denuminator                     ; div - частное

	mov  divide, EAX
 	
;############################ 3*a #############################     

	mov EAX, 3
	mul first                           ; mul - произведение

	mov  multiply, EAX
	
;###################### 3*a - (a + b)/2: ####################### 

	mov EAX, multiply
       	mov EBX, divide
       	
        sub EAX, EBX   			   ; sub - разность
	
	push offset final
	push EAX
	call dwtoa

	push offset final
	call lstrlen
	
	push NULL
 	push offset numberOfChars
 	push EAX
 	push offset final
 	push outputHandle
 	call WriteConsole  
 	
;######################### END PROCESS #########################
        
	push 3000h
	call Sleep
	
	push 0
	call ExitProcess

end entryPoint 	