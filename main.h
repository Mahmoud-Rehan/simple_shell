#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFSIZE 128
#define DELIM " \t\r\n\a"

/* Points to an array of pointers to the "environment" strings*/
extern char **environ;


/**
 * struct data - struct that contains all relevant data.
 * @argv: Argument vector.
 * @input: Command line written by the user.
 * @arguments: Tokens of the command line.
 * @stat: last Status of the shell.
 * @count: Lines counter.
 * @env: Environment variable.
 * @pid: Process ID of the shell.
 */

typedef struct data
{
	char **argv;
	char *input;
	char **arguments;
	int stat;
	int count;
	char **env;
	char *pid;
} shell_data;

/**
 * struct separate_list - Linked list.
 * @sep: ; | &
 * @next: next node.
 */

typedef struct separate_list
{
	char sep;
	struct separate_list *next;
} sep_t;

/**
 * struct cmdline_list - Linked list.
 * @cmd: command line.
 * @next: next node.
 */

typedef struct cmdline_list
{
	char *cmd;
	struct cmdline_list *next;
} cmdline_t;

/**
 * struct var_list - Linked list.
 * @var_length: length of the variable.
 * @value: value of the variable.
 * @val_length: length of the value.
 * @next: next node.
 */

typedef struct var_list
{
	int var_length;
	char *value;
	int val_length;
	struct var_list *next;
} var_t;

/**
 * struct builtins_list - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env.
 * @function: data type pointer function.
 */

typedef struct builtin_list
{
	char *name;
	int (*function)(shell_data *data);
} builtins_t;


/* lists_functions2.c */
sep_t *insert_sepnode_at_end(sep_t **head_ptr, char sp);
void free_sep_list(sep_t **head_ptr);
cmdline_t *insert_cmdnode_at_end(cmdline_t **head_ptr, char *command);
void free_cmdline_list(cmdline_t **head_ptr);

/* list_functions1.c */
var_t *insert_varnode_at_end(var_t **head_ptr, int var_len, char *value, int val_len);
void free_var_list(var_t **head_ptr);

/* strig_functions2.c */
char *string_cat(char *str1, const char *str2);
char *string_cpy(char *str1, char *str2);
int string_cmp(char *str1, char *str2);
char *string_chr(char *str, char c);
int string_spn(char *str, char *accept_bytes);

/* memory_functons.c */
void memory_cpy(void *newp, const void *p, unsigned int ptr_size);
void *reallocate(void *p, unsigned int size, unsigned int newsize);
char **realloc_dptr(char **p, unsigned int size, unsigned int newsize);

/* string_functions3.c */
char *string_dup(const char *str);
int string_len(const char *str);
int chars_cmp(char s[], const char *delim);
char *string_tok(char s[], const char *delim);
int is_digit(const char *str);

/* string_functions1.c */
void string_rev(char *str);

/* syntax_error_check.c */
int char_repeated(char *input_str, int n);
int sep_error(char *input_str, int n, char c);
int first_char_indx(char *input_str, int *n);
void syntax_error_print(shell_data *data, char *input_str, int n, int bool);
int syntax_error_check(shell_data *data, char *input_str);

/* loop.c */
char *delete_comment(char *input);
void loop(shell_data *data);

/* read.c */
char *_readline(int *return_val);

/* separate.c */
char *_swapchar(char *input_str, int bool);
void insert_nodes(sep_t **sep_head, cmdline_t **cmd_head, char *input_str);
void _next(sep_t **sep_list, cmdline_t **cmd_list, shell_data *data);
int separate_commands(shell_data *data, char *input_str);
char **separate_input(char *input_str);

/* replace.c */
void environ_check(var_t **head, char *input, shell_data *data);
int vars_check(var_t **head, char *input, char *last, shell_data *data);
char *replace_input(var_t **head, char *input, char *new_input, int nlen);
char *replace_var(char *input_str, shell_data *data);

/* getline.c */
void _bringline(char **buffer_ptr, size_t *line_size, char *buf, size_t size);
ssize_t _getline(char **buffer_ptr, size_t *size, FILE *stream);

/* exec.c */
int execute_line(shell_data *data);

/* exec_command.c */
int is_current_dir(char *path, int *n);
char *which_cmd(char *command, char **_env);
int is_exec(shell_data *data);
int command_error_check(char *directory, shell_data *data);
int execute_command(shell_data *data);

/* environ1.c */
char *_getenviron(const char *env_name, char **_env);
int _environ(shell_data *data);
int environ_cmp(const char *env_name, const char *input);

/* environ2.c */
char *info_cpy(char *var_name, char *var_value);
void set_environ(char *env_name, char *env_value, shell_data *data);
int _setenviron(shell_data *data);
int _unsetenviron(shell_data *data);

/* change_dir1.c */
void cd_parent(shell_data *data);
void change_dir(shell_data *data);
void cd_prev(shell_data *data);
void cd_home(shell_data *data);

/* change_dir2.c */
int cd_current(shell_data *data);

/* builtin.c */
int (*_getbuiltin(char *command))(shell_data *data);

/* exit.c */
int shell_exit(shell_data *data);

/* stdlib_functions.c */
int _getlen(int num);
char *_itos(int num);
int _stoi(char *str);

/* error_functions2.c */
char *string_cat_cd(shell_data *, char *, char *, char *);
char *get_error_cd(shell_data *data);
char *not_found_error(shell_data *data);
char *exit_error(shell_data *data);

/* error_functions1.c */
char *error_get_alias(char **args);
char *environ_error(shell_data *data);
char *error_syntax(char **args);
char *error_permission(char **args);
char *path_error(shell_data*data);


/* error.c */
int _geterror(shell_data *data, int error_val);

/* getsigint.c */
void _getsigint(int signal);

/* help_functions2.c */
void env_help(void);
void setenv_help(void);
void unsetenv_help(void);
void general_help(void);
void exit_help(void);

/* help_functions1.c */
void _help(void);
void alias_help(void);
void cd_help(void);

/* help.c */
int _gethelp(shell_data *data);

#endif
