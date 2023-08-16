# include "main.h"

/**
 * _itoa - stringify a number
 *
 * @num: number to stringify
 * Return: the number as a string
 */

char *_itoa(int num)
{
	unsigned int len = 0, neg = 0, aux = num;
	char *numStr;

	if (num == 0)
	{
		numStr = malloc(2);
		if (!numStr)
			return (NULL);
		numStr[0] = '0', numStr[1] = '\0';
		return (numStr);
	}
	if (num < 0)
	{
		neg = 1, num = -num, len++;
	}
	aux = num;
	while (aux)
		aux /= 10, len++;
	numStr = malloc(len + neg + 1);
	if (!numStr)
		return (NULL);
	numStr[len + neg] = '\0';
	while (num)
		numStr[--len + neg] = (num % 10) + '0', num /= 10;
	if (neg)
		numStr[0] = '-';
	return (numStr);
}

/**
* not_found - prints in stderr
* @str: the command given
* @count: number of lines
* @shell: the name of the shell
*/

void not_found(char *shell, char *str, int count)
{
	char *num = _itoa(count);

	write(STDERR_FILENO, shell, strlen(shell));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, strlen(str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, num, strlen(num));
	write(STDERR_FILENO, ": not found\n", 12);

	free(num);
}

/**
 * free_all - frees a array of arrays
 * @array: array to free
 * @str: string to free
 */


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
