#ifndef SHELL_H
#define SHELL_H
#define MAX_LINE 80

extern char **environ;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

/* function declarations*/
void parse_input(char* input, char **args);
void execute_command(char **args);
int builtin_command(char **args);


#endif
