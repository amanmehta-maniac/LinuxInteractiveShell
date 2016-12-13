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
//check info of process with pid given.
int execPINFO(char **param)
{

	char path[clmax],stat[clmax],memory[clmax],str[clmax];
	char status[clmax],str2[clmax],memory2[clmax],stat2[clmax],status2[clmax];
	FILE *fp,*fp2;
	if(param[1] == NULL)
	{
		char path[clmax] = "~/./a.out";
		int pid = getpid();
		fp = fopen("/proc/self/status","r");
		fgets(stat,clmax,fp);
		fscanf(fp,"%s %s",str,status);
		while(1)
		{
			fgets(str,100,fp);
			if(strstr(str,"VmPeak") !=NULL)
			{
				break;
			}
		}
		fscanf(fp,"%s %s",str,memory);
		fclose(fp);
		fp2 = fopen("/proc/self/status","r");
		fgets(stat2,clmax,fp2);
		fscanf(fp2,"%s %s",str2,status2);
		while(1)
		{
			fgets(str2,100,fp2);
			if(strstr(str2,"NSsid") !=NULL)
			{
				break;
			}
		}
		fscanf(fp2,"%s %s",str2,memory2);
		fclose(fp2);
		printf("PID: %d\nProcess Status : %s\nProcess lloudalafouawfMemory(Virtual):%s\nPeak Process Memory(Virtual): %s\nExecutable Path: %s\n",pid,status,memory,memory2,path);
	}
	else
	{
		char folder1[clmax] = "/proc/";
		char folder2[clmax] = "/proc/";
		char file1[clmax] = "/status";
		char file2[clmax] = "/cmdline";
		char *x;
		char *y;
		x = strcat(folder1,param[1]);
		printf("x=%s\n",x);
		y = strcat(folder2,param[1]);
		printf("x=%s\ty=%s\n",x,y);
		strcat(x,file1);
		strcat(y,file2);
		printf("x=%s\ty=%s\n",x,y);
		fp = fopen(x,"r");
		if(fp==NULL)  
		{
			printf("ERR: Some problem occurred while running pinfo of given pid, maybe because no process of given pid exists.\nNOTE: You cannot find pinof of 'ps' command\nTry some other pid\n");
			return 0;
		}
		char *err = fgets(stat,clmax,fp);
		if(err==NULL) {
			printf("ERR: Some problem occurred while running pinfo of given pid, maybe because no process of given pid exists.\nNOTE: You cannot find pinof of 'ps' command\nTry some other pid\n");
			return 0;
		}
		fscanf(fp,"%s %s",str,status);
		while(1)
		{
			fgets(str,20,fp);
			if(strstr(str,"VmPeak") !=NULL)
			{
				break;
			}
		}
		fscanf(fp,"%s %s",str,memory);
		fseek(fp,0,SEEK_SET);
		err = fgets(stat,clmax,fp);
		if(err==NULL) {
			printf("ERR: Some problem occurred while running pinfo of given pid, maybe because no process of given pid exists.\nNOTE: You cannot find pinof of 'ps' command\nTry some other pid\n");
			return 0;
		}
		fscanf(fp,"%s %s",str2,status);
		while(1)
		{
			fgets(str2,20,fp);
			if(strstr(str2,"NSsid") !=NULL)
			{
				break;
			}
		}
		fscanf(fp,"%s %s",str2,memory2);
		fclose(fp);
		fp = fopen(y,"r");
		char path[clmax];
		fgets(path,clmax,fp);
		fclose(fp);
		printf("PID: %s\nProcess Status : %s\nProcess Memory(Virtual):%s\nPeak Process Memory(Virtual): %s\nExecutable Path: %s\n",param[1],status,memory,memory2,path);
	}
	return 0;
}
