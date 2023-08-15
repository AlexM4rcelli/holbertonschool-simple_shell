# include "main.h"

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */

int main(void) {
    char *buffer = NULL;
    char **tokens = NULL;
    int i, count = 0;

    while (1) {
        count++;
        buffer = print_prompt();

        if (!buffer)
            break;

        if (feof(stdin) || strcmp(buffer, "exit") == 0)
            break;

        if (strcmp(buffer, "") == 0)
        {
            free(buffer);
            continue;
        }

        tokens = parser(buffer, " \t\n");

        if (tokens)
        {
            create_process(tokens, count);

            for (i = 0; tokens[i]; i++)
                free(tokens[i]);
            free(tokens);
        }
        free(buffer);
    }
    free(buffer);
    return (0);
}