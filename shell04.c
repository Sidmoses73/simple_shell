#include "shell.h"

#define MAX_INPUT_LENGTH 1024
/**
 * exit_main - Function to exit
 * Return: Exit success
 */
int exit_main(void)
{
char input[MAX_INPUT_LENGTH];
char *args[10];
int should_run = 1;
int i = 0;
while (should_run)
{
printf("Simple shell 0.3 +\n$ ");
fgets(input, MAX_INPUT_LENGTH, stdin);
args[i] = strtok(input, " \n");
while (args[i] != NULL && i < 9)
{
i++;
args[i] = strtok(NULL, " \n");
}
args[i] = NULL;
if (args[0] != NULL && strcmp(args[0], "exit") == 0)
{
should_run = 0;
printf("Exiting Simple shell...\n");
break;
}
memset(input, 0, MAX_INPUT_LENGTH);
memset(args, 0, sizeof(args));
}
return (EXIT_SUCCESS);
}
