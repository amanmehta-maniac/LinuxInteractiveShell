#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <limits.h>

#define clmax 1024
#define plmax 1024
#define Magenta "\e[35m"
#define Green "\e[32m"
#define Red "\e[31m"
#define White "\e[97m"
#define LightYellow "\e[93m"
#define LightRed "\e[202m"
#define MagentaBlock "\e[45m"
#define Cyan "\e[320m"
//tion to get the username of user logged in ..
extern char tilde[1024];

int execCD(char ** params){
	//	printf("%s\n",params[1]);
	if(params[1] && strcmp(params[1],"~")!=0) {int err=chdir(params[1]);
		if(err<0){
			printf("Err: Some error occured while performing <cd %s>. Please check name of directory and try again.\n",params[1]);
			perror("bash");	
		}
	}
	else chdir(tilde);
	return 0;
}
