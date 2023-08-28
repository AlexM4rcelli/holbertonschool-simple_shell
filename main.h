# ifndef MAIN
# define MAIN

# include <stdio.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

#define OP_SEMICOLON 1
#define OP_AND       2
#define OP_OR        3
#define OP_NONE      0

extern char **environ;

/**
 * struct builtins - Struct of formats to print
 * @type: format to print;
 * @func: the function pointer of the specific format
 */

typedef struct builtins
{
	char *name;
	int (*func)(char *, int, char **, char *, int);
} built_ins;

extern char **environ;

char *print_prompt(int status);
char **parser(char *str, char *separator);
char *_getenv(char *str);
char *search_cmd(char *cmd, char *path);

int create_process(char *shell, char **buff, int count, char *path);
int execute_command(char *shell, char **tokens, int line_count, char *path, char *buffer, int status);
char ***split_command_line(char *command_line, char *delimiters);

/*Built-ins*/
int exec_builtin(char *shell, int count, char *built, char **tokens, char *buffer, int status);
int validate (char *built);
int my_env(char *shell, int count, char **tokens, char *buffer, int status);
int my_exit(char *shell, int count, char **tokens, char *buffer, int status);
int my_cd(char *shell, int count, char **tokens, char *buffer, int status);


/*Auxiliars*/
int is_In(char *file);
void free_all(char **array);
ssize_t my_getline(char **buffer, size_t *buffer_size, FILE *stream);


# endif
