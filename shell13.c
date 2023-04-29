#include "shell.h"

/**
* get_history_file - function to retrieve the hisory
* of a file for the current user.
* @param - info of  the parameter struct.
* Return: The path to the history file, or NULL on failure.
*/
char *get_history_file(info_t *info)
{
char *dir = _getenv(info, "HOME=");
if (!dir)
{
return (NULL);
}
char *filename = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!filename)
{
return (NULL);
}
_strcpy(filename, dir);
_strcat(filename, "/");
_strcat(filename, HIST_FILE);
free(dir);
return (filename);
}

/**
* write_history - Write the shell history to a file.
* @param - info to the parameter struct.
* Return: 1 on success, -1 on failure.
*/
int write_history(info_t *info)
{
char *filename = get_history_file(info);
if (!filename)
{
return (–1);
}
ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
{
return (-1);
}
for (list_t *node = info->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
* read_history - Read the shell history from a file.
* @param info The parameter struct.
* return: The number of history entries read, or 0 on failure.
*/
int read_history(info_t *info)
{
char *filename = get_history_file(info);
if (!filename)
{
return (0);
}
int linecount = 0;
ssize_t fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
{
return (0);
}
struct stat st;
if (!fstat(fd, &st))
{
ssize_t fsize = st.st_size;
if (fsize < 2)
{
close(fd);
return (0);
}
char *buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
{
close(fd);
return (0);
}
ssize_t rdlen = read(fd, buf, fsize);
buf[fsize] = '\0';
if (rdlen <= 0)
{
free(buf);
close(fd);
return (0);
}
close(fd);
int last = 0;
for (int i = 0; i < fsize; i++)
{
if (buf[i] == '\n')
{
buf[i] = '\0';
build_history_list(info, buf + last, linecount++);
last = i + 1;
}
}
if (last != fsize)
{
build_history_list(info, buf + last, linecount++);
}
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
{
delete_node_at_index(&(info->history), 0);
}
renumber_history(info);
return (info->histcount);
}
else
{
close(fd);
return (0);
}
}

