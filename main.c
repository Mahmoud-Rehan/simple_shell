#include "main.h"

/**
 * freedata - Frees data.
 * @datash: Data.
 */

void freedata(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * setdata - Initialize data.
 * @datash: Data.
 * @av: argument vector.
 */

void setdata(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = string_dup(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = _itos(getpid());
}

/**
 * main - Main function.
 * @ac: Argument count.
 * @av: Argument vector
 * Return: 0 on success.
 */

int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, _getsigint);
	setdata(&datash, av);
	loop(&datash);
	freedata(&datash);

	if (datash.status < 0)
		return (255);

	return (datash.status);
}
