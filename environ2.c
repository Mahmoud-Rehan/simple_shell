#include "main.h"

/**
 * info_cpy - Copies info to create
 * a new env or alias.
 * @name: The name of env or alias.
 * @value: The value of env or alias
 * Return: The new env or alias.
 */

char *info_cpy(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = string_len(name);
	len_value = string_len(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	string_cpy(new, name);
	string_cat(new, "=");
	string_cat(new, value);
	string_cat(new, "\0");

	return (new);
}

/**
 * set_environ - Sets an env variable.
 * @name: Environment variable name.
 * @value: Environment variable value.
 * @datash: Data.
 */

void set_environ(char *name, char *value, data_shell *datash)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = string_dup(datash->_environ[i]);
		name_env = string_tok(var_env, "=");

		if (string_cmp(name_env, name) == 0)
		{
			free(datash->_environ[i]);
			datash->_environ[i] = info_cpy(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = realloc_dptr(datash->_environ, i,
			sizeof(char *) * (i + 2));
	datash->_environ[i] = info_cpy(name, value);
	datash->_environ[i + 1] = NULL;
}

/**
 * _setenviron - Compares env variable names
 * @datash: Data.
 * Return: 1 on success.
 */

int _setenviron(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		_geterror(datash, -1);
		return (1);
	}
	set_environ(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenviron - Deletes an environment variable.
 * @datash: Data.
 * Return: 1 on success.
 */

int _unsetenviron(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (datash->args[1] == NULL)
	{
		_geterror(datash, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datash->_environ[i]; i++)
	{
		var_env = string_dup(datash->_environ[i]);
		name_env = string_tok(var_env, "=");

		if (string_cmp(name_env, datash->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		_geterror(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; datash->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = datash->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
