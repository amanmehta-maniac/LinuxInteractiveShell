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
//THIS ECHO FUNCTION TAKES CARE OF DOUBLE QUOTES.
void execECHO(char **para,int type,char *line)
{
	int i=0;
	int index;
	for(i=0;i<clmax;i++)
	{
		if(line[i] == 'e' && line[i+1]=='c' && line[i+2] =='h' && line[i+3]=='o')
		{
			index = i+4;
			break;
		}
	}
	int it=index+1;
	int j=1;
	if(!type)
	{
		while(para[j]!=NULL)
		{
			printf("%s ",para[j]);
			j++;
		}
		printf("\n");
	}
	else
	{
		while(line[it] != '\0')
		{
			//dont print quotes
			if(line[it]!='"')
				printf("%c",line[it]);
			it++;
		}
		printf("\n");
	}
}
