# include "main.h"

int execute_single(char *shell, char *path, int count, char **tokens, char *buffer, int status)
{
    if (validate(tokens[0]) == 0)
        status = exec_builtin(shell, count, tokens[0], tokens, buffer, status);
    else
        status = create_process(shell, tokens, count, path);
    
    return (status);
}

int check_operator(const char *token) {
    int op = 0;
    if (strstr(token, ";") != NULL)
        op = OP_SEMICOLON;
    else if (strstr(token, "&&") != NULL)
        op = OP_AND;
    else if (strstr(token, "||") != NULL)
        op = OP_OR;
    else
        op = OP_NONE;
    return (op);
}

int execute_command(char *shell, char **tokens, int count, char *path, char *buffer, int status)
{
    int i = 0, op = 0, k = 0;
    size_t buffsize = 0;
    char **parsed = NULL;
    char **commands = NULL;

    for (i = 0; buffer[i] && op == 0; i++)
    {
        if (buffer[i] == '&' || buffer[i] == '|' || buffer[i] == ';')
            op = 1;
    }
    if (op != OP_NONE)
    {
        commands = parser(buffer, ";&|");
        for (i = 0; commands[i]; i++)
            printf("%s\n", commands[i]);
        parsed = parser(commands[k], " \n\t");
        status = execute_single(shell, path, count, parsed, buffer, status);
        free_all(parsed);
        k++;
        for (i = 0; tokens[i]; i++)
        {
            op = check_operator(tokens[i]);
            if (op == OP_SEMICOLON)
            {
                if (commands[k])
                {
                    parsed = parser(commands[k], " \n\t");
                    status = execute_single(shell, path, count, parsed, buffer, status);
                    free_all(parsed);
                }
                k++;
            }
            else if (op == OP_AND)
            {
                if (status == 0)
                {
                    if (commands[k])
                    {
                        parsed = parser(commands[k], " \n\t");
                        status = execute_single(shell, path, count, parsed, buffer, status);
                        free_all(parsed);
                    }
                    else
                        my_getline(&buffer, &buffsize, stdin);
                }
                k++;
            }
            else if (op == OP_OR)
            {
                if (status != 0)
                {
                    if (commands[k])
                    {
                        parsed = parser(commands[k], " \n\t");
                        status = execute_single(shell, path, count, parsed, buffer, status);
                        free_all(parsed);
                    }
                    else
                        my_getline(&buffer, &buffsize, stdin);
                }
                k++;
            }
        }
        free_all(commands);
    }
    else
        status = execute_single(shell, path, count, tokens, buffer, status);
    return (status);
}