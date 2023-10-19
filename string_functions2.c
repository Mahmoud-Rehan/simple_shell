#include "main.h"

/**
 * string_cat - Concatenates two strings.
 * @str1: Pointer the dest of the copied str.
 * @str2: Pointer the source of str.
 * Return: String.
 */

char *string_cat(char *str1, const char *str2)
{
	int i;
	int j;

	for (i = 0; str1[i] != '\0'; i++)
		;

	for (j = 0; str2[j] != '\0'; j++)
	{
		str1[i] = str2[j];
		i++;
	}

	str1[i] = '\0';

	return (str1);
}

/**
 * string_cpy - Copies the string pointed to by src.
 * @str1: Pointer the dest of the copied str.
 * @str2: Pointer the source of str.
 * Return: String.
 */

char *string_cpy(char *str1, char *str2)
{

	size_t a;

	for (a = 0; str2[a] != '\0'; a++)
	{
		str1[a] = str2[a];
	}

	str1[a] = '\0';

	return (str1);
}

/**
 * string_cmp - Compares two strings.
 * @str1: String compared.
 * @str2: String compared.
 * Return: 0 Always.
 */

int string_cmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;

	if (str1[i] > str2[i])
	{
		return (1);
	}
	if (str1[i] < str2[i])
	{
		return (-1);
	}

	return (0);
}

/**
 * string_chr - locates a char in a string.
 * @str: String.
 * @c: character.
 * Return: Pointer.
 */

char *string_chr(char *str, char c)
{
	unsigned int i = 0;

	for (; *(str + i) != '\0'; i++)
	{
		if (*(str + i) == c)
		{
			return (str + i);
		}
	}

	if (*(str + i) == c)
	{
		return (str + i);
	}

	return ('\0');
}

/**
 * string_spn - Gets the length of a prefix substring.
 * @str: initial segment.
 * @accept_bytes: Bytes Accepted.
 * Return: Integer.
 */

int string_spn(char *str, char *accept_bytes)
{
	int i, j, bool;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		bool = 1;

		for (j = 0; *(accept_bytes + j) != '\0'; j++)
		{
			if (*(str + i) == *(accept_bytes + j))
			{
				bool = 0;
				break;
			}
		}

		if (bool == 1)
		{
			break;
		}
	}

	return (i);
}
