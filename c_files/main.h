# ifndef MAIN
# define MAIN

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
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

extern char **environ;

char *print_prompt(void);
char **parser(char *str, char *separator);
char *_getenv(char *str);
char *search_cmd(char *cmd);
pid_t create_process(char **buff);
# endif
