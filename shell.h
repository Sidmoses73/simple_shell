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
int is_shell_interactive(shell_info_t *shell_info);
int is_character_delimiter(char c, char *delimiters);
int is_character_alpha(int c);
int convert_string_to_integer(char *s);
int exit_shell(info_t *info);
int change_dir(info_t *info);
int print_command_history(shell_info_t *shell_info);
int unset_command_alias(shell_info_t *shell_info, char *alias_str);
int set_command_alias(shell_info_t *shell_info, char *alias_str);
int print_command_alias(list_t *alias_node);
int handle_command_alias(shell_info_t *shell_info);
int print_env(shell_info_t *shell_info);
char *get_env(shell_info_t *shell_info, const char *name);
int set_env(shell_info_t *shell_info);
int unset_env(shell_info_t *shell_info);
int populate_env_vars_list(shell_info_t *shell_info);
void custom_puts(char *str);
int custom_putchar(char c);
int custom_put_fd(char c, int fd);
int custom_puts_fd(char *str, int fd);
int str_to_int(char *str);
void print_error_msg(info_t *info, char *error_msg);
int print_decimal(int number, int fd);
char *num_to_str(long int num, int base, int flags);
void remove_first_comment(char *str);
char *copy_string(char *dst, char *src, int max_len);
char *concatenate_string(char *dst, char *src, int max_len);
char *find_character(char *str, char c);
ssize_t read_buffer(int fd, char *buffer, size_t buffer_size);
int get_line(int fd, char **line, size_t *line_size);
void handle_sigint(__attribute__((unused)) int sig_num);
char **get_environment(info_t *info);
int remove_environment_variable(info_t *info, char *var_name);
int set_environment_variable(info_t *info, char *var_name, char *value);
void initialize_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);
int entry(int argument_count, char **arguments);
void execute_cmd(info_t *info);
void run_command(info_t *info);

#endif
