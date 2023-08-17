# include "main.h"

void free_all(char **array, char *str)
{
	int i;

	if (array)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);
		free(array);
	}
	if (str)
		free(str);
}
