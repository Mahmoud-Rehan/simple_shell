#include "main.h"

/**
 * info_cpy - Copies info to create
 * a new env or alias.
 * @var_name: The name of env or alias.
 * @var_value: The value of env or alias
 * Return: The new env or alias.
 */

char *info_cpy(char *var_name, char *var_value)
{
	char *new;
	int len_name, len_value, len;

	len_name = string_len(var_name);
	len_value = string_len(var_value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	string_cpy(new, var_name);
	string_cat(new, "=");
	string_cat(new, var_value);
	string_cat(new, "\0");

	return (new);
}

/**
 * set_environ - Sets an env variable.
 * @env_name: Environment variable name.
 * @env_value: Environment variable value.
 * @data: Data.
 */

void set_environ(char *env_name, char *env_value, shell_data *data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; data->env[i]; i++)
	{
		var_env = string_dup(data->env[i]);
		name_env = string_tok(var_env, "=");

		if (string_cmp(name_env, env_name) == 0)
		{
			free(data->env[i]);
			data->env[i] = info_cpy(name_env, env_value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	data->env = realloc_dptr(data->env, i,
			sizeof(char *) * (i + 2));
	data->env[i] = info_cpy(env_name, env_value);
	data->env[i + 1] = NULL;
}

/**
 * _setenviron - Compares env variable names
 * @data: Data.
 * Return: 1 on success.
 */

int _setenviron(shell_data *data)
{

	if (data->arguments[1] == NULL || data->arguments[2] == NULL)
	{
		_geterror(data, -1);
		return (1);
	}
	set_environ(data->arguments[1], data->arguments[2], data);

	return (1);
}

/**
 * _unsetenviron - Deletes an environment variable.
 * @data: Data.
 * Return: 1 on success.
 */

int _unsetenviron(shell_data *data)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (data->arguments[1] == NULL)
	{
		_geterror(data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data->env[i]; i++)
	{
		var_env = string_dup(data->env[i]);
		name_env = string_tok(var_env, "=");

		if (string_cmp(name_env, data->arguments[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		_geterror(data, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; data->env[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = data->env[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(data->env[k]);
	free(data->env);
	data->env = realloc_environ;
	return (1);
}
