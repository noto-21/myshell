#include "myshell.h"
#include <sys/types.h>//Process management/File handling
#include <sys/wait.h>//Process management
#include <fcntl.h>//File control
#include <dirent.h>//Directory manipulation

//Change the current working directory
void ch_dir(char *path)
{
    //If path argument is NULL, no directory was provided
    if (path == NULL) 
    {
        //Buffer to store current working directory path
        char cwd[1024];

        //Use getcwd to get the current working directory.
        //getcwd fills the array 'cwd' with the absolute pathname of the current working directory
	
        if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("'getcwd()' ERROR");//Print error mssg
    }	
    else 
    {
        //If path is provided, change the directory to the specified path
        
        // If chdir returns a non-zero value, an error occurred
        if (chdir(path) != 0)//Print error mssg
            perror("'chdir()' ERROR");
    }
}

//Clear the screen
void clr_scr()
{
	//If the platform is Windows
	#ifdef _WIN32
		system("cls");//Windows system call for clearing screen
	#else		
		system("clear");//UNIX/LINUX system call for clearing screen
	#endif
}

//List contents of a directory
void list_dir(char *dir)
{
	//If no directory arg is specified
	if (dir == NULL)
		dir = ".";//List contents of CWD
	
	//Open the directory for reading
	DIR *direct = opendir(dir);
	if (direct == NULL)//If an error occurs
	{
		perror("'opendir()' ERROR");//Print error message
		return;//Exit function
	}

	//Declare a struct named 'dirent' for the directory entries
	struct dirent *entry;
	//Read the contents of the directory while not NULL, and print the names
	while ((entry = readdir(direct)) != NULL)
		printf("%s | ", entry->d_name);//Print the directory names
	
	
	if (entry == NULL)//If the last entry has been printed
		printf("\n");//Print a new line

	//Close the directory from reading
	closedir(direct);
}


//List environment strings
void list_env()
{
	extern char **environ;
	int i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}


//Echo user comments
void echo_out(char *ech)
{
	//Code here
}

//Display user manual
void disp_man()
{
	//Code here
}


//Pause the shell
void suspend()
{
	//Code here
}


//Quit the shell
void quit()
{
	//Code here
}
