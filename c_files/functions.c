# include "main.h"

char *print_prompt(void)
{
    ssize_t prompt;
    char *buffer = NULL;
    size_t buffsize = 0;

    if (isatty(STDIN_FILENO) == 1)
            printf("#cisfun$ ");
            
    prompt = getline(&buffer, &buffsize, stdin);
        
    if (prompt == -1)
    {
        if (buffer)
            free(buffer);
        return (NULL);
    }
    if (buffer[prompt - 1] == '\n')
    {
        buffer[prompt - 1] = '\0';
        prompt--;
    }

    return (buffer);
}

char **parser(char *str, char *separator)
{
    char **tokens = NULL;
    int i, count = 0, j;
    char *token;
    char *aux = strdup(str);

    for (i = 0; str[i]; i++)
    {
        for (j = 0; separator[j]; j++)
        {
            if (str[i] == separator[j] || str[i + 1] == '\0')
                count++;
        }
    }

    count += 1;
    tokens = malloc(count * sizeof(char *));

    if (!tokens)
        return (NULL);

    token = strtok(aux, separator);   
    i = 0;
    while (token)
    {
        tokens[i++] = strdup(token);
        token = strtok(NULL, separator);
    }
    tokens[i] = NULL;

    free(aux);
    return (tokens);
}

char *_getenv(char *str)
{
    int i;
    char **parsed = NULL;
    char *value = NULL;

    for (i = 0; environ[i]; i++)
    {
        if ((strncmp(str, environ[i], strlen(str))) == 0)
        {
            parsed = parser(environ[i], "=");
            value = strdup(parsed[1]);
            for (i = 0; parsed[i]; i++)
                free(parsed[i]);
            free(parsed);
            return (value);
        }
    }

    return (NULL);
}

char *search_cmd(char *cmd)
{
    char *full_path = _getenv("PATH=");
    char *path = NULL;
    char **directories = parser(full_path, ":");
    int i;

    for (i = 0; directories[i]; i++)
    {
        path = (char *)calloc((strlen(directories[i]) + strlen(cmd) + 2), sizeof(char));
        if (path)
        {
            strcat(path, directories[i]);
            strcat(path, "/");
            strcat(path, cmd);
    
            if (access(path, F_OK) == 0)
            {
                if (directories)
                {
                    for (i = 0; directories[i]; i++)
                        free(directories[i]);
                    free(directories);
                }
                free(full_path);
                return (path);
            }
            
            free(path);
        }
    }
    if (directories)
    {
        for (i = 0; directories[i]; i++)
            free(directories[i]);
        free(directories);
    }
    free(full_path);
	return (NULL);
}

pid_t create_process(char **buff)
{
    int status = 0;
    char *full_path = NULL;
    struct stat path_stat;
    pid_t pid = fork();

    if (pid == -1)
        return -1;
	else if (pid == 0)
    {
        if (buff[0][0] == '/')
        {
            if (stat(buff[0], &path_stat) == 0)
            {
                if (path_stat.st_mode & S_IXUSR)
                    execve(buff[0], buff, environ);
                exit(1);
            }
		}
		else
        {
            if ((full_path = search_cmd(buff[0])))
			{
				execve(full_path, buff, environ);
                free(full_path);
                exit(0);
			}
			else
			{
				printf("comand not found %s\n", buff[0]);
				free(buff);
				free(full_path);
				exit(0);
			}
		}
	} else {
		waitpid(pid, &status, 0);
	}
	return pid;
}
