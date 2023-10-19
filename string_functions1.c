#include "main.h"

/**
 * string_rev - Reverses a string.
 * @str: String.
 */

void string_rev(char *str)
{
	int count = 0, i, j;
	char *string, temp;

	while (count >= 0)
	{
		if (str[count] == '\0')
		{
			break;
		}
		count++;
	}

	string = str;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(string + j);
			*(string + j) = *(string + (j - 1));
			*(string + (j - 1)) = temp;
		}
	}
}
