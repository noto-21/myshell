#include "myshell.h"

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
	{
		tkn = strtok(NULL, dlim);
		echo_out(tkn);
	}
	else if (strcmp(tkn, "help") == 0)//Display manual command
		disp_man();
	else if (strcmp(tkn, "pause") == 0)//Pause shell command
		suspend();
	else if (strcmp(tkn, "quit") == 0)//Quit shell command
		quit();
	else
            printf("Command not recognized!\n");
    }
}

int main()
{
    char in[1024];//Input buffer
    char cwd[1024];//CWD buffer

    //Run loop
    while (1) 
    {
        printf("<%s>\n | ", getcwd(cwd, sizeof(cwd)));//Prompt for input
        if (fgets(in, sizeof(in), stdin) == NULL)
		break;//Exit on EOF

        exec_cmd(in);//Execute input
    }

    return 0;
}
