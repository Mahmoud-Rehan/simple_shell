#include "main.h"

/**
 * environ_cmp - Compares environ variable names.
 * @nenv: The environment variable.
 * @name: Name passed.
 * Return: Integer.
 */

int environ_cmp(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenviron - Get an environment variable.
 * @name: The environment variable name.
 * @_environ: environment variable.
 * Return: Value of the environment variable if is found.
 * or NULL.
 */

char *_getenviron(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	ptr_env = NULL;
	mov = 0;

	for (i = 0; _environ[i]; i++)
	{
		mov = environ_cmp(_environ[i], name);

		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _environ - Prints the evironment variables.
 * @datash: Data.
 * Return: 1 on success.
 */

int _environ(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
