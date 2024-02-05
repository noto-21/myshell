#include "myshell.h"//Include header libraries

//Skip leading spaces
char* skip_spaces(char* str)
{
	while (isspace((unsigned char)*str))
		str++;

	return str;
}

//Execute commands
void exec_cmd(char *in)
{
	char *tkn;//Char for tokens
	char *dlim = " \n";//Delimiters for args
	tkn = strtok(in, dlim);//Tokenize input

	//If first token is a command
	if (tkn != NULL) 
	{
		if (tkn[0] =='\"')
		{
			//Find the end of the quoted path
			char *end_quote = strchr(tkn + 1, '\"');
			if (end_quote != NULL)
			{
				//Replace closing quote with null terminator
				*end_quote = '\0';
				tkn = tkn + 1;//Move tkn to the start of the path
			}
		}

		if (strcmp(tkn, "cd") == 0)//Change directories command
		{
			tkn = strtok(NULL, "\n");//Use newline as delim, not space
			ch_dir(tkn);
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
		else if (strcmp(tkn, "quit") == 0)//Quit shell command
			quit();
		else
		{
			//Fork and exec system calls for external commands
			pid_t pid = fork();	
			if (pid == 0)//Child
			{
				char cwd_child[1024];//Get cwd of the child
				if (getcwd(cwd_child, sizeof(cwd_child)) == NULL)
				{
					perror("'getcwd()' ERROR");
					exit(1);
				}

				setenv("parent", getenv("shell"), 1);//Set parent env. var.
				setenv("shell", cwd_child, 1);//Set shell env. var.
				
				//Use execvp to consider paths w/spaces
				char* args[] = {tkn, NULL};
				execvp(tkn, args);

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

int main(int argc, char *argv[])
{
	char in[1024];//Input buffer
	char cwd_main[1024];//CWD buffer
	
	if (argc == 2)//If CL arg is provided
	{
		//Batch Mode - Reads commands from specified file
		FILE *bat_file = fopen(argv[1], "r");
		if (bat_file == NULL)//If error opening file
		{
			perror("Error opening batch file!");
			return 1;//Return w/error
		}

		while (fgets(in, sizeof(in), bat_file) != NULL)
		{
			printf("<%s>\n |> %s", getcwd(cwd_main, sizeof(cwd_main)), in);
			exec_cmd(in);
		}

		fclose(bat_file);

		return 0;
	}
	else if (argc > 2)//If more than two args are provided
	{
		fprintf(stderr, "Usage: %s [batchfile]\n", argv[0]);//Echo intended usage
		return 1;//Exit w/error
	}
	
	//Get current working directory
	if (getcwd(cwd_main, sizeof(cwd_main)) == NULL)
	{
		perror("'getcwd()' ERROR");
		return 1;
	}

	//Set shell env. var.
	char shell_path[2048];
	snprintf(shell_path, sizeof(shell_path), "shell=%s", cwd_main);//Format as safe/size-limited string
	if (putenv(shell_path) != 0)//Set environment variable
	{
		perror("'putenv()' ERROR");//Error message if something goes wrong
		return 1;//Exit w/error
	}

	//Interactive Mode - Solicit input from user via prompt
	while (1) 
	{
		printf("<%s>\n |> ", getcwd(cwd_main, sizeof(cwd_main)));//Prompt for input
		if (fgets(in, sizeof(in), stdin) == NULL)
			break;//Exit on EOF

		exec_cmd(in);//Execute input
	}

	return 0;
}
