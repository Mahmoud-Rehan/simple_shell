#include "main.h"

/**
 * freedata - Frees data.
 * @data: Data.
 */

void freedata(shell_data *data)
{
	unsigned int i;

	for (i = 0; data->env[i]; i++)
	{
		free(data->env[i]);
	}

	free(data->env);
	free(data->pid);
}

/**
 * setdata - Initialize data.
 * @data: Data.
 * @argv: argument vector.
 */

void setdata(shell_data *data, char **argv)
{
	unsigned int i;

	data->argv = argv;
	data->input = NULL;
	data->arguments = NULL;
	data->stat = 0;
	data->count = 1;

	for (i = 0; environ[i]; i++)
		;

	data->env = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data->env[i] = string_dup(environ[i]);
	}

	data->env[i] = NULL;
	data->pid = _itos(getpid());
}

/**
 * main - Main function.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success.
 */

int main(int argc, char **argv)
{
	shell_data data;
	(void) argc;

	signal(SIGINT, _getsigint);
	setdata(&data, argv);
	loop(&data);
	freedata(&data);

	if (data.stat < 0)
	{
		return (255);
	}

	return (data.stat);
}
