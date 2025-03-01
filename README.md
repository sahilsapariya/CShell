# Custom Shell Implementation in C

This project is a minimal implementation of a custom shell in C. The shell will allow users to run basic commands, handle redirection, background processes, and more, simulating the functionality of a typical Unix/Linux shell.

## Features

- Command execution (external commands like `ls`, `pwd`, etc.)
- Built-in commands (`cd`, `pwd`, `exit`)
- Background execution using `&`
- Input/Output redirection (`>`, `<`)
- Piping between commands (`|`)
- Customizable prompt
- Error handling for invalid commands
- (Optional) Job control (`Ctrl+Z`, `bg`, `fg`)
- (Optional) Command history and aliases

## Getting Started

### Prerequisites

- A C compiler (GCC, Clang, etc.)
- A Unix-like operating system (Linux, macOS)
- Basic knowledge of C and Unix system calls

### Project Structure

```
shell/
├── src/          # Source files for the shell
├── include/      # Header files
├── tests/        # Test cases and files for the shell
├── Makefile      # Makefile for managing build process
└── README.md     # Project documentation (this file)
```

### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/your-shell-repo.git
    cd your-shell-repo
    ```

2. Compile the project using `make`:
    ```bash
    make
    ```

3. Run the shell:
    ```bash
    ./shell
    ```

### Usage

Once you start the shell, you can enter commands just like you would in any other terminal. For example:

```bash
sahilshell> ls -l
sahilshell> pwd
sahilshell> cd /path/to/directory
sahilshell> cat file.txt > output.txt
sahilshell> ls | grep '.txt'
sahilshell> ./a.out &
```

### Built-in Commands

- **cd [directory]**: Change the current directory.
- **pwd**: Print the current working directory.
- **exit**: Exit the shell.

### Roadmap

- [x] Basic input/output handling
- [x] Command loop and prompt customization
- [ ] Tokenization of input
- [ ] Forking and executing commands
- [ ] Implementing built-in commands (`cd`, `pwd`, `exit`)
- [ ] Handling redirection and pipes
- [ ] Background process management (`&`)
- [ ] Optional: Job control, command history, aliases

### 🚀 Contributing

If you'd like to contribute to this project, feel free to fork the repository and submit a pull request with any improvements, bug fixes, or new features. Happy Coding 🚀
