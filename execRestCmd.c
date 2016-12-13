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
void exitStatus(int sig)
{
  pid_t pid;
  pid = wait(NULL);
  printf("Background Process with PID = %d exited Normally.\n", pid);
}
// Function to get the username of user logged in ..
//execute rest of the commands.
int execRestCmd(char ** params, int ampersand)
{
	signal(SIGCHLD, exitStatus);
	pid_t pid = fork();
	signal(SIGCHLD, SIG_IGN);

	if (pid == -1) {
		char* errnumber = strerror(errno);
		perror("bash");
		printf("Some errornumber occurred while running a process\nfork: %s\n", errnumber);
		return 1;
	}

	// Child process
	else if (pid == 0) 
	{
		// Execute command
		execvp(params[0], params);  

		// if error occurred
		char* errnumber = strerror(errno);

		printf("Aman's Shell: %s: %s\n", params[0], errnumber);
		return 0;
	}

	// Parent process
	else {
		// Wait for child process to finish
		int childStatus;
		if(!ampersand) //if foreground process then wait for the child process to finish
		{
			signal(SIGCHLD, SIG_DFL);
			waitpid(pid, &childStatus, 0);
		}
		else  // if process is background then don't wait for the child process and print the pid when exited
		{
			printf("PID=%d\n",pid);
			signal(SIGCHLD, exitStatus);
		}
		return 1;
	}
}
