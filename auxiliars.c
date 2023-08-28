# include "main.h"

/**
 * free_all - frees a array of arrays
 * @array: array to free
 */

void free_all(char **array)
{
	int i;

	for (i = 0; array[i]; i++)
		free(array[i]);
	free(array);
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

/**
 * my_getline - read a line of text from a specified input stream
 *
 * @buffer: pointer to string that will store the line
 * @buffer_size: pointer to a variable that holds the size of the buffer
 * @stram: the input stream from which read the line
 *
 * Return: the number of characters readed or -1 on error or EOF is reached
 */
ssize_t my_getline(char **buffer, size_t *buffer_size, FILE *stream)
{
	size_t line_len = 0, capacity = *buffer_size;
	int character;

	if (*buffer == NULL)
	{
		if (*buffer_size == 0)
			capacity = 128;
		*buffer = (char *) malloc(capacity + 1);
		if (*buffer == NULL)
			return (-1);
	}
	while ((character = fgetc(stream)) != EOF)
	{
		if (line_len + 1 >= capacity)
		{
			capacity = capacity * 2;
			*buffer = (char*)realloc(*buffer, capacity + 1);
			if (*buffer == NULL)
				return (-1);
		}
		(*buffer)[line_len++] = (char)character;
		if (character == '\n')
			break;
	}
	if (line_len == 0 && character == EOF)
		return (-1);
	(*buffer)[line_len] = '\0';
	*buffer_size = strlen(*buffer);

	return (line_len);
}
