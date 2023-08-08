# include "main.h"

int main (void)
{
    char *buffer;
    size_t buffsize = 1024;
    ssize_t prompt;

    buffer = (char *)malloc(buffsize * sizeof(char));
    if (!buffer)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    while (1)
    {
        if (isatty(0))
        {
            printf("$ ");
            prompt = getline(&buffer, &buffsize, stdin);
            if ((strcmp(buffer, "exit\n")) == 0 || prompt < 0)
            {
                free(buffer);
                exit(0);
            }
            printf("Typed: %ld - %s\n", prompt, buffer);
        }
    }

    return (0);
}