#include "main.h"

/**
 * _readline - Reads the input string.
 * @return_val: return value of getline.
 * Return: string.
 */

char *_readline(int *return_val)
{
	char *input = NULL;
	size_t bufsize = 0;

	*return_val = getline(&input, &bufsize, stdin);

	return (input);
}
