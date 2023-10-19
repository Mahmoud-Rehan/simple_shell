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

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */

typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* aux_lists.c */
sep_list *insert_sepnode_at_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *insert_cmdnode_at_end(line_list **head, char *line);
void free_cmdline_list(line_list **head);

/* aux_lists2.c */
r_var *insert_varnode_at_end(r_var **head, int lvar, char *var, int lval);
void free_var_list(r_var **head);

/* aux_str functions */
char *string_cat(char *dest, const char *src);
char *string_cpy(char *dest, char *src);
int string_cmp(char *s1, char *s2);
char *string_chr(char *s, char c);
int string_spn(char *s, char *accept);

/* aux_mem.c */
void memory_cpy(void *newptr, const void *ptr, unsigned int size);
void *reallocate(void *ptr, unsigned int old_size, unsigned int new_size);
char **realloc_dptr(char **ptr, unsigned int old_size, unsigned int new_size);

/* aux_str2.c */
char *string_dup(const char *s);
int string_len(const char *s);
int chars_cmp(char str[], const char *delim);
char *string_tok(char str[], const char *delim);
int is_digit(const char *s);

/* aux_str3.c */
void string_rev(char *s);

/* check_syntax_error.c */
int char_repeated(char *input, int i);
int sep_error(char *input, int i, char last);
int first_char_indx(char *input, int *i);
void syntax_error_print(data_shell *datash, char *input, int i, int bool);
int syntax_error_check(data_shell *datash, char *input);

/* shell_loop.c */
char *delete_comment(char *in);
void loop(data_shell *datash);

/* read_line.c */
char *_readline(int *i_eof);

/* split.c */
char *_swapchar(char *input, int bool);
void insert_nodes(sep_list **head_s, line_list **head_l, char *input);
void _next(sep_list **list_s, line_list **list_l, data_shell *datash);
int separate_commands(data_shell *datash, char *input);
char **separate_input(char *input);

/* rep_var.c */
void environ_check(r_var **h, char *in, data_shell *data);
int vars_check(r_var **h, char *in, char *st, data_shell *data);
char *replace_input(r_var **head, char *input, char *new_input, int nlen);
char *replace_var(char *input, data_shell *datash);

/* get_line.c */
void _bringline(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int execute_line(data_shell *datash);

/* cmd_exec.c */
int is_current_dir(char *path, int *i);
char *which_cmd(char *cmd, char **_environ);
int is_exec(data_shell *datash);
int command_error_check(char *dir, data_shell *datash);
int execute_command(data_shell *datash);

/* env1.c */
char *_getenviron(const char *name, char **_environ);
int _environ(data_shell *datash);
int environ_cmp(const char *nenv, const char *name);

/* env2.c */
char *info_cpy(char *name, char *value);
void set_environ(char *name, char *value, data_shell *datash);
int _setenviron(data_shell *datash);
int _unsetenviron(data_shell *datash);

/* cd.c */
void cd_parent(data_shell *datash);
void change_dir(data_shell *datash);
void cd_prev(data_shell *datash);
void cd_home(data_shell *datash);

/* cd_shell.c */
int cd_current(data_shell *datash);

/* get_builtin */
int (*_getbuiltin(char *cmd))(data_shell *datash);

/* _exit.c */
int shell_exit(data_shell *datash);

/* aux_stdlib.c */
int _getlen(int n);
char *_itos(int n);
int _stoi(char *s);

/* aux_error2.c */
char *string_cat_cd(data_shell *, char *, char *, char *);
char *get_error_cd(data_shell *datash);
char *not_found_error(data_shell *datash);
char *exit_error(data_shell *datash);

/* aux_error1.c */
char *error_get_alias(char **args);
char *environ_error(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *path_error(data_shell *datash);


/* get_error.c */
int _geterror(data_shell *datash, int eval);

/* get_sigint.c */
void _getsigint(int sig);

/* aux_help.c */
void env_help(void);
void setenv_help(void);
void unsetenv_help(void);
void general_help(void);
void exit_help(void);

/* aux_help2.c */
void _help(void);
void alias_help(void);
void cd_help(void);

/* get_help.c */
int _gethelp(data_shell *datash);

#endif
