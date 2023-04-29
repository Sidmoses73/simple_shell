#include "shell.h"

/**
 * initialize_info - initializes the fields of info_t struct
 * @info: pointer to info_t struct
 */
void initialize_info(info_t *info)
{
	info->arguments = NULL;
	info->argument_vector = NULL;
	info->path = NULL;
	info->argument_count = 0;
}

/**
 * set_info - sets the fields of info_t struct
 * @info: pointer to info_t struct
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->function_name = av[0];
	if (info->arguments)
	{
		info->argument_vector = strtow(info->arguments, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->arguments);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_alias(info);
		replace_variables(info);
	}
}

/**
 * free_info - frees fields of info_t struct
 * @info: pointer to info_t struct
 * @all: true if freeing all fields
 */
void free_info(info_t *info, int all)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->arguments);
		if (info->environment_variables)
			free_list(&(info->environment_variables));
		if (info->history)
			free_list(&(info->history));
		if (info->aliases)
			free_list(&(info->aliases));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUFFER_FLUSH);
	}
}
