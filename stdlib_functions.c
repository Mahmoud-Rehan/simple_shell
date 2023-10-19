#include "main.h"

/**
 * _getlen - Get the lenght of a number.
 * @num: Number.
 * Return: Integer.
 */

int _getlen(int num)
{
	unsigned int n1;
	int lenght = 1;

	if (num < 0)
	{
		lenght++;
		n1 = num * -1;
	}
	else
	{
		n1 = num;
	}

	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}

/**
 * _itos - Converts int to string.
 * @num: Number
 * Return: String.
 */

char *_itos(int num)
{
	unsigned int n1;
	int lenght = _getlen(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));

	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (num < 0)
	{
		n1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = num;
	}

	lenght--;

	do {
		*(buffer + lenght) = (n1 % 10) + '0';
		n1 = n1 / 10;
		lenght--;
	}

	while (n1 > 0)
		;
	return (buffer);
}

/**
 * _stoi - Converts a string to an integer.
 * @str: String.
 * Return: Integer.
 */

int _stoi(char *str)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(str + count) != '\0')
	{
		if (size > 0 && (*(str + count) < '0' || *(str + count) > '9'))
			break;

		if (*(str + count) == '-')
			pn *= -1;

		if ((*(str + count) >= '0') && (*(str + count) <= '9'))
		{
			if (size > 0)
				m *= 10;

			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(str + i) - 48) * m);
		m /= 10;
	}

	return (oi * pn);
}
