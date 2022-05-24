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
       
	; ����� ��������� � ����� ����� �
	push NULL
	push offset numberOfChars
	push 9
	push offset inputA
	push outputHandle
	call WriteConsole
		 
        push NULL                         ;   ������  ���������� ������, ��� ���� �����
	push offset numberOfChars         ; ����������� ������ ������������ � ���������� 
	push 1000                         ; numberOfChars
	push offset stringA          
	push inputHandle
	call ReadConsole                 
	
       	mov EDX, offset stringA           ; ���������� ������ ����������� ������
       	mov EAX, numberOfChars            ; ���������� ����� ����������� ������
       	mov byte ptr [ EDX + EAX - 2], 0  ; ������ ������������ 0 � ����� ������, ��� ���� ��������� 2 �� ������ ���������� ��� 
					  ; ������������ �������� � ������ 13 � 10 � ����� ������, ���������� � ����� ����� ������� Enter
       	push offset stringA
	call atodw                        ;  ����������� ������ � ���������� ������� ��������, ���������� ������
	mov first, EAX                    ; ������ ������������ ����� � 10-������ ��, � 32-������ ����� �����
	
	; ����� ��������� � ����� ����� B
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
       	
      	mov EDX, offset stringB           ; ���������� ������ ����������� ������
       	mov EAX, numberOfChars            ; ���������� ����� ����������� ������
       	mov byte ptr [ EDX + EAX - 2], 0  ; ������ ������������ 0 � ����� ������, ��� ���� ��������� 2 �� ������ ���������� ��� 
					  ; ������������ �������� � ������ 13 � 10 � ����� ������, ���������� � ����� ����� ������� Enter	                   
	
	push offset stringB
	call atodw     	                  ;  ����������� ������ � ���������� ������� ��������, ���������� ������
	mov second, EAX                   ; ������ ������������ ����� � 10-������ ��, � 32-������ ����� ����� 
	           
	
	push NULL
	push offset numberOfChars
	push 18
	push offset input_string
	push outputHandle
	call WriteConsole     
	
;########################## (a + b) ##########################  

  	mov EAX, first
        add EAX, second	
 	
 	mov addition, EAX 			   ; �������� �� �������� EAX � ���������� a   
	                
;######################### (a + b)/2 ######################### 

	mov EAX, addition
	div denuminator                     ; div - �������

	mov  divide, EAX
 	
;############################ 3*a #############################     

	mov EAX, 3
	mul first                           ; mul - ������������

	mov  multiply, EAX
	
;###################### 3*a - (a + b)/2: ####################### 

	mov EAX, multiply
       	mov EBX, divide
       	
        sub EAX, EBX   			   ; sub - ��������
	
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