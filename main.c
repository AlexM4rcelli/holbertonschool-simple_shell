# include "main.h"

# include "main.h"

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
		path = _getenv("PATH");
		if (!buffer)
			break;
		if (strspn(buffer, " \t\n\r") == strlen(buffer))
		{
			free(buffer);
			continue;
		}
		else if (feof(stdin))
			my_exit(argv[0], count, tokens, buffer, status);
		else
		{
			tokens = parser(buffer, " \t\n\r");
			if (tokens)
			{
				status = execute_command(argv[0], tokens, count, path, buffer, status);
				free_all(tokens);
			}
		}
		free(buffer);
	}
	(void)argc;
	free(path);
	return (status);
}
