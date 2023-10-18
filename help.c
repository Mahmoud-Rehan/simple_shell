#include "main.h"

/**
 * _gethelp - Get help messages according to builtin.
 * @datash: Data.
 * Return: Integer.
*/

int _gethelp(data_shell *datash)
{

	if (datash->args[1] == 0)
		general_help();
	else if (string_cmp(datash->args[1], "setenv") == 0)
		setenv_help();
	else if (string_cmp(datash->args[1], "env") == 0)
		env_help();
	else if (string_cmp(datash->args[1], "unsetenv") == 0)
		unsetenv_help();
	else if (string_cmp(datash->args[1], "help") == 0)
		_help();
	else if (string_cmp(datash->args[1], "exit") == 0)
		exit_help();
	else if (string_cmp(datash->args[1], "cd") == 0)
		cd_help();
	else if (string_cmp(datash->args[1], "alias") == 0)
		alias_help();
	else
		write(STDERR_FILENO, datash->args[0],
		      string_len(datash->args[0]));

	datash->status = 0;

	return (1);
}
