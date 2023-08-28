# include "main.h"
/*exit - env - help - history - setenv -unsetenv - cd - alias*/

/**
 * my_env - prints the environment variables
 *
 * Return: 0 if environ exists and can print, -1 if not
 */
int my_env(char *shell, int count, char **tokens, char *buffer, int status)
{
	char **env_ptr = environ;

	if (!env_ptr)
		return (-1);

	while (*env_ptr)
	{
		write(STDOUT_FILENO, *env_ptr, strlen(*env_ptr));
		write(STDOUT_FILENO, "\n", 1);
		env_ptr++;
	}
	(void)tokens;
	(void)shell;
	(void)count;
	(void)buffer;
	return (status = 0);
}


/**
 * my_exit - exit fo the current shell
 * @status: value of exit
 * Return: status value
 */
int my_exit(char *shell, int count, char **tokens, char *buffer, int status)
{
	int last_status = status, i, len = 0;

	for (i = 0; tokens[i]; i++)
		len++;

	if (len > 1)
		status = atoi(tokens[1]);
	else
		status = last_status;
	
	free_all(tokens);
	(void)shell;
	(void)count;
	free(buffer);
	_Exit(status);
}

int my_cd(char *shell, int count, char **tokens, char *buffer, int status)
{
	char *dir = NULL, *prev_dir = NULL, *cwd = getcwd(NULL, 0);
	int i, len = 0;
	for (i = 0; tokens[i]; i++)
		len++;
	dir = len > 1 ? tokens[1] : _getenv("HOME");
	prev_dir = !strcmp(dir, "-") ? _getenv("OLDPWD") : NULL;
	
	if (!strcmp(dir, "-"))
	{
		if (prev_dir && !chdir(prev_dir))
		{
			fprintf(stdout, "%s\n", prev_dir);
			setenv("OLDPWD", cwd, 1);
		}
		else
			status = errno;
	}
	else
	{
		if (!chdir(dir))
			setenv("OLDPWD", cwd, 1);
		else
		{
			fprintf(stderr, "%s: %d: cd: can't cd to %s\n", shell, count, dir);
			status = errno;
		}
	}

	free(cwd);
	(void)buffer;
	return (status);
}