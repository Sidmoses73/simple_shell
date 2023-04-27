#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 100
#define MAX_ARGS 20

int main(void)
{
char cmd[MAX_CMD_LEN];
char* args[MAX_ARGS];
int status;
int i = 0;
pid_t pid;

while (1)
{
printf("> ");
fflush(stdout);

if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
{
exit(0);
}

cmd[strcspn(cmd, "\n")] = 0;

args[i] = strtok(cmd, " ");
while (args[i] != NULL && i < MAX_ARGS-1)
{
i++;
args[i] = strtok(NULL, " ");
}
args[i] = NULL;
if (args[0] == NULL)
{
continue;
}

if (strcmp(args[0], "exit") == 0)
{
exit(0);
}
else if (strcmp(args[0], "cd") == 0)
{
if (args[1] == NULL)
{
fprintf(stderr, "cd: no argument provided\n");
}
else
{
if (chdir(args[1]) == -1)
{
perror("cd");
}
}
continue;
}

pid = fork();
if (pid == -1)
{
perror("fork");
}
else if (pid == 0)
{
execve(args[0], args, NULL);
perror(args[0]);
_exit(EXIT_FAILURE);
}
else
{

waitpid(pid, &status, 0);
}
}

return (0);
}

