# Minishell

## Project Overview
Minishell is a simplified shell implementation that replicates the behavior of a Unix shell. It supports command execution, built-in commands, redirections, pipes, and signal handling.

## Features
### General Requirements
- **Prompt Display**: Displays a prompt while waiting for a new command.
- **Command Execution**: Searches and executes the correct executable based on the `PATH` environment variable, or using a relative or absolute path.
- **History**: Maintains a functional command history.

### Signal Handling
- **Global Variable Restriction**: Only one global variable is allowed to indicate a received signal. This ensures that signal handling does not access the main data structure.
  - The global variable cannot communicate any other information or provide access to the main data structure.

### Quoting Rules
- **Single Quotes (`'`)**: Prevents the shell from interpreting meta-characters within the quoted sequence.
- **Double Quotes (`"`)**: Prevents the shell from interpreting meta-characters within the quoted sequence, except for the `$` (dollar sign).
- **Unclosed Quotes**: Does not interpret unclosed quotes or unsupported special characters like `\` (backslash) or `;` (semicolon).

### Redirections
- `<` : Redirects input.
- `>` : Redirects output.
- `<<` : Reads input until a specified delimiter is encountered (heredoc). The history is not updated during this process.
- `>>` : Redirects output in append mode.

### Pipes
- Implements pipes (`|`) to connect the output of one command to the input of the next.

### Environment Variables
- Supports substitution of environment variables (e.g., `$VAR`).
- Handles the special variable `$?`, which is replaced by the exit status of the last executed pipeline.

### Signal Behavior
- **Interactive Mode**:
  - `Ctrl-C`: Displays a new prompt on a new line.
  - `Ctrl-D`: Exits the shell.
  - `Ctrl-\`: Does nothing.
- Signal handling mimics the behavior of `bash`.

### Built-in Commands
The following built-in commands are implemented:
- **`echo`**: Supports the `-n` option.
- **`cd`**: Works with relative or absolute paths.
- **`pwd`**: Prints the current working directory (no options supported).
- **`export`**: Sets environment variables (no options supported).
- **`unset`**: Unsets environment variables (no options supported).
- **`env`**: Displays the environment variables (no options or arguments supported).
- **`exit`**: Exits the shell (no options supported).

## Usage
To use Minishell, compile the project using the provided `Makefile` and execute the resulting binary. The shell will display a prompt where you can enter commands.

## Compilation
Run the following command to compile the project:
```bash
make
