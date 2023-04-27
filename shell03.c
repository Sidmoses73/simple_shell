#include"shell.h"
/**
 * main - Entry point
 * Return: 0 on success
 */
int  path_main(void)
{
char command[100];
char *args[20];
int i = 0;
pid_t pid;

while (1)
{
printf("Enter a command: ");
fgets(command, sizeof(command), stdin);
args[0] = strtok(command, " \n");
while (args[i] != NULL)
{
i++;
args[i] = strtok(NULL, " \n");
}
pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execvp(args[0], args);
perror("execvp");
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
i = 0;
memset(command, 0, sizeof(command));
memset(args, 0, sizeof(args));
}

return (0);
}
