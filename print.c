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
//prints prompt.
int print(char * user, char * currDir){
	//	char * Company = "DEll";
	char hostName[100];
	int err=gethostname(hostName,sizeof(hostName));
	//	printf("%s@%s:%s $ ",user,hostName,currDir);
	if(err==-1) printf("Err: Some error occured while getting the hostname\n");
	printf("%sAman's Shell=>",LightYellow);
	//	printf("%s=>",GreenBlock);
	printf("%s ",White);
	printf("%s%s@%s%s:%s $",Green,user,Red,hostName,currDir);
	printf("%s ",White);
	return 0;
}