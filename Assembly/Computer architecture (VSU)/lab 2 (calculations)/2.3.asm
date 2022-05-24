.486
.model flat, stdcall
option casemap : none
include windows.inc
include kernel32.inc   
include masm32.inc
includelib masm32.lib
includelib kernel32.lib

.data   
      enterA db "Enter a: "
      enterB db "Enter b: "
      enterC db "Enter c: "
      
      stringA db 100 dup (" ")
      stringB db 100 dup (" ")
      stringC db 100 dup (" ")
      myNumber dq 0 
      inputBufer db 0
      perehod db 0ah
      
.data?
      numberOfChars dd ?
      inputHandle dd ?
      outputHandle dd ? 
      myNumberA dd ?
      myNumberB dd ?
      myNumberC dd ?
      
      resultA dq ?
      resultFirstAdd dq ?
      res dq ?
      result dd ?
.code
entryPoint:

      push STD_OUTPUT_HANDLE
      call GetStdHandle
      mov outputHandle, EAX
	   
	
      push STD_INPUT_HANDLE
      call GetStdHandle
      mov inputHandle, EAX  
	
     
      ; Вывод сообщения
      push NULL
      push offset numberOfChars
      push 9
      push offset enterA
      push outputHandle
      call WriteConsole 
		
      ; Ввод числа
      push NULL
      push offset numberOfChars
      push 100
      push offset stringA
      push inputHandle
      call ReadConsole   
	
      ; Добавление в конец завершающего 0
      mov EDX, offset stringA
      mov EAX, numberOfChars
      mov byte ptr [ EDX + EAX -2 ], 0  
	
      ; Преобразование строки в число
      push offset stringA
      call atodw
      mov myNumberA, EAX
	
      ; Вывод сообщения
      push NULL
      push offset numberOfChars
      push 9
      push offset enterB
      push outputHandle
      call WriteConsole 
		
      ; Ввод числа
      push NULL
      push offset numberOfChars
      push 100
      push offset stringB
      push inputHandle
      call ReadConsole      
	
      ; Добавление в конец 0
      mov EDX, offset stringB
      mov EAX, numberOfChars
      mov byte ptr [ EDX + EAX -2 ], 0
	
      ; Преобразование строки в число
      push offset stringB
      call atodw
      mov myNumberB, EAX 
	
      ; Вывод сообщения
      push NULL
      push offset numberOfChars
      push 9
      push offset enterC
      push outputHandle
      call WriteConsole 
		
      ; Ввод числа
      push NULL
      push offset numberOfChars
      push 100
      push offset stringC
      push inputHandle
      call ReadConsole    
	
      ; Добавление в конец 0
      mov EDX, offset stringC
      mov EAX, numberOfChars
      mov byte ptr [ EDX + EAX -2 ], 0
	
      ; Преобразование строки в число
      push offset stringC
      call atodw
      mov myNumberC, EAX
	
      ; b делим на 32
      mov EAX, myNumberB
      mov EBX, 32
      div EBX       
      mov myNumberB, EAX  
			
      ; Возведение a в 7 степень
      mov EAX, myNumberA         
	
;######################### a^a #########################     

      mov dword ptr myNumber, EAX 		; myNumber = EDX:EAX
      mov dword ptr myNumber[4], EDX 
	  
      mul EAX 					; EAX = EAX * EAX  
         				
      mov dword ptr resultA, EAX 		; resultA = EDX:EAX                  
      mov dword ptr resultA[4], EDX
	
;######################### a^3 #########################
 
      mov dword ptr myNumber, EAX 		; myNumber = EDX:EAX
      mov dword ptr myNumber[4], EDX   
	
      mul myNumberA				; EAX = EAX * myNumberA
	
      mov dword ptr resultA, EAX 		; resultA = EDX:EAX                  
      mov dword ptr resultA[4], EDX 
	
;######################### a^6 ######################### 

      mov dword ptr myNumber, EAX 		; myNumber = EDX:EAX
      mov dword ptr myNumber[4], EDX  
	 
      mul EAX; EAX = EAX * EAX    
	
      mov dword ptr resultA, EAX 		; resultA = EDX:EAX                  
      mov dword ptr resultA[4], EDX 
	
;######################### a^7 ######################### 

      mov dword ptr myNumber, EAX 		; myNumber = EDX:EAX
      mov dword ptr myNumber[4], EDX  
	
      mul myNumberA	     
					 	; EAX = EAX*myNumberA
      mov dword ptr resultA, EAX 		; resultA = EDX:EAX                  
      mov dword ptr resultA[4], EDX 
	
;######################### (a^7 + b/32) #########################

      mov EBX, dword ptr myNumberB 	       	
      add EAX, EBX
      jnc notLabel
      adc EDX, 0 
        
notLabel:       

;######################### (a^7 + b/32)/c and (a^7 + b/32)%c #########################         
	
      div myNumberC
      add EAX, EDX  	 
      push offset result
      push EAX
      call dwtoa  				; Перевод слова в целое беззнаковое число
	
      push offset result
      call lstrlen
	
      push NULL
      push offset numberOfChars
      push EAX
      push offset result
      push outputHandle
      call WriteConsole 
	  	
      push NULL
      push offset numberOfChars
      push 1
      push offset inputBufer
      push inputHandle
      call ReadConsole 
 
;######################### END PROCESS ######################### 
   
end entryPoint
