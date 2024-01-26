#include "myshell.h"

void prompt()
{
	char cwd[MAX_PATH_LENGTH];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s$ ", cwd);
	else
		perror("getcwd() error");
}

void input(char *in)
{
	fgets(in, MAX_INPUT_LENGTH, stdin);
	
	in[strcspn(in, "\n")] = '\0';//Remove newline char
}

int execInternalCmd(char *in)
{
	//Parse input for internal commands
	//Implement functionality for internal commands
	//Return 1 if the command is internal, 0 otherwise
}

void execExternalCmd(char *in)
{
	pid_t pid;
	int stat;

	pid = fork();

	if (pid == 0)//Child
	{
		//Set env. var. and execute cmd
		setenv("parent", SHELL_PATH, 1);
		
		execCmd(in);
	}
	else if (pid < 0)//Error
		perror("Fork failed!");
	else//Parent proc.
		waitpid(pid, &stat, 0);
}

void execCmd(char *in)
{
	//Command exec. w/execvp
}

//Other goes here
