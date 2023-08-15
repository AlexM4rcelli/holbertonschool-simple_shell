# include "main.h"

int my_env(void);
int my_exit(void);

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */

int main(void) {
    char *buffer = NULL;
    char **tokens = NULL;
    int i, count = 0;

    while (1) {
        count++;
        buffer = print_prompt();

        if (!buffer)
            break;

        if (strcmp(buffer, "env") == 0)
        {
            my_env();
            continue;
        }

        if (feof(stdin) || strcmp(buffer, "exit") == 0)
        {
            my_exit();
            break;
        }

        if (strcmp(buffer, "") == 0)
        {
            free(buffer);
            continue;
        }

        tokens = parser(buffer, " \t\n");

        if (tokens)
        {
            create_process(tokens, count);

            for (i = 0; tokens[i]; i++)
                free(tokens[i]);
            free(tokens);
        }
        free(buffer);
    }
    free(buffer);
    return (0);
}

/**
 * my_env - prints the environment variables
 *
 * Return: true
 */

int my_env(void)
{
    int i;

    for (i = 0; environ[i]; i++)
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDIN_FILENO, "\n", 1);
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
