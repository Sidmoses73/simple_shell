#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
/**
 * shell_main - Entry point
 * Return: 0 on success
 */
int shell_main(void)
{
pid_t pid;

pid = fork();

if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
/*child process code here*/
}
else
{
/*parent process code here*/
}
return (0);
}
