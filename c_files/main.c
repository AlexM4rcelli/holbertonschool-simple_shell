# include "main.h"

int main (void)
{
    char **tokens = NULL, *buffer = NULL;
    int i = 0;
    
    while (1)
    {
        buffer = print_prompt();

        if ((strcmp(buffer, "exit")) == 0)
            break;

        tokens = parser(buffer, " \t\n");

        create_process(tokens);

        if (tokens)
        {
            for(i = 0; tokens[i]; i++)
            {
                free(tokens[i]);
            }
            free(tokens);
        }
        free(buffer);
    }

    free(buffer);
    return (0);
}