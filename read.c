#include "main.h"

/**
 * _readline - Reads the input string.
 * @i_eof: return value of getline.
 * Return: string.
 */

char *_readline(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
