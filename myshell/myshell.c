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
        if (strcmp(tkn, "cd") == 0) 
	{
            tkn = strtok(NULL, dlim);//Get arg (directory path)
            c_dir(tkn);//Call the function
        } 
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
        printf("myshell | %s |\n| ", getcwd(cwd, sizeof(cwd)));//Prompt for input
        if (fgets(in, sizeof(in), stdin) == NULL)
		break;//Exit on EOF

        exec_cmd(in);//Execute input
    }

    return 0;
}
