# include "main.h"

/**
 * free_all - frees a array of arrays
 * @array: array to free
 * @str: string to free
 */

void free_all(char **array)
{
	int i;

	if (array)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);
		free(array);
	}
}
