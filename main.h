# ifndef MAIN
# define MAIN

# include <stdio.h>
#include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

extern char **environ;

char *print_prompt(int status);
char **parser(char *str, char *separator);
char *_getenv(char *str);
char *search_cmd(char *cmd, char *path);

int create_process(char *shell, char **buff, int count, char *path);
int is_In(char *file);

void print_env(void);
void free_all(char **array);

# endif
