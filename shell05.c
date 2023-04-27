#include "shell.h"

extern char **environ;

void print_environment(void)
{
char **env = environ;
while (*env)
{
printf("%s\n", *env++);
}
}

int env_main(void)
{
print_environment();
return (0);
}
