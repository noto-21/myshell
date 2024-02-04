#include "myshell.h"//Include header libraries

//Execute commands
void exec_cmd(char *in)
{
    char *tkn;
    char *dlim = " \n";
    tkn = strtok(in, dlim);//Tokenize input

    //If first token is a command
    if (tkn != NULL) 
    {
        if (strcmp(tkn, "cd") == 0)//Change directories command
	{
            tkn = strtok(NULL, dlim);//Get arg (directory path)
            ch_dir(tkn);//Call the function
        }
	else if (strcmp(tkn, "clr") == 0)//Clear screen command
		clr_scr();
	else if (strcmp(tkn, "dir") == 0)//List directory command
	{
		tkn = strtok(NULL, dlim);
		list_dir(tkn);
	}
	else if (strcmp(tkn, "environ") == 0)//List environment command
		list_env();
	else if (strcmp(tkn, "echo") == 0)//Echo string command
		echo_out(in + strlen("echo "));
	else if (strcmp(tkn, "help") == 0)//Display manual command
		disp_man();
	else if (strcmp(tkn, "pause") == 0)//Pause shell command
		suspend();
	else if (strcmp(tkn, "quit") == 0 || strcmp(tkn, "exit") == 0)//Quit shell command
		quit();
	else
	{
		//Fork and exec system calls for external commands
		pid_t pid = fork();	
		if (pid == 0)//Child
		{
			setenv("parent", "./myshell", 1);//Set parent env. var.
			execlp(tkn, tkn, NULL);
			perror("'exec()' ERROR");
			exit(1);
		}
		else if (pid > 0)//Parent
			waitpid(pid, NULL, 0);//Wait for child to terminate
		else
			perror("'fork()' ERROR");
	}
    }
}

int main()
{
	char in[1024];//Input buffer
	char cwd[1024];//CWD buffer

	//Get CWD
	if (getcwd(cwd, sizeof(cwd)) == NULL)//If an error occurs
	{
		perror("'getcwd()' ERROR");//Print error message
		return 1;//Exit w/error
	}

	//Set shell env. var.
	char shell_path[2048];
	snprintf(shell_path, sizeof(shell_path), "shell=%s/myshell", cwd);//Format as safe/size-limited string
	if (putenv(shell_path) != 0)//Set environment variable
	{
		perror("'putenv()' ERROR");//Error message if something goes wrong
		return 1;//Exit w/error
	}

	//Run loop
	while (1) 
	{
		printf("<%s>\n |> ", getcwd(cwd, sizeof(cwd)));//Prompt for input
		if (fgets(in, sizeof(in), stdin) == NULL)
			break;//Exit on EOF

		exec_cmd(in);//Execute input
	}

	return 0;
}
