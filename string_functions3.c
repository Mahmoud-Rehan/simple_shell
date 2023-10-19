#include "main.h"

/**
 * string_dup - Duplicates a str in the heap memory.
 * @str: String.
 * Return: String.
 */

char *string_dup(const char *str)
{
	char *new;
	size_t len;

	len = string_len(str);
	new = malloc(sizeof(char) * (len + 1));

	if (new == NULL)
	{
		return (NULL);
	}

	memory_cpy(new, str, len + 1);

	return (new);
}

/**
 * string_len - Gets lenght of a string.
 * @str: String.
 * Return: Integer.
 */

int string_len(const char *str)
{
	int len;

	for (len = 0; str[len] != 0; len++)
	{
	}

	return (len);
}

/**
 * chars_cmp - Compare chars of strings.
 * @s: String.
 * @delim: Delimiter.
 * Return: 1 if equals or 0 if not.
 */

int chars_cmp(char s[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; s[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (s[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}

	if (i == k)
	{
		return (1);
	}
	return (0);
}

/**
 * string_tok - Tokinize a string by a delimiter.
 * @s: String.
 * @delim: Delimiter.
 * Return: String.
 */

char *string_tok(char s[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (s != NULL)
	{
		if (chars_cmp(s, delim))
			return (NULL);
		splitted = s;
		i = string_len(s);
		str_end = &s[i];
	}
	str_start = splitted;

	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);

	return (str_start);
}

/**
 * is_digit - Checks if string passed is a number.
 * @str: String.
 * Return: 1 if string is a number or 0 if not.
 */

int is_digit(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < 48 || str[i] > 57)
		{
			return (0);
		}
	}

	return (1);
}
