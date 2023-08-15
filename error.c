# include "main.h"

/**
 * _itoa - stringify a number
 *
 * @num: number to stringify
 * Return: the number as a string
 */

char *_itoa(int num)
{
    unsigned int len = 0, negative = 0, aux = num;
    char *numStr;

    if (num == 0)
	{
        numStr = malloc(2);
        if (numStr)
		{
            numStr[0] = '0';
            numStr[1] = '\0';
        }
        return numStr;
    }

    if (num < 0)
	{
        negative = 1;
        num = -num;
        len++;
    }

    aux = num;
    while (aux != 0)
	{
        aux = aux / 10;
        len++;
    }

    numStr = malloc(len + 1);
    if (!numStr)
		return NULL;

    numStr[len] = '\0';

    while (num > 0)
	{
        numStr[--len] = (num % 10) + '0';
        num = num / 10;
    }

    if (negative)
        numStr[0] = '-';

    return numStr;
}

/**
* not_found - prints in stderr
* 
* @str: the command given
* @count: number of lines
*/

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