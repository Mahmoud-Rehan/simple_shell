#include "main.h"

/**
 * is_current_dir - Checks ":" if is in the current directory.
 * @path: Pointer char.
 * @i: Pointer of index.
 * Return: 1 or 0.
 */

int is_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
	{
		return (1);
	}

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
	{
		*i += 1;
	}

	return (0);
}

/**
 * which_cmd - Locates a command.
 * @cmd: Command.
 * @_environ: Environment variable.
 * Return: Command location.
 */

char *which_cmd(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenviron("PATH", _environ);
	if (path)
	{
		ptr_path = string_dup(path);
		len_cmd = string_len(cmd);
		token_path = string_tok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = string_len(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			string_cpy(dir, token_path);
			string_cat(dir, "/");
			string_cat(dir, cmd);
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
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);

	return (NULL);
}

/**
 * is_exec - Checks if is an executable.
 * @datash: Data.
 * Return: Integer.
 */

int is_exec(data_shell *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];

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

	_geterror(datash, 127);

	return (-1);
}

/**
 * command_error_check - Checks if user has permissions to access.
 * @dir: Destination dir.
 * @datash: Data.
 * Return: 1 or 0.
 */

int command_error_check(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		_geterror(datash, 127);
		return (1);
	}

	if (string_cmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			_geterror(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			_geterror(datash, 126);
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

int execute_command(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_exec(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = which_cmd(datash->args[0], datash->_environ);
		if (command_error_check(dir, datash) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = which_cmd(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];

		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	datash->status = state / 256;

	return (1);
}
