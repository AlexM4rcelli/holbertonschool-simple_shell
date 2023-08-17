# include "main.h"

int my_env(void);
int my_exit(void);

/**
 * main - Entry point of the shell.
 *
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	char *buffer = NULL;
	char **tokens = NULL;
	int i, count = 0, status = 0;

	while (status == 0)
	{
		count++;
		buffer = print_prompt();

		if (!buffer)
			break;

		if (strspn(buffer, " \t\n\r") == strlen(buffer))
		{
			free(buffer);
			continue;
		}

		if (strcmp(buffer, "env") == 0)
			my_env();
		else if (feof(stdin) || strcmp(buffer, "exit") == 0)
		{
			status = my_exit();
		}
		else
		{
			tokens = parser(buffer, " \t\n\r");
			if (tokens)
			{
				status = create_process(argv[0], tokens, count);
				for (i = 0; tokens[i]; i++)
					free(tokens[i]);
				free(tokens);
			}
		}
		free(buffer);
	}

	(void)argc;
	return (0);
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

int my_exit(void)
{
	return (-1);
}
