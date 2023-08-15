# include "main.h"

char *_itoa(int num)
{
    unsigned int i = 0, len = 0, negative = 0, aux = num;
	char *numStr;

	while (aux != 0)
	{
		aux = aux / 10;
		len++;
	}

	if (num < 0)
	{
		negative = 1;
		num = -num;
		numStr = malloc(len + 2);
		len++;
	} else
		numStr = malloc(len + 1);

	while (num > 0)
	{
		numStr[i++] = num % 10 + '0';
		num = num / 10;
	}

	if (negative)
		numStr[i++] = '-';
	numStr[i] = '\0';

	return (numStr);
}

void not_found(char *str, int count)
{
    char *num = _itoa(count);
    
    write(STDERR_FILENO, str, strlen(str));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, num, strlen(num));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, "not found\n", 10);

    free(num);
}