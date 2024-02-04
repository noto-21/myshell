#ifndef MYSHELL_H  // Prevents double inclusion of this header file
#define MYSHELL_H

#include <stdio.h>   // Standard I/O functions
#include <stdlib.h>  // Standard library for functions like malloc
#include <string.h>  // String handling functions
#include <unistd.h>  // Provides access to the POSIX operating system API

//Change directories function (cd)
void ch_dir(char *path);

//Clear screen
void clr_scr();

//List contents of directory
void list_dir(char *dir);

//List environment strings
void list_env();

//Echo strings
void echo_out(char *ech);

//Display user manual
void disp_man();

//Pause shell
void suspend();

//Quit shell
void quit();

#endif
