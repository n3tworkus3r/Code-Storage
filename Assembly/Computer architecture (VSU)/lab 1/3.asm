.486   ; Enables assemblyof nonpriviliged instructions for the 80486 processor
.model flat, stdcall ; Memory model and call programs
option casemap :none
include windows.inc
include kernel32.inc
includelib kernel32.lib

.data

firstLine db 020h,020h,020h,020h ; " "
return_line db 10,13 ; "\n\r"
second_line db 0DAh,0C4h,0C4h,0C4h,0C4h,0C4h,0C4h,0C4h,0C4h,0C4h,0C4h,0C4h,0C4h,0BFh,10,13 
third_line db 0B3h,0B0h,0B0h,0B0h,0B0h,0B0h,0B0h,0B0h,0B0h,0B0h,0B0h,0B0h,0B0h,0B3h,10,13
opening_line db 0B3h,0B0h
closing_line db 0B0h,0B3h,10,13
fourth_line db 0B3h,0B0h,0B0h,0B0h,0C9h,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CFh,0CDh,0CDh,0CDh,0BBh,10,13 
second_opening_line db 020h,020h,020h,020h,0BAh,0B1h
second_closing_line db 0B1h,0BAh,10,13
fifth_line db 0C0h,0C4h,0C4h,0C4h,0B6h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0BAh,10,13 
sixth_line db 020h,020h,020h,020h,0BAh,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0B1h,0BAh,10,13 
seventh_line db 020h,020h,020h,020h,0C8h,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0CDh,0BCh,10,13
firstStr db 100 dup (" ")
secondStr db 100 dup (" ")
thirdStr db 100 dup (" ")


.data?
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

; Reading a string from the console
push NULL
push offset numberOfChars
push 1000
push offset firstStr
push inputHandle
call ReadConsole

; Limit of entering up to 10 characters
mov EBX, offset firstStr
mov EAX, numberOfChars
mov byte ptr [ EBX + EAX - 1 ], " "
mov byte ptr [ EBX + EAX - 2 ], " "

; Reading second string from the console
push NULL
push offset numberOfChars
push 1000
push offset secondStr
push inputHandle
call ReadConsole

; Limit on entering up to 10 characters
mov EBX, offset secondStr
mov EAX, numberOfChars
mov byte ptr [ EBX + EAX - 1 ], " "
mov byte ptr [ EBX + EAX - 2 ], " "

; Reading third string from the console
push NULL
push offset numberOfChars
push 1000
push offset thirdStr
push inputHandle
call ReadConsole

; Limit on entering up to 10 characters
mov EBX, offset thirdStr
mov EAX, numberOfChars
mov byte ptr [ EBX + EAX - 1 ], " "
mov byte ptr [ EBX + EAX - 2 ], " "


; ##################OUTPUT##################

; Entering 1-st line in the console
push NULL
push offset numberOfChars
push 4
push offset firstLine
push outputHandle
call WriteConsole
                         
; !!! Entering 1-st string in the console
push NULL
push offset numberOfChars
push 10
push offset firstStr;##########################
push outputHandle
call WriteConsole

; Entering return-line in the console
push NULL
push offset numberOfChars
push 2
push offset return_line
push outputHandle
call WriteConsole

; Entering 2-nd line in the console
push NULL
push offset numberOfChars
push 16
push offset second_line
push outputHandle
call WriteConsole

; Entering 3-rd line in the console
push NULL
push offset numberOfChars
push 16
push offset third_line
push outputHandle
call WriteConsole  

; Entering opening-line in the console
push NULL
push offset numberOfChars
push 2
push offset opening_line
push outputHandle
call WriteConsole 


; !!! Entering 2-nd string in the console
push NULL
push offset numberOfChars
push 10
push offset secondStr;##########################
push outputHandle
call WriteConsole 

; Entering ending-line in the console
push NULL
push offset numberOfChars
push 4
push offset closing_line
push outputHandle
call WriteConsole 
 

; Entering 4-th line in the console
push NULL
push offset numberOfChars
push 20
push offset fourth_line
push outputHandle
call WriteConsole  


; Entering 5-th line in the console
push NULL
push offset numberOfChars
push 20
push offset fifth_line
push outputHandle
call WriteConsole

; Entering second-opening-line in the console
push NULL
push offset numberOfChars
push 6
push offset second_opening_line
push outputHandle
call WriteConsole   

; !!! Entering 3-rd string in the console
push NULL
push offset numberOfChars
push 10
push offset thirdStr;##########################
push outputHandle
call WriteConsole


; Entering second-closing-line in the console
push NULL
push offset numberOfChars
push 4
push offset second_closing_line
push outputHandle
call WriteConsole  

; Entering sixth-line in the console
push NULL
push offset numberOfChars
push 20
push offset sixth_line
push outputHandle
call WriteConsole

; Entering seventh-line in the console
push NULL
push offset numberOfChars
push 20
push offset seventh_line
push outputHandle
call WriteConsole  


push NULL
push offset numberOfChars
push 1
push offset firstStr
push inputHandle
call ReadConsole

push 0
call ExitProcess
end entryPoint