#include "main.h"

/**
 * env_help - Help info the builtin env.
 */

void env_help(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, string_len(help));

	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, string_len(help));
}

/**
 * setenv_help - Help info for the builtin setenv.
 */

void setenv_help(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, string_len(help));

	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, string_len(help));

	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, string_len(help));
}

/**
 * unsetenv_help - Help info for the builtin unsetenv.
 */

void unsetenv_help(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, string_len(help));

	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, string_len(help));
}


/**
 * general_help - Help info for the help builtin.
 */

void general_help(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, string_len(help));

	help = "These commands are defined internally.Type 'help' to see the list";
	write(STDOUT_FILENO, help, string_len(help));

	help = "Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, string_len(help));

	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, string_len(help));

	help = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, string_len(help));

	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, string_len(help));

	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, string_len(help));
}

/**
 * exit_help - Help info fot the builint exit.
 */

void exit_help(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, string_len(help));

	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, string_len(help));

	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, string_len(help));
}
