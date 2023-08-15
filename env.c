# include "main.h"

/**
 * print_env - print the environment variable
 */
void print_env(void)
{
    unsigned int i = 0;

    while (environ[i])
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
}