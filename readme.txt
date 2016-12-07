README
_______________________________________________________
_______________________________________________________

FEATURES IMPLEMENTED
-------------------------------------------------------
The shell supports pinfo,cd,pwd,echo and other built in commands.
echo is able to manage double quotes successfully.
Errors are handled properly using perror.
Echo command is not the same as in the bash shell(acts differently on presence of escape characters and semicolon). Double quotes are dealt with.


HOW TO COMPILE
-------------------------------------------------------

to compile run the command:-   make

HOW TO RUN
-------------------------------------------------------
run the command:- ./main
-------------------------------------------------------
-------------------------------------------------------

FILES
-------------------------------------------------------
execPINFO.c:- the function to execute pinfo command (bonus).
execCD.c:- the function to execute cd command (with tilde properly taken care).
execRestCmd.c:- the function to execute built in commands other than pwd,cd,echo and pinfo.
execECHO.c:- the function to execute echo command.
execPWD.c:- the function to execute pwd command.
parse.c:- the function to parse the given string of commands properly.
print.c:- the function to print the initials in shell.
main.c:- the main code of Aman's Shell.

