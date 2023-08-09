# include "main.h"

char **parser(char *str, char *separator)
{
    char **tokens = NULL;
    int i = 0, count = 0;
    char *token;
    char *aux = strdup(str);

    while (str[i])
    {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i + 1] == '\0')
            count++;
        i++;
    }

    count += 1;
    tokens = malloc(count * sizeof(char *));

    if (!tokens)
        return (NULL);

    token = strtok(aux, separator);   
    i = 0;
    while (token)
    {
        tokens[i++] = strdup(token);
        token = strtok(NULL, separator);
    }
    tokens[i] = NULL;

    free(aux);
    return (tokens);
}

char *_getenv(char *str)
{
    int i;
    char **value = NULL;

    for (i = 0; environ[i]; i++)
    {
        if ((strncmp(str, environ[i], strlen(str))) == 0)
        {
            
            value = parser(environ[i], "=");
            return (value[1]);
        }
    }

    return (NULL);
}

int getcmd(void)
{
    char *path = strdup(_getenv("PATH="));
    char *aux = strdup(path);
    char **directories;
    int i;
    
    directories = parser(aux, ":");

    for(i = 0; directories[i]; i++)
        printf("%s\n", directories[i]);
    
    for (i=0; directories[i]; i++)
        free(directories[i]);
    free(path);
    free(aux);
    return (0);
}