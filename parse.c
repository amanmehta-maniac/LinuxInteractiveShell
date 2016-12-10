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
// Function to get the username of user logged in ..
char *delimAllSpace = "' '\t";
//command to parse and check ampersand existance.
int parseCmd(char* cmd, char** params)
{
	int ampersandTemp = 0;
	//	printf("%s\n",tokenedCmd);
	char * Split_temp = strtok(cmd,delimAllSpace);
	int i=0;
	while(1)
	{
		params[i] = Split_temp;
		Split_temp = strtok(NULL,delimAllSpace);
		if(params[i] == NULL) break;
		if (!strcmp(params[i],"&")) {ampersandTemp = 1;params[i]=NULL;}
		i++;
		//		else printf("%s\n",params[i]);
	}
	return ampersandTemp;
	//	printf("%s\n",tokenedCmd);
	//tokenedCmd= strtok(cmd,delimScolon);
}