:loop
data.exe > in.txt  
J-std.exe < in.txt > J-std.txt  
J.exe < in.txt > J-ans.txt 
fc /A J-std.txt J-ans.txt
if not errorlevel 1 goto loop
pause
:end