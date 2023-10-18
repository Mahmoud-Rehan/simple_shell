#include "main.h"

/**
 * string_cat - Concatenates two strings.
 * @dest: Pointer the dest of the copied str.
 * @src: Pointer the source of str.
 * Return: String.
 */

char *string_cat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * string_cpy - Copies the string pointed to by src.
 * @dest: Pointer the dest of the copied str.
 * @src: Pointer the source of str.
 * Return: String.
 */

char *string_cpy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}

	dest[a] = '\0';

	return (dest);
}

/**
 * string_cmp - Compares two strings.
 * @s1: String compared.
 * @s2: String compared.
 * Return: 0 Always.
 */

int string_cmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
	{
		return (1);
	}
	if (s1[i] < s2[i])
	{
		return (-1);
	}

	return (0);
}

/**
 * string_chr - locates a char in a string.
 * @s: String.
 * @c: character.
 * Return: Pointer.
 */

char *string_chr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
	{
		if (*(s + i) == c)
		{
			return (s + i);
		}
	}

	if (*(s + i) == c)
	{
		return (s + i);
	}

	return ('\0');
}

/**
 * string_spn - Gets the length of a prefix substring.
 * @s: initial segment.
 * @accept: Bytes Accepted.
 * Return: Integer.
 */

int string_spn(char *s, char *accept)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;

		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
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
