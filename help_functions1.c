#include "main.h"

/**
 * _help - Help info for the builtin help.
 */

void _help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, string_len(help));

	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, string_len(help));

	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, string_len(help));
}

/**
 * alias_help - Help info for the builtin alias.
 */

void alias_help(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, string_len(help));

	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, string_len(help));
}

/**
 * cd_help - Help info for the builtin alias.
 */

void cd_help(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, string_len(help));

	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, string_len(help));
}
