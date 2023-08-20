# include "main.h"

/**
 * free_all - frees a array of arrays
 * @array: array to free
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

/**
 * is_In - compare the absolute path of a file and the curren working directory
 *
 * @file: file to compare;
 * Return: 0 if is in the curr working directory, 1 if not, -1 on error
 */
int is_In(char *file)
{
	char *absolutePath = realpath(file, NULL);
	char *curr = NULL;
	int comparisonResult = 0;

	if (absolutePath == NULL)
		return (-1);
	curr = getcwd(NULL, 0);
	curr = realloc(curr, strlen(curr) + strlen(file) + 2);
	strcat(curr, "/");
	strcat(curr, file);
	if (curr == NULL)
	{
		free(absolutePath);
		return (-1);
	}
	comparisonResult = strcmp(absolutePath, curr);
	if (comparisonResult == 0)
	{
		free(absolutePath);
		free(curr);
		return (0);
	}
	free(absolutePath);
	free(curr);
	return (1);
}
