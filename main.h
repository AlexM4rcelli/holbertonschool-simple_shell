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

char *print_prompt(int status);
char **parser(char *str, char *separator);
char *_getenv(char *str);
char *search_cmd(char *cmd);
int create_process(char *shell, char **buff, int count);
int execute_with_path(char **buff, char *full_path);
void print_env(void);
void free_all(char **array, char *str);

# endif
