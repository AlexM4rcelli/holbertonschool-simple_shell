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

#define ERR_MALLOC "Unable to malloc space\n"
#define ERR_FORK "Unable to fork and create child process\n"
#define ERR_PATH "No such file or directory\n"

extern char **environ;

char *print_prompt(void);
char **parser(char *str, char *separator);
char *_getenv(char *str);
char *search_cmd(char *cmd);
void create_process(char *shell, char **buff, int count);
void print_env(void);
void not_found(char *shell, char *str, int count);
char *_itoa(int num);


# endif
