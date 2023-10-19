#include "main.h"

/**
 * environ_cmp - Compares environ variable names.
 * @env_name: The environment variable.
 * @input: Name passed.
 * Return: Integer.
 */

int environ_cmp(const char *env_name, const char *input)
{
	int i;

	for (i = 0; env_name[i] != '='; i++)
	{
		if (env_name[i] != input[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenviron - Get an environment variable.
 * @env_name: The environment variable name.
 * @_env: environment variable.
 * Return: String or NULL.
 */

char *_getenviron(const char *env_name, char **_env)
{
	char *ptr_env;
	int i, mov;

	ptr_env = NULL;
	mov = 0;

	for (i = 0; _env[i]; i++)
	{
		mov = environ_cmp(_env[i], env_name);

		if (mov)
		{
			ptr_env = _env[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _environ - Prints the evironment variables.
 * @data: Data.
 * Return: 1 on success.
 */

int _environ(shell_data *data)
{
	int i, j;

	for (i = 0; data->env[i]; i++)
	{

		for (j = 0; data->env[i][j]; j++)
			;

		write(STDOUT_FILENO, data->env[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->stat = 0;

	return (1);
}
