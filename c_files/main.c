# include "main.h"

int main(void) {
    
	char **tokens = NULL, *buffer = NULL;
	int i = 0;

    while (1) {
        buffer = print_prompt();
        
        if (buffer == NULL) {
            break;
        }
        
        if (strcmp(buffer, "exit") == 0) {
            free(buffer);
            break;
        }

        tokens = parser(buffer, " \t\n");
        
        if (tokens) {
            pid_t child_pid = create_process(tokens);
            
            if (child_pid != -1) {
                waitpid(child_pid, NULL, 0);
            }
            
            for (i = 0; tokens[i]; i++) {
                free(tokens[i]);
            }
            free(tokens);
        }
        
        free(buffer);
    }

    return 0;
}
