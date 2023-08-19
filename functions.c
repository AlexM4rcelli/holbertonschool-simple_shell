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
	* @full_path: the actual PATH variable.
	*
	* Return: The full path to the command if found, otherwise NULL.
	*/

	char *search_cmd(char *cmd, char *full_path)
	{
		char *path = NULL;
		char **directories = NULL;
		int i;

		if (!full_path || strlen(full_path) == 0)
			return (NULL);
		directories = parser(full_path, ":");
		if (!directories)
			return (NULL);

		for (i = 0; directories[i]; i++)
		{
			path = calloc(strlen(directories[i]) + strlen(cmd) + 2, sizeof(char));
			if (path)
			{
				strcat(path, directories[i]), strcat(path, "/"), strcat(path, cmd);
				if (access(path, F_OK) == 0)
				{
					free_all(directories);
					return (path);
				}
				free(path);
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
	* Return: status
	*/

	int create_process(char *shell, char **buff, int count, char *path)
	{
		char *full_path = NULL;
		struct stat path_stat;
		pid_t pid;
		int status = 0;

		if (!path || strlen(path) == 0)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", shell, count, buff[0]);
			return (127);
		}
		stat(path, &path_stat);
		if (access(buff[0], F_OK) == 0 && (path_stat.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		{
			pid = fork();
			if (pid == -1)
				perror("Can't fork");
			else if (pid == 0)
			{
				execve(buff[0], buff, environ);
				perror("Error in execve");
				free_all(buff);
				free(full_path);
				exit(127);
			}
			waitpid(pid, &status, 0);
		}
		else
		{
			full_path = search_cmd(buff[0], path);
			if (full_path)
				status = execute_with_path(buff, full_path);
			else
				{
					fprintf(stderr, "%s: %s: %d: not found\n", shell, buff[0], count);
					status = 127;
				}
		}
		return (status);
	}

	/**
	* execute_with_path - Execute a command using the full path.
	* @buff: An array of strings containing the command and its arguments.
	* @full_path: The full path to the command.
	*
	* Return: status
	*/
	int execute_with_path(char **buff, char *full_path)
	{
		int status = 0;
		pid_t pid = fork();


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
		free(full_path);
		return (status);
	}
