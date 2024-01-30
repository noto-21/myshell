#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
#define MAX_PATH_LENGTH 256
#define SHELL_PATH "/path/to/myshell"

void prompt();
void input(char *in);
int execInternalCmd(char *in);
void execExternalCmd(char *in);
void execCmd(char *in);

#endif
