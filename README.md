# Custom Shell

This is a simple custom shell implementation in C. It allows you to execute commands and manage processes.

## Files

- `main.h`: Header file containing function declarations, included libraries, and external variable declaration.

- `functions.c`: Source file containing the implementation of various utility functions used in the shell, such as printing the prompt, parsing input, searching for commands in the PATH, and creating processes.

- `main.c`: Source file containing the main function that drives the custom shell. It repeatedly takes user input, processes it, and executes commands.

## Usage

1. Compile the code:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o exe_file

2. Run the custom shell:
./exe_file

3. Once the shell is running, you can enter commands and execute them.

## Features

- Command Prompt: The shell provides a command prompt that displays "#cisfun$" when input is expected.

- Command Parsing: User input is parsed into separate tokens based on space, tab, and newline characters.

- Execution of Commands: The shell supports executing commands either by specifying the full path or by searching for the command in the PATH environment variable.

- Exiting the Shell: You can exit the shell by typing "exit".

## Functions

- `print_prompt()`: Prints the command prompt and reads user input.

- `parser(char *str, char *separator)`: Parses a string into an array of tokens using the specified separator characters.

- `_getenv(char *str)`: Searches for an environment variable and returns its value.

- `search_cmd(char *cmd)`: Searches for a command in the directories specified by the PATH environment variable and returns its full path.

- `create_process(char **buff, int count)`: Creates a new process to execute the specified command and waits for the process to complete.


