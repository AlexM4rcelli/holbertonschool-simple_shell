# include "main.h"

# include "main.h"


int my_env(void);
int my_exit(int status);

/**
 * main - Entry point of the shell.
 *
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: Always 0.
 */


int main(int argc, char *argv[])
{
	char *buffer = NULL, *path = NULL;
	char **tokens = NULL;
	int count = 0, status = 0;

	while (status >= 0)
	{
		count++;
		buffer = print_prompt(status);
		if (!buffer)
			break;
		if (strspn(buffer, " \t\n\r") == strlen(buffer))
		{
			free(buffer);
			continue;
		}
		if (strcmp(buffer, "env") == 0)
			status = my_env();
		else if (feof(stdin) || strcmp(buffer, "exit") == 0)
		{
			free(buffer);
			my_exit(status);
		}
		else
		{
			tokens = parser(buffer, " \t\n\r");
			if (tokens)
			{
				path = _getenv("PATH");
				status = create_process(argv[0], tokens, count, path);
				free_all(tokens);
			}
		}
		free(buffer);
	}
	(void)argc;
	free(path);
	return (status);
}

/**
 * my_env - prints the environment variables
 *
 * Return: true
 */

int my_env(void)
{
	char **env_ptr = environ;

	while (*env_ptr)
	{
		write(STDOUT_FILENO, *env_ptr, strlen(*env_ptr));
		write(STDOUT_FILENO, "\n", 1);
		env_ptr++;
	}

	return (0);
}


/**
 * my_exit - exit fo the current shell
 *
 * Return: false
 */

int my_exit(int status)
{
	_Exit(status);
}
