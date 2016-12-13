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
#define Cyan "\e[36m"
// Function to get the us:wername of user logged in ..
//stores commands after tokenised by ";"
char * tokenedCmd;
// 2D array that stores commands with arguments
char cmdWithParams[100][100];
char *copyright = "Aman's Shell";
char *sym = "=>";
// get username
char * cuserid (char * Name);
int print(char * user, char * currDir);
//this will execute PWD
void execPWD(char *dir) {printf("%s\n",dir);}
//delimiter which will take care of all spaces and tabs. 
char *delimAllSpaces = "' '\t";
//semicolon delimiter
char delimScolon[2] = ";";
// checks whether process is background or not. ("&")
int ampersand;
char currDir[1024];
//stores path of directory of this terminal
char tilde[1024];

char newCurr[1024];
//stores username
char user[200];
char quote = '"';
//function definitions
int parseCmd(char * cmd, char ** params);
int execRestCmd(char ** params,int ampersa);
int execCD(char ** params);
int execPINFO(char ** param);
void execECHO(char **para, int type,char *line);

int main()
{
	//initial string of commands
	char cmd[clmax + 1];
	//space and colon delimited string of commands
	char * params[plmax + 1];
	int cmdCount = 0,i=0,temp=0;
	char bye[clmax + 1]  = "Thanks for using Aman's Shell :)\n";
	char *input;
	getcwd(tilde,sizeof(tilde));
	int exit=0;

	while(1) {
		if(exit) break;
		ampersand = 0;
		temp=0;
		// Getting the current working directory of user and username of user logged in ..                      
		char *ptr = getcwd(currDir, sizeof(currDir));
		if(ptr==NULL) printf("Err: Some error occured while getting the current working directory\n");
		//Get the Login name of the user
		cuserid(user);
		int sizeT = strlen(tilde);
		int sizeC = strlen(currDir);
		int index;

		// Print the username of shell ..
		//printf("curr=%s len=%d\t tilde=%s len=%d\n",currDir,sizeC,tilde,sizeT);
		//This piece of code prints the path of folder as relative to our new tilde
		if(!strcmp(currDir,tilde) && sizeC == sizeT) print(user,"~");
		else if(strcmp(currDir,tilde) && sizeC >= sizeT) 
		{
			index = INT_MAX;
			for(i=0;i<sizeT;i++)
			{
				if(currDir[i] != tilde[i]) {index = i;break;}
			}
			
						if(index==INT_MAX)
			{
				newCurr[0] = '~';
				for(i=sizeT;i<sizeC;i++)
					newCurr[i+1-sizeT] = currDir[i];
				print(user,newCurr);
			}
			else
				print(user,currDir);
		}
		else
		{
			print(user,currDir);
		}
		// Read command from standard input, exit on Ctrl+D
		input = fgets(cmd,sizeof(cmd),stdin);
		//Exit on CTRL + D 
		if(input == NULL) {exit=1;printf("\n%s%s",Cyan,bye); break;}
		//Exit if input command is "exit"
		if(!strcmp(cmd,"exit")) {exit=1;printf("%s%s",Cyan,bye); break;}
		///printf("command= %s\n",cmd);
		// Remove trailing newline character, if any
		if(cmd[strlen(cmd)-1] == '\n') {
			cmd[strlen(cmd)-1] = '\0';
		}
		//		printf("\nYes\n");
		tokenedCmd = strtok(cmd,delimScolon);
		int type=0,fault=0;
		//tokenise with semicolon
		if(tokenedCmd)
		{
			while(2>1){
				//printf("%s\n",tokenedCmd);
				strcpy(cmdWithParams[temp],tokenedCmd);
				tokenedCmd = strtok(NULL,delimScolon);
				temp++;
				if(!tokenedCmd) break;
			}
		}
				// Split cmd into array of parameters
		//		printf("Split : %s\n",tokenedCmd);
		//tokenize with spaces and tabs
		for(i=0;i<temp;i++){
			type = 0;
			fault=0;
			printf("%s\n",cmdWithParams[i]);
			//			SplitAgain(params);
			//			parseCmd()
			//parse through command 2d array
			ampersand = parseCmd(cmdWithParams[i], params);
			//printf("ampersand = %d\n",ampersand );
			//printf("Split : %s\n",params[1]);
			// Exit?
			if(!strcmp(params[0],"exit")) {exit = 1;printf("%s%s",Cyan,bye);break;}
			// Execute command echo considering double quotes!**
			else if(strcmp(params[0],"echo") == 0){
				i=1;
				int j=0;
				int count = 0;
				while(params[i]!=NULL)
				{
					for(j=0;j<strlen(params[i]);j++)
					{
						if(params[i][j] == '"')
							count++;
						//		printf("j is infinte\n");
					}
					//	printf("i is infinte\n");
					i++;
				}
				if(count%2){
					fault = 1;
					printf("Err: Missing closing quotes\n");
				}
				else type = 1;
				printf("it = %d\n",type);
				if(!fault) execECHO(params,type,cmd);
			}
			//execute pinfo
			else if(strcmp(params[0],"pinfo") == 0){
				execPINFO(params);
			}
			//execute pwd
			else if(strcmp(params[0],"pwd") == 0){
				execPWD(currDir);
			}
			//execute cd
			else if(strcmp(params[0],"cd") == 0){
				execCD(params);
			}
			//execute rest of the commands.
			else if(execRestCmd(params,ampersand) == 0) break;
			//			tokenedCmd = strtok(NULL,delimScolon);
		}
	}

	return 0;
}
