#include "main.h"

/**
 * cd_current - Cd to the current directory.
 * @datash: Data.
 * Return: 1 if success.
 */

int cd_current(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = string_cmp("$HOME", dir);
		ishome2 = string_cmp("~", dir);
		isddash = string_cmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_home(datash);
		return (1);
	}

	if (string_cmp("-", dir) == 0)
	{
		cd_prev(datash);
		return (1);
	}

	if (string_cmp(".", dir) == 0 || string_cmp("..", dir) == 0)
	{
		cd_parent(datash);
		return (1);
	}

	change_dir(datash);

	return (1);
}
