	# include "main.h"


/**
 * print_prompt - Display the shell prompt and read user input.
 * @status: status of the process
 *
 * Return: Pointer to the input buffer.
 */
char *print_prompt(int status)
{
	ssize_t prompt;
	char *buffer = NULL;
	size_t buffsize = 0;

	if (isatty(STDIN_FILENO) == 1)
		write(STDOUT_FILENO, "$ ", 2);

	prompt = getline(&buffer, &buffsize, stdin);

	if (prompt == -1)
	{
		if (buffer)
			free(buffer);
		exit(status);
	}
	if (buffer[prompt - 1] == '\n')
	{
		buffer[prompt - 1] = '\0';
		prompt--;
	}
	return (buffer);
}

/**
 * parser - Tokenize a string based on a separator.
 * @str: The string to be tokenized.
 * @separator: The separator used for tokenization.
 *
 * Return: An array of tokens.
 */
char **parser(char *str, char *separator)
{
	char **tokens = NULL, *token = NULL, *aux = NULL;
	int i, count = 0, j;


	if (!str)
		return (NULL);
	for (i = 0; str[i]; i++)
	{
		for (j = 0; separator[j]; j++)
		{
			if (str[i] == separator[j] || str[i + 1] == '\0')
				count++;
		}
	}
	count++;
	tokens = malloc(count * sizeof(char *));
	if (!tokens)
	{
		perror("Unable to malloc space\n");
		return (NULL);
	}
	aux = strdup(str);
	token = strtok(aux, separator);
	for (i = 0; token; i++)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("Unable to malloc space\n");
			free_all(tokens);
			free(aux);
			return (NULL);
		}
		token = strtok(NULL, separator);
	}
	tokens[i] = NULL;
	free(aux);
	return (tokens);
}

/**
 * search_cmd - Search for a command in the directories specified by PATH.
 * @cmd: The command to search for.
 * @path: the actual PATH variable.
 *
 * Return: The full path to the command if found, otherwise NULL.
*/

char *search_cmd(char *cmd, char *path)
{
	char *full_path = NULL;
	char **directories = NULL;
	int i;

	if (!path || strlen(path) == 0)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (strdup(cmd));
	directories = parser(path, ":");
	if (!directories)
		return (NULL);
	for (i = 0; directories[i]; i++)
	{
		full_path = calloc(strlen(directories[i]) + strlen(cmd) + 2, sizeof(char));
		if (full_path)
		{
			strcat(full_path, directories[i]);
			strcat(full_path, "/");
			strcat(full_path, cmd);
			if (access(full_path, F_OK) == 0)
			{
				free_all(directories);
				return (full_path);
			}
			free(full_path);
		}
		else
		{
			perror("Unable to malloc space\n");
			free_all(directories);
			return (NULL);
		}
	}
	free_all(directories);
	return (NULL);
}

/**
 * create_process - Create and execute a new process for a given command.
 * @buff: An array of strings containing the command and its arguments.
 * @count: The command count for error reporting.
 * @shell: the name of the shell
 * @path: actual path
 * Return: status
 */

int create_process(char *shell, char **buff, int count, char *path)
{
	char *full_path = search_cmd(buff[0], path);
	pid_t pid;
	int status = 0;

	if (!full_path && (!path || strlen(path) == 0))
	{
		if (access(buff[0], F_OK) == 0)
			full_path = strdup(buff[0]);
		else
		{
			fprintf(stderr, "%s: %d: %s: not found\n", shell, count, buff[0]);
			return (127);
		}
	}
	if (!full_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", shell, count, buff[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		perror("Can't fork");
	else if (pid == 0)
	{
		execve(full_path, buff, environ);
		perror("Error in execve");
		free_all(buff);
		free(full_path);
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && ((WEXITSTATUS(status)) != 0))
	{
		free(full_path);
		return (WEXITSTATUS(status));
	}
	free(full_path);
	return (status);
}
