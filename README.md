# Custom Shell

This is a simple custom shell implementation in C. It allows you to execute commands and manage processes.

## Files

- `main.h`: Header file containing function declarations, included libraries, and external variable declaration.

- `functions.c`: Source file containing the implementation of various utility functions used in the shell, such as printing the prompt, parsing input, searching for commands in the PATH, and creating processes.

- `main.c`: Source file containing the main function that drives the custom shell. It repeatedly takes user input, processes it, and executes commands.

- 'auxiliars.c': It contains the `free_all` function which is responsible for freeing the memory associated with a string array and the `is_In` function which compares the absolute path of a file with a constructed path, which combines the current working directory and the file name. given file to determine if the file is in the current working directory.

- 'env.c': Contains the `_getenv` function that finds and retrieves the value associated with a specific environment variable

## Usage

1. Compile the code:
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o exe_file

2. Run the custom shell:
./exe_file

3. Once the shell is running, you can enter commands and execute them.

## Features

- Command Prompt: The shell provides a command prompt that displays "$" when input is expected.

- Command Parsing: User input is parsed into separate tokens based on space, tab, and newline characters.

- Execution of Commands: The shell supports executing commands either by specifying the full path or by searching for the command in the PATH environment variable.

- Exiting the Shell: You can exit the shell by typing "exit".

## Functions

- `print_prompt()`:
  
1. Displays the shell prompt ( $) if the program is running in an interactive terminal.
    
2. Reads a line of user input.
  
3. If there is an error reading the input or if the input line is empty, the program ends.

- `parser(char *str, char *separator)`:

1. Tokenizes a given string using a specific separator (usually a space).
  
2. Counts the number of tokens to allocate memory for a string array.
  
3. Copies each token to a separate string within the array.
     
4. Returns the array of tokens.

- `search_cmd(char *cmd)`:
  
1. Looks for a given command in the directories specified by the PATH environment variable.

2. Tokenize the PATH variable to get individual directories.
    
3. Build a possible full path to the command in each directory and check if the file exists.
  
4. Returns the full path to the command if found; otherwise NULL.
     
- `create_process(char *shell, char **buff, int count, char *path)`:
  
1. Determines if the command is an executable file in the current directory or requires searching the PATH file.

2. If the command is an executable in the current directory:

     - Create a child process using fork().
       
     - Run the command using execve() in the child process.
     
     - Waits for the child process to complete and returns the exit status.

3. If the command requires searching through PATH:

     - Calls search_cmd to get the full path of the command.
       
     - If the full path is found, execute the command.
       
     - If the command is not found, an error message is printed and an exit status of 127 is returned.