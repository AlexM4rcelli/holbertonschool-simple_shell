#include "main.h"

/**
 * _getenv - Get the value of an environment variable.
 * @str: The name of the environment variable.
 *
 * Return: The value of the environment variable.
 */

char *_getenv(char *str)
{
    int i;
    char **parsed = NULL, *value = NULL;

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