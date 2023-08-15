# include "main.h"

/**
 * print_prompt - Display the shell prompt and read user input.
 *
 * Return: Pointer to the input buffer.
 */

char *print_prompt(void)
{
    ssize_t prompt;
    char *buffer = NULL;
    size_t buffsize = 0;

    if (isatty(STDIN_FILENO) == 1)
            write(STDOUT_FILENO,"$ ", 2);

    prompt = getline(&buffer, &buffsize, stdin);

    if (prompt == -1)
    {
        if (buffer)
            free(buffer);
        exit(0);
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

    if (str)
    {
        for (i = 0; str[i]; i++)
        {
            for (j = 0; separator[j]; j++)
            {
                if (str[i] == separator[j] || str[i + 1] == '\0')
                    count++;
            }
        }

        count ++;
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
                for (j = 0; j < i; j++)
                    free(tokens[j]);
                free(tokens);
                free(aux);
                return NULL;
            }
            token = strtok(NULL, separator);
        }
        tokens[i] = NULL;

        free(aux);
    }
    return (tokens);
}

/**
 * search_cmd - Search for a command in the directories specified by PATH.
 * @cmd: The command to search for.
 *
 * Return: The full path to the command if found, otherwise NULL.
 */

char *search_cmd(char *cmd)
{
    char *full_path = _getenv("PATH="), *path = NULL;
    char **directories = parser(full_path, ":");
    int i;

    if (cmd && full_path && directories)
    {
        if (access(cmd, F_OK | X_OK) == 0)
        {
            free(full_path);
            free(directories);
            return (strdup(cmd));
        }

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
            else
                perror("Unable to malloc space\n");
        }
        for (i = 0; directories[i]; i++)
            free(directories[i]);
        free(directories);
        free(full_path);
    }
    return (NULL);
}

/**
 * create_process - Create and execute a new process for a given command.
 * @buff: An array of strings containing the command and its arguments.
 * @count: The command count for error reporting.
 */

void create_process(char *shell, char **buff, int count)
{
    int status = 0;
    char *full_path = NULL;
    struct stat path_stat;
    pid_t pid;

    /* Check if the input is a valid path*/
    if (stat(buff[0], &path_stat) == 0 && (path_stat.st_mode & S_IXUSR))
    {
        /* Execute the valid path*/
        pid = fork();
        if (pid == -1)
            perror("Can't fork");
        else if (pid == 0)
        {
            execve(buff[0], buff, environ);
            perror("Error in execve");
            free(buff);
            exit(0);
        }
        waitpid(pid, &status, 0);
    }
    else
    {
        /* Search for the command in PATH*/
        full_path = search_cmd(buff[0]);
        if (full_path)
        {
            pid = fork();
            if (pid == -1)
                perror("Can't fork");
            else if (pid == 0)
            {
                execve(full_path, buff, environ);
                perror("Error in execve");
                free(buff);
                free(full_path);
                exit(0);
            }
            waitpid(pid, &status, 0);
            free(full_path);
        }
        else
            not_found(shell, buff[0], count);
    }
}
