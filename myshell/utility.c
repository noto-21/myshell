#include "myshell.h"//Include header libraries

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
	//External pointer to an array of strings (char pointers), 
	//to be found elsewhere on the system; variable to be 
	//resolved at the linking stage
	extern char **environ;
	int i = 0;//Counter variable

	//If there is an error finding environment variables
	if (environ == NULL)
	{
		perror("'environ' var.s ERROR");//Print error message
		return;//Exit the function
	}

	while (environ[i] != NULL)//While environment strings exist to be read
	{
		printf("%s\n", environ[i]);//Print the environment variables
		i++;//Increment counter
	}
}


//Echo user comments
void echo_out(char *ech)
{
	//If no string is provided
	if (ech == NULL)
	{
		printf("\n");//Print new line
		return;//Exit function
	}

	//String processing
	char processed[1024];//Buffer w/assumed max length for string processing
	int i, j = 0;//Counter variables
	
	for (i = 0; ech[i] != '\0'; i++)//Iterate until null termination
	{
		//If the current char is not a space and the char before it is not a space
		if (!isspace((unsigned char)ech[i]) || (i > 0 && !isspace((unsigned char)ech[i - 1])))
			processed[j++] = ech[i];//Include the char in the processed string and iterate 'j'
	}

	processed[j] = '\0';//Null-terminate processed string

	if (printf("%s", processed) < 0)//Take user input and output it to the screen
		perror("'printf' ERROR");//Print error message if something goes wrong
}

//Display user manual via text viewer
void disp_man()
{
    #ifdef _WIN32//If on Windows, open the manual with notepad
        int res = system("notepad.exe readme");
	//Check for errors
        if (res != 0)
            fprintf(stderr, "ERROR: Unable to display user manual using 'notepad.exe'!\n");
    #else
        //Check if 'more' is available on the system
        if (system("which more > /dev/null") == 0)
        {
            //Open manual using 'more'
            int res = system("more readme");
            //Check for errors
	    if (res != 0)
                fprintf(stderr, "ERROR: Unable to display user manual using 'more'!\n");
        }
        else//'more' is not on the system
            fprintf(stderr, "ERROR: 'more' command is not available on this system!\n");
    #endif
}

//Pause the shell
void suspend()
{
	printf("Press 'Enter' to continue...");//Print continue prompt
	
	int c;//Char tracking variable
	while ((c = getchar()) != '\n' && c != EOF)
		//Discard chars in input buffer

	getchar();//Wait until input is detected
}


//Quit the shell
void quit()
{
	printf("|> Exiting myshell...goodbye!\n");//Print exit message
	exit(0);//Successful exit
}
