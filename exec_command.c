#include "main.h"

/**
 * is_current_dir - Checks ":" if is in the current directory.
 * @path: Pointer char.
 * @n: Pointer of index.
 * Return: 1 or 0.
 */

int is_current_dir(char *path, int *n)
{
	if (path[*n] == ':')
	{
		return (1);
	}

	while (path[*n] != ':' && path[*n])
	{
		*n += 1;
	}

	if (path[*n])
	{
		*n += 1;
	}

	return (0);
}

/**
 * which_cmd - Locates a command.
 * @command: Command.
 * @_env: Environment variable.
 * Return: Command location.
 */

char *which_cmd(char *command, char **_env)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenviron("PATH", _env);
	if (path)
	{
		ptr_path = string_dup(path);
		len_cmd = string_len(command);
		token_path = string_tok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(command, &st) == 0)
					return (command);
			len_dir = string_len(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			string_cpy(dir, token_path);
			string_cat(dir, "/");
			string_cat(dir, command);
			string_cat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = string_tok(NULL, ":");
		}
		free(ptr_path);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);

	return (NULL);
}

/**
 * is_exec - Checks if is an executable.
 * @data: Data.
 * Return: Integer.
 */

int is_exec(shell_data *data)
{
	struct stat st;
	int i;
	char *input;

	input = data->arguments[0];

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;

			i++;
			break;
		}
		else
			break;
	}

	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}

	_geterror(data, 127);

	return (-1);
}

/**
 * command_error_check - Checks if user has permissions to access.
 * @directory: Destination dir.
 * @data: Data.
 * Return: 1 or 0.
 */

int command_error_check(char *directory, shell_data *data)
{
	if (directory == NULL)
	{
		_geterror(data, 127);
		return (1);
	}

	if (string_cmp(data->arguments[0], directory) != 0)
	{
		if (access(directory, X_OK) == -1)
		{
			_geterror(data, 126);
			free(directory);
			return (1);
		}
		free(directory);
	}
	else
	{
		if (access(data->arguments[0], X_OK) == -1)
		{
			_geterror(data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_command - Executes command.
 * @datash: Data.
 * Return: 1 if success.
 */

int execute_command(shell_data *data)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_exec(data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = which_cmd(data->arguments[0], data->env);
		if (command_error_check(dir, data) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = which_cmd(data->arguments[0], data->env);
		else
			dir = data->arguments[0];

		execve(dir + exec, data->arguments, data->env);
	}
	else if (pd < 0)
	{
		perror(data->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	data->stat = state / 256;

	return (1);
}
