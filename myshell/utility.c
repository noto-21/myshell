#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Change the current working directory
void c_dir(char *path)
{
    //If path argument is NULL, no directory was provided
    if (path == NULL) 
    {
        //Buffer to store current working directory path
        char cwd[1024];

        //Use getcwd to get the current working directory.
        //getcwd fills the array 'cwd' with the absolute pathname of the current working directory
	
        if (getcwd(cwd, sizeof(cwd)) == NULL)
            perror("getcwd() error");//Print error mssg
    }	
    else 
    {
        //If path is provided, change the directory to the specified path
        
        // If chdir returns a non-zero value, an error occurred
        if (chdir(path) != 0)//Print error mssg
            perror("myshell");
    }
}
