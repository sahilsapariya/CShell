# Build Your Own Shell - Project Roadmap

## Chapter 1: Project Setup

- [x] **Task 1.1: Set up the development environment**
  - [x] Install a C compiler (e.g., GCC, Clang).
  - [x] Set up a text editor or IDE (VS Code, CLion, etc.).
  - [x] Create a GitHub repository for version control.
    - [x] Initialize the project: `git init`.
    - [x] Create a `.gitignore` for C projects.

- [x] **Task 1.2: Basic Project Structure**
  - [x] Create the following folder structure:
    ```
    shell/
      ├── src/
      ├── include/
      ├── tests/
      ├── Makefile
      └── README.md
    ```
    - [x] Add a basic Makefile.
    - [x] Add a `README.md` file.

- [x] **Task 1.3: Implement Basic Input/Output**
  - [x] Implement `main.c` to:
    - [x] Print a prompt.
    - [x] Read a single line of input.
    - [x] Echo the input back.

- [x] **Task 1.4: Compile & Run the Program**
  - [x] Add compilation instructions to the Makefile.
  - [x] Compile and run: `make`.
  - [x] Ensure basic I/O is functional.

---

## Chapter 2: Building the Command Loop

- [x] **Task 2.1: Infinite Command Loop**
  - [x] Continuously display the prompt until `exit` is typed.

- [x] **Task 2.2: Customize the Shell Prompt**
  - [x] Display current working directory using `getcwd()`.
  - [x] Show the current username with `getenv("USER")`.

- [x] **Task 2.3: Tokenize Input**
  - [x] Split input into tokens (command + arguments) using `strtok()`.

- [x] **Task 2.4: Handle Empty Input**
  - [x] Ignore empty input when the user presses Enter.

---

## Chapter 3: Executing Commands

- [ ] **Task 3.1: Forking a New Process**
  - [ ] Use `fork()` to create a new process.
  - [ ] Parent process should wait for child process completion.

- [ ] **Task 3.2: Execute System Commands**
  - [ ] Implement command execution using `execvp()`.
  - [ ] Handle errors for invalid commands.

- [ ] **Task 3.3: Add Built-in Commands (Part 1)**
  - [ ] Implement built-ins:
    - [ ] `exit`: Terminate the shell.
    - [ ] `cd`: Change directories.
    - [ ] `pwd`: Print working directory.

- [ ] **Task 3.4: Error Handling for Built-ins**
  - [ ] Handle errors for built-ins (e.g., invalid `cd` paths).

---

## Chapter 4: Enhancing Command Handling

- [ ] **Task 4.1: Add Environment Variables Support**
  - [ ] Read environment variables using `getenv()`.
  - [ ] Modify environment variables using `setenv()` and `unsetenv()`.

- [ ] **Task 4.2: Handle Background Execution**
  - [ ] Support background tasks (e.g., `command &`).

- [ ] **Task 4.3: Handle Redirection (Input & Output)**
  - [ ] Implement output redirection (`>`) using `dup2()`.
  - [ ] Implement input redirection (`<`).

- [ ] **Task 4.4: Handle Piping Between Commands**
  - [ ] Implement pipes (`|`) to connect commands.
