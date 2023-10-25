# Minishell

```
This project is all about recreating your very own (mini)shell, taking bash as reference.
```

Built by me and [Rel09](https://github.com/Rel09)

![Minishell Gif](https://i.imgur.com/M0nKL3N.gif)

## Features

- **Interactive Prompt**: A user-friendly prompt is displayed while waiting for a new command.

- **Command History**: Keeps a working history of previously executed commands.

- **Executable Launch**: Can find and execute executables using the PATH variable or absolute paths.

- **Quoting Support**: Handles single and double quotes like in Bash.

- **Redirections**: Supports redirections such as `<` (input), `>` (output), `>>` (output in append mode), and `<<`.

- **Pipes**: Implements the pipe (`|`) functionality for command chaining.

- **Environment Variables**: Handles environment variables.

- **Exit Code**: Supports the `$?` feature to display the exit code of the last executed command.

- **Signal Handling**: Behaves like Bash for signals, including `ctrl-C`, `ctrl-D`, and `ctrl-\`.

- **Built-in Commands**:
  - `pwd` without any flags.
  - `exit` without any flags.
  - `unset` without any flags.
  - `export` without any flags.
  - `echo` with the `-n` option.
  - `env` without any flags or arguments.
  - `cd` with only a relative or absolute path.
