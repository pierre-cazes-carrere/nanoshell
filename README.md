# nanoshell

A minimal Unix shell implementation in C, designed to understand core shell mechanics: `fork()`, `execve()`, and `waitpid()`.

## Features

### Implemented
- **Prompt display**: Simple `?>` prompt
- **Line reading**: Read commands from stdin
- **Basic parsing**: Simple space-separated argument splitting
- **Builtin commands**:
  - `cd` - Change directory (supports `cd`, `cd ~`, `cd ..`, `cd <dir>`)
  - `pwd` - Print working directory
  - `env` - Display environment variables
  - `exit` - Exit the shell gracefully
- **External command execution**:
  - Absolute paths: `/usr/bin/ls`
  - Relative paths: `./script.sh`
  - PATH search: Automatically find commands in PATH

### Planned Extensions
- Background execution (`&`)
- Pipes (`|`)
- Input/output redirection (`>`, `<`)
- Signal handling (Ctrl-C, Ctrl-D)
- Command history

## Building

```bash
make          # Compile
make clean    # Remove object files
make fclean   # Remove all generated files
make re       # Rebuild from scratch
```

## Running

```bash
./nanoshell
```

## Usage Examples

```bash
?> ls
?> cd /tmp
?> pwd
/tmp
?> cd ..
?> env | head -5
?> exit
```

## Project Structure

```
nanoshell/
├── include/
│   └── nanoshell.h      # Main header with all prototypes
├── src/
│   ├── main.c           # Main shell loop
│   ├── prompt.c         # Prompt display and line reading
│   ├── parser.c         # Command line parsing
│   ├── exec.c           # External command execution
│   └── builtins.c       # Builtin command implementations
├── Makefile             # Build configuration
└── README.md            # This file
```

## Implementation Notes

- **No external libraries**: Uses only standard C and POSIX APIs
- **Simple parsing**: No quote handling, no escape sequences
- **Memory safety**: Proper allocation and deallocation
- **Portability**: Targets Linux/Unix systems

## TODO

See `// TODO:` comments in source files for remaining implementation details.

Key areas:
- `exec.c`: PATH search and fork/execve logic
- `builtins.c`: cd, pwd, env, exit implementations
- `prompt.c`: EOF (Ctrl-D) handling
