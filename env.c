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
	size_t str_len = strlen(str);

	if (!str || !environ)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(str, environ[i], str_len) == 0 && environ[i][str_len] == '=')
			return (environ[i] + str_len + 1);
	}

	return (NULL);
}
