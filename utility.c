/* Noah Toma - 100825559 
 *
 * Group #5
 *
 * Methods and functions for myshell
 */

#include "myshell.h"//Include header libraries

#define MAX_PATH_LENGTH 2048//Stores the max allowable length of a path

//Change the current working directory
void ch_dir(char *path)
{
	//Buffer to store current working directory path
	char cwd[1024];
    
	//If path argument is NULL, no directory was provided
	if (path == NULL) 
	{
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

		//If 'chdir()' returns a non-zero value, an error occurred
		if (chdir(path) != 0)
			perror("'chdir()' ERROR");
		else
			setenv("PWD", getcwd(cwd, sizeof(cwd)), 1);
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
		printf("| %s |\n", entry->d_name);//Print the directory names

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

//Function to get the directory of the executable
char *get_executable_directory() 
{
	//Buffer to store the path
	static char dir[MAX_PATH_LENGTH];

	//Read the symbolic link pointing to the executable
	ssize_t len = readlink("/proc/self/exe", dir, sizeof(dir) - 1);
	if (len != -1) 
	{
		dir[len] = '\0';//Null-terminate the string

		//Find the last occurrence of '/' to get the directory
		char *last_slash = strrchr(dir, '/');
		if (last_slash != NULL) 
		{
			*(last_slash + 1) = '\0';//Null-terminate at the last '/'
			return dir;
		}
	}

	return NULL;//Return NULL on failure
}

//Function to check if a file exists
int file_exists(const char *filename) 
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

//Function to initialize the environment variable for the readme file
void init_readme_env() 
{
	char *executable_dir = get_executable_directory();
	if (executable_dir != NULL) 
	{
		//Construct the path to the readme file
		char readme_path[MAX_PATH_LENGTH];
		snprintf(readme_path, sizeof(readme_path), "%sreadme", executable_dir);

		//Check if the readme file exists
		if (file_exists(readme_path)) 
		{
			//Set the environment variable with the path
			setenv("MY_SHELL_README", readme_path, 1);
		}
	}
}

//Function to display the user manual
void disp_man() 
{
	//Retrieve the path from the environment variable
	char *readme_path = getenv("MY_SHELL_README");
	if (readme_path != NULL) 
	{
		//Display the contents of the readme file using a text viewer
		char command[MAX_PATH_LENGTH + 10];//Add extra space for command
		snprintf(command, sizeof(command), "more \"%s\"", readme_path);

		int res = system(command);
		if (res != 0)
			fprintf(stderr, "ERROR: Unable to display user manual using 'more'!\n");
	}
	else
		fprintf(stderr, "ERROR: README file not found!\n");
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
