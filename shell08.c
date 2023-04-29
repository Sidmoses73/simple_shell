#include "shell.h"

/**
 * buffer_input - buffers multiple commands together
 * @param_list: parameter list struct
 * @buffer: address of the buffer
 * @len: address of the length variable
 *
 * Return: bytes read
 */
ssize_t buffer_input(param_list_t *param_list, char **buffer, size_t *len)
{
	ssize_t read_bytes = 0;
	size_t len_position = 0;

	if (!*len) /* if buffer is empty, fill it with input */
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_signal_interrupt);
#if USE_GETLINE
		read_bytes = getline(buffer, &len_position, stdin);
#else
		read_bytes = _getline(param_list, buffer, &len_position);
#endif
		if (read_bytes > 0)
		{
			if ((*buffer)[read_bytes - 1] == '\n')
			{
				(*buffer)[read_bytes - 1] = '\0'; /* remove trailing newline */
				read_bytes--;
			}
			param_list->line_count_flag = 1;
			remove_comments(*buffer);
			build_history_list(param_list, *buffer, param_list->histcount++);
			/* if (_strchr(*buffer, ';')) is this a command chain? */
			{
				*len = read_bytes;
				param_list->cmd_buffer = buffer;
			}
		}
	}
	return (read_bytes);
}

/**
 * get_input - gets a line of input without the newline
 * @param_list: parameter list struct
 *
 * Return: bytes read
 */
ssize_t get_input(param_list_t *param_list)
{
	static char *buffer; /* buffer for command chains with ';' */
	static size_t i, j, len;
	ssize_t read_bytes = 0;
	char **arg_p = &(param_list->arg), *p;

	_putchar(BUF_FLUSH);
	read_bytes = buffer_input(param_list, &buffer, &len);
	if (read_bytes == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* initialize new iterator to current buffer position */
		p = buffer + i; /* get pointer for return */

		check_command_chain(param_list, buffer, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_command_chain(param_list, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past null ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			param_list->cmd_buffer_type = CMD_NORM;
		}

		*arg_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*arg_p = buffer; /* else not a chain, pass back buffer from _getline() */
	return (read_bytes); /* return length of buffer from _getline() */
}
/**
 * read_buffer - reads a buffer from a file descriptor
 * @fd: file descriptor
 * @buffer: buffer
 * @buffer_size: size of the buffer
 *
 * Return: the number of bytes read on success, -1 on failure
 */
ssize_t read_buffer(int fd, char *buffer, size_t buffer_size)
{
ssize_t bytes_read = 0;

if (buffer_size == 0)
{
return (0);
}

bytes_read = read(fd, buffer, buffer_size);
if (bytes_read < 0)
{
return (-1);
}
return (bytes_read);
}

/**
 * get_line - gets the next line of input from a file descriptor
 * @fd: file descriptor
 * @line: address of pointer to buffer, preallocated or NULL
 * @line_size: size of preallocated line buffer if not NULL
 *
 * Return: the number of bytes read on success, -1 on failure
 */
int get_line(int fd, char **line, size_t *line_size)
{
static char buffer[READ_BUFFER_SIZE];
static size_t buffer_start = 0, buffer_end = 1;
size_t line_length = 0;
ssize_t bytes_read = 0;
char *line_start = NULL, *new_line = NULL, *line_end = NULL;

line_start = *line;
if (line_start && line_size)
{
line_length = *line_size;
}
if (buffer_start == buffer_end)
{
buffer_start = buffer_end = 0;
}

bytes_read = read_buffer
(fd, buffer + buffer_end, READ_BUFFER_SIZE - buffer_end);
if (bytes_read < 0 || (bytes_read == 0 && buffer_end == 0))
{
return (-1);
}

line_end = strchr(buffer + buffer_start, '\n');
line_length += (line_end ? 1 + (size_t)(line_end - buffer) : bytes_read);
new_line = realloc(line_start, line_length + 1);
if (!new_line)
{
return (line_start ? (free(line_start), -1) : -1);
}

if (line_start)
{
strncat(new_line, buffer + buffer_start, line_length - *line_size - 1);
}
else
{
strncpy(new_line, buffer + buffer_start, line_length - buffer_start + 1);
}

*line = new_line;
if (line_size)
{
*line_size = line_length;
}

buffer_start += (line_end ? (size_t)(line_end - buffer) - buffer_start + 1 : bytes_read);
return (line_length);
}

/**
 * handle_sigint - blocks SIGINT signals
 * @sig_num: signal number
 *
 * Return: void
 */
void handle_sigint(__attribute__((unused)) int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUFFER_FLUSH);
}

