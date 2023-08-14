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


extern char **environ;

char *print_prompt(void);
char **parser(char *str, char *separator);
char *_getenv(char *str);
char *search_cmd(char *cmd);
void create_process(char **buff, int count);

# endif
