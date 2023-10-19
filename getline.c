#include "main.h"

/**
 * _bringline - Assigns the line var.
 * @buffer_ptr: Buffer that store the input.
 * @line_size: Str that is been called to line.
 * @buf: Line size.
 * @size: Buffer size.
 */

void _bringline(char **buffer_ptr, size_t *line_size, char *buf, size_t size)
{

	if (*buffer_ptr == NULL)
	{
		if  (size > BUFFER_SIZE)
			*line_size = size;

		else
			*line_size = BUFFER_SIZE;

		*buffer_ptr = buf;
	}
	else if (*line_size < size)
	{
		if (size > BUFFER_SIZE)
			*line_size = size;
		else
			*line_size = BUFFER_SIZE;

		*buffer_ptr = buf;
	}
	else
	{
		string_cpy(*buffer_ptr, buf);
		free(buf);
	}
}

/**
 * _getline - Read inpt from stream.
 * @buffer_ptr: buffer that stores the input.
 * @size: Lineptr size.
 * @stream: stream to read from.
 * Return: The number of bytes.
 */

ssize_t _getline(char **buffer_ptr, size_t *size, FILE *stream)
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
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
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
		if (input >= BUFFER_SIZE)
			buffer = reallocate(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	_bringline(buffer_ptr, size, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
