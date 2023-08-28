#include "main.h"

int exec_builtin(char *shell, int count, char *built, char **tokens, char *buffer, int status)
{
	unsigned int i = 0;

	built_ins b_ins[] = {
		{"env1", my_env},
		{"exit", my_exit},
		{"cd", my_cd},
		{NULL, NULL}
	};

	while (b_ins[i].name)
	{
		if (strcmp(b_ins[i].name, built) == 0)
			return (b_ins[i].func(shell, count, tokens, buffer, status));
		i++;
	}

	return (status = 0);
}

/**
 * validate - check if an token is a buitin
 * @built: token to check
 *
 * Return: 0 if is a builtin or 1 if not
 */

int validate (char *built)
{
    int i;
    char *validator[] = {"env", "exit", "cd", NULL};

    for (i = 0; validator[i]; i++)
    {
        if (strcmp(built, validator[i]) == 0)
            return (0);
    }
    return (1);
}