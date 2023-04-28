# C Project - Command Line Interpreter (Shell)
The objective of this project is to create a simple command interpreter taking as a reference the UNIX shell.

A command line interpreter is a program that allows the entering of commands and then executes those commands to the operating system.

## Table of contents

   * [Table of contents](#table-of-contents)
   * [Requirements](#requirements)
   * [Allowed functions and system calls](#list-of-allowed-functions-and-system-calls)
   * [Compilation](#compilation)
   * [Tasks](#tasks-completed)
   * [Installation](#installation)
   * [Authors](#authors)

---------------------------------------------------------------------------------

## Requirements
### General

  - Allowed editors: ´vi´, ´vim´, ´emacs´, ´VSCode´
  - All your files will be compiled on `Ubuntu 20.04 LTS` using `gcc`, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
  - All your files should end with a new line
  - A `README.md` file, at the root of the folder of the project is mandatory
Your code should use the `Betty` style. It will be checked using [`betty-style.pl`](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl) and [`betty-doc.pl`](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl)
  - Your shell should not have any memory leaks
  - No more than 5 functions per file
  - All your header files should be include guarded
  - Use system calls only when you need to ([`why?`](https://www.quora.com/Why-are-system-calls-expensive-in-operating-systems))
  
## More Info
### Output
- Unless specified otherwise, your program **must have the exact same output** as `sh` (`/bin/sh`) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)

Example of error with `sh`:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with your program `hsh`:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```
---------------------------------------------------------------------------------

## List of allowed functions and system calls

- All functions from `<strings.h>` standard library
- `access` (man 2 access)
- `chdir` (man 2 chdir)
- `close` (man 2 close)
- `closedir` (man 3 closedir)
- `execve` (man 2 execve)
- `exit` (man 3 exit)
- `_exit` (man 2 _exit)
- `fflush` (man 3 fflush)
- `fork` (man 2 fork)
- `free` (man 3 free)
- `getcwd` (man 3 getcwd)
- `getline` (man 3 getline)
- `isatty` (man 3 isatty)
- `kill` (man 2 kill)
- `malloc` (man 3 malloc)
- `open` (man 2 open)
- `opendir` (man 3 opendir)
- `perror` (man 3 perror)
- `read` (man 2 read)
- `readdir` (man 3 readdir)
- `signal` (man 2 signal)
- `stat` (__xstat) (man 2 stat)
- `lstat` (__lxstat) (man 2 lstat)
- `fstat` (__fxstat) (man 2 fstat)
- `strtok` (man 3 strtok)
- `wait` (man 2 wait)
- `waitpid` (man 2 waitpid)
- `wait3` (man 2 wait3)
- `wait4` (man 2 wait4)
- `write` (man 2 write)

## Compilation
The shell will be compiled this way:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Testing
The shell should work like this in ``interactive mode``:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in ``non-interactive mode``:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
---------------------------------------------------------------------------------

## Tasks Completed

### 1. Basic shell using `execve`
### 2. Handle command lines with arguments
### 3. Handle the `PATH`
### 4. Implement the `exit built-in`, that exits the shell
### 5. Implement the `env` built-in, that prints the current environment
### 6. Handle arguments for the built-in `exit`
### 7. Handle `Ctrl+C`: the shell should not quit when the user inputs ^C
### 8. Implement the `setenv` and `unsetenv` builtin commands
### 9. Implement the builtin command `cd`
### 10. Handle the commands separator `;`
### 11. Handle the `&&` and `||` shell logical operators
### 12. Implement the `alias` builtin command
### 13. Handle variables replacement
### 14. Handle comments (`#`)
### 15. Implement the `help` built-in
### 16. Implement the `history built-in`, without any argument
### 17. Handle files as input

---------------------------------------------------------------------------------

## Installation

To use this Simple Shell (called `hsh`) follow these steps:
1. Clone this repository to your local environment.
```
$ git clone https://github.com/Hiojam/holbertonschool-simple_shell.git
```
2. Go to the holbertonschool-simple_shell directory.
```
$ cd holbertonschool-simple_shell
```
3. Compile the C source code using this command:
```
$ gcc -g -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
---------------------------------------------------------------------------------

## Authors

[Cristian Encalada](https://github.com/cristian-encalada)

[Hiojam Rodríguez](https://github.com/Hiojam)
