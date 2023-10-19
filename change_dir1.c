#include "main.h"

/**
 * cd_parent - Cd to the parent directory.
 * @data: Data.
 */

void cd_parent(shell_data *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = string_dup(pwd);
	set_environ("OLDPWD", cp_pwd, data);
	dir = data->arguments[1];

	if (string_cmp(".", dir) == 0)
	{
		set_environ("PWD", cp_pwd, data);
		free(cp_pwd);
		return;
	}
	if (string_cmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	string_rev(cp_strtok_pwd);
	cp_strtok_pwd = string_tok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = string_tok(NULL, "\0");
		if (cp_strtok_pwd != NULL)
			string_rev(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_environ("PWD", cp_strtok_pwd, data);
	}
	else
	{
		chdir("/");
		set_environ("PWD", "/", data);
	}
	data->stat = 0;
	free(cp_pwd);
}

/**
 * change_dir - Cd to a given directory.
 * @data: Data.
 */

void change_dir(shell_data *data)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));
	dir = data->arguments[1];

	if (chdir(dir) == -1)
	{
		_geterror(data, 2);
		return;
	}

	cp_pwd = string_dup(pwd);
	set_environ("OLDPWD", cp_pwd, data);
	cp_dir = string_dup(dir);
	set_environ("PWD", cp_dir, data);
	free(cp_pwd);
	free(cp_dir);
	data->stat = 0;
	chdir(dir);
}

/**
 * cd_prev - Cd to the previous directory.
 * @data: Data.
 */

void cd_prev(shell_data *data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = string_dup(pwd);
	p_oldpwd = _getenviron("OLDPWD", data->env);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = string_dup(p_oldpwd);

	set_environ("OLDPWD", cp_pwd, data);

	if (chdir(cp_oldpwd) == -1)
		set_environ("PWD", cp_pwd, data);
	else
		set_environ("PWD", cp_oldpwd, data);

	p_pwd = _getenviron("PWD", data->env);
	write(STDOUT_FILENO, p_pwd, string_len(p_pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(cp_pwd);

	if (p_oldpwd)
		free(cp_oldpwd);

	data->stat = 0;
	chdir(p_pwd);
}

/**
 * cd_home - Cd to home directory.
 * @data: Data.
 */

void cd_home(shell_data *data)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = string_dup(pwd);
	home = _getenviron("HOME", data->env);

	if (home == NULL)
	{
		set_environ("OLDPWD", p_pwd, data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		_geterror(data, 2);
		free(p_pwd);
		return;
	}

	set_environ("OLDPWD", p_pwd, data);
	set_environ("PWD", home, data);
	free(p_pwd);
	data->stat = 0;
}
