# ifndef MAIN
# define MAIN

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
/**
 * struct command_p - Struct of commands to print
 * @command: command to execute;
 * @func: the function pointer of the specific command
 */

typedef struct command_p
{
	char *command;
	int (*func)(va_list args);
} comm;

# endif