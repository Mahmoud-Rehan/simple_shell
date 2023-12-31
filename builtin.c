#include "main.h"

/**
 * _getbuiltin - Builtin that compare the argument cmd with builtin
 * @command: Command line.
 * Return: Function pointer.
 */

int (*_getbuiltin(char *command))(shell_data *)
{
	builtins_t builtin[] = {
		{ "env", _environ },
		{ "exit", shell_exit },
		{ "setenv", _setenviron },
		{ "unsetenv", _unsetenviron },
		{ "cd", cd_current },
		{ "help", _gethelp },
		{ NULL, NULL }
	};

	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (string_cmp(builtin[i].name, command) == 0)
		{
			break;
		}
	}

	return (builtin[i].function);
}
