# include "main.h"

int main (void)
{
    int i;
    char **tokens = NULL;
    char *buffer = NULL;
    char *path = NULL;
    
    size_t buffsize = 0;
    ssize_t prompt;
    while (1)
    {
        if (isatty(0))
            printf("#cisfun$ ");
                    
        prompt = getline(&buffer, &buffsize, stdin);
        
        if (prompt < 0)
        {
            free(buffer);
            exit(0);
        }
        if (buffer[prompt - 1] == '\n')
        {
            buffer[prompt - 1] = '\0';
            prompt--;
        }
        if ((strcmp(buffer, "exit")) == 0)
        {
            free(buffer);
            exit(0);
        }
       
        tokens = parser(buffer, " \t\n");
        printf("%s - Typed: %ld - %s - Size: %ld\n", tokens[0], prompt, buffer, sizeof(buffer));
        
        path = _getenv("PATH=");
        printf("%s\n", path);
        i = 0;
        while(tokens[i])
        {
            free(tokens[i]);
            i++;
        }
        free(path);
        free(tokens);
    }

    free(buffer);
    return (0);
}