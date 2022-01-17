@ECHO OFF
cls
chcp 1251 > NUL
COLOR 0B
set /p fn="ֲגוהטעו טלÿ פאיכא: " 
g++ -Wfatal-errors -Wall -Wextra -pedantic -std=c++11 -O2 -s -o %fn%  %fn%.cpp 
%fn%.exe  
pause 



