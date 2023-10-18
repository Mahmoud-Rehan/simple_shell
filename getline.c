#include "main.h"

/**
 * _bringline - Assigns the line var.
 * @lineptr: Buffer that store the input.
 * @buffer: Str that is been called to line.
 * @n: Line size.
 * @j: Buffer size.
 */

void _bringline(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;

		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;

		*lineptr = buffer;
	}
	else
	{
		string_cpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _getline - Read inpt from stream.
 * @lineptr: buffer that stores the input.
 * @n: Lineptr size.
 * @stream: stream to read from.
 * Return: The number of bytes.
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);

	input = 0;
	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);

		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = reallocate(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	_bringline(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
