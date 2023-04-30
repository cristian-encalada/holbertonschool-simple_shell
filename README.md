# C Project - Command Line Interpreter (Shell)
The objective of this project is to create a simple command interpreter taking as a reference the UNIX shell.

A command line interpreter is a program that allows the entering of commands and then executes those commands to the operating system.

![HBN_Shell_gif](/logo/Holberton_shell.gif)

## Table of contents

   * [Table of contents](#table-of-contents)
   * [Requirements](#requirements)
   * [Allowed functions and system calls](#list-of-allowed-functions-and-system-calls)
   * [Compilation](#compilation)
   * [Installation](#installation)
   * [Mandatory Tasks](#mandatory-tasks)
   * [Advanced Tasks](#advanced-tasks)
   * [Testing](#testing)
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
---------------------------------------------------------------------------------

## Installation

To use this Simple Shell (called `hsh`) follow these steps:
1. Clone this repository to your local environment.
```
$ git clone https://github.com/Hiojam/holbertonschool-simple_shell.git
```
2. Go to the holbertonschool-simple_shell directory.
```
$ cd holbertonschool-simple_shell/
```
3. Compile the C source code using this command:
```
$ gcc -g -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
---------------------------------------------------------------------------------

## Mandatory Tasks

### 1. Basic shell using `execve`
Write a UNIX command line interpreter
Requirements:
- Display a prompt and wait for the user to type a command. A command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
- The command lines are made only of one word. No arguments will be passed to programs.
- If an executable cannot be found, print an error message and display the prompt again.
- Handle errors.
- You have to handle the “end of file” condition (Ctrl+D)
- Usage: `./hsh`

Example:
```
/root/holbertonschool-simple_shell$ ./hsh     
j#0000000000000000000000000000000000000
j#000000000000000000@Q**g00000000000000
j#0000000000000000*]++]4000000000000000
j#000000000000000k]++]++*N#000000000000
j#0000000000000*C+++]++]++]J*0000000000
j#00000000000@+]++qwwwp=]++++]*00000000
j#0000000000*+++]q#0000k+]+]++]4#000000
j#00000000*C+]+]w#0000*]+++]+]++0000000
j#0000we+]wW000***C++]++]+]++++40000000
j#000000000*C+]+]]+]++]++]++]+q#0000000
j#0000000*]+]+++++++]++]+++]+++J0000000
j#000000C++]=]+]+]+]++]++]+]+]+]=000000
j#00000k+]++]+++]+]++qwW0000000AgW00000
j#00000k++]++]+]+++qW#00000000000000000
j#00000A]++]++]++]++J**0000000000000000
j#000000e]++]+++]++]++]J000000000000000
j#0000000A]++]+]++]++]++000000000000000
j#000000000w]++]+]++]+qW#00000000000000
j#00000000000w]++++]*0##000000000000000
j#0000000000000Ag]+]++*0000000000000000
j#00000000000000000we]+]Q00000000000000
j#0000000000000@@+wgdA]+J00000000000000
j#0000000000000k?qwgdC=]4#0000000000000
j#00000000000000w]+]++qw#00000000000000
"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/root/holbertonschool-simple_shell$ /bin/ls
alias_utils.c  built-in_cmds2.c  cmds		    dir_utils.c  help		  hsh	main.c	   shell.h
AUTHORS        built-in_cmds.c	 command_manager.c  errors.c	 history_utils.c  logo	README.md  string_utils.c
/root/holbertonschool-simple_shell$ /bin/pwd
/root/holbertonschool-simple_shell
```
### 2. Handle command lines with arguments
Requirements:
- Handle command lines with arguments
Example:
```
/root/holbertonschool-simple_shell$ ls -la
total 140
drwxr-xr-x 5 root root  4096 Apr 29 14:44 .
drwx------ 1 root root  4096 Apr 29 14:43 ..
-rw-r--r-- 1 root root    13 Apr 29 14:43 .aliases
-rw-r--r-- 1 root root  2201 Apr 29 14:43 alias_utils.c
-rw-r--r-- 1 root root   118 Apr 29 14:43 AUTHORS
-rw-r--r-- 1 root root  3367 Apr 29 14:43 built-in_cmds2.c
-rw-r--r-- 1 root root  2748 Apr 29 14:43 built-in_cmds.c
-rw-r--r-- 1 root root   312 Apr 29 14:43 cmds
-rw-r--r-- 1 root root  6228 Apr 29 14:43 command_manager.c
-rw-r--r-- 1 root root  1448 Apr 29 14:43 dir_utils.c
-rw-r--r-- 1 root root   613 Apr 29 14:43 errors.c
drwxr-xr-x 8 root root   163 Apr 29 14:43 .git
-rw-r--r-- 1 root root    40 Apr 29 14:43 .gitignore
drwxr-xr-x 2 root root   167 Apr 29 14:43 help
-rw-r--r-- 1 root root  3176 Apr 29 14:43 history_utils.c
-rwxr-xr-x 1 root root 61216 Apr 29 14:44 hsh
drwxr-xr-x 2 root root    78 Apr 29 14:43 logo
-rw-r--r-- 1 root root  2300 Apr 29 14:43 main.c
-rw-r--r-- 1 root root  5201 Apr 29 14:43 README.md
-rw-r--r-- 1 root root  1997 Apr 29 14:43 shell.h
-rw-r--r-- 1 root root   121 Apr 29 14:49 .simple_shell_history
-rw-r--r-- 1 root root  2968 Apr 29 14:43 string_utils.c
/root/holbertonschool-simple_shell$ ps lf
F   UID   PID  PPID PRI  NI    VSZ   RSS WCHAN  STAT TTY        TIME COMMAND
4     0 18311 18308  20   0   8768     0 -      S    pts/6      0:00 su root
4     0 18312 18311  20   0   7368     8 poll_s S+   pts/6      0:01  \_ bash
4     0 18396     0  20   0   7236  3868 do_wai Ss   pts/203    0:00 /bin/bash
0     0 18563 18396  20   0   2504  1464 do_wai S+   pts/203    0:00  \_ ./hsh
0     0 18571 18563  20   0   8956  3080 -      R+   pts/203    0:00      \_ ps lf
4     0 30452     0  20   0   7236  3516 do_wai Ss   pts/202    0:00 /bin/bash
0     0 30499 30452  20   0   2492  1512 wait_w S+   pts/202    0:00  \_ ./hsh

```
### 3. Handle the `PATH`
Requierements:
- Handle the PATH
- `fork` must not be called if the command doesn’t exist
Example:
```
/root/holbertonschool-simple_shell$ /bin/ls
alias_utils.c  built-in_cmds2.c  cmds		    dir_utils.c  help		  hsh	main.c	   shell.h
AUTHORS        built-in_cmds.c	 command_manager.c  errors.c	 history_utils.c  logo	README.md  string_utils.c
/root/holbertonschool-simple_shell$ ls
alias_utils.c  built-in_cmds2.c  cmds		    dir_utils.c  help		  hsh	main.c	   shell.h
AUTHORS        built-in_cmds.c	 command_manager.c  errors.c	 history_utils.c  logo	README.md  string_utils.c
/root/holbertonschool-simple_shell$ ls -l /tmp 
total 4
-rw-r--r-- 1 root  root   0 Feb  8 08:35 iamafile
-rw-r--r-- 1 root  root   0 Apr  6 12:27 recover
-rw-r--r-- 1 root  root   0 Mar 29  2022 right_school
-rw-r--r-- 1 root  root  13 Feb  7 04:29 school
```
### 4. Implement the `exit built-in`, that exits the shell
Requirements:
- Implement the exit built-in, that exits the shell
Usage: `exit`
- Don’t handle any argument to the built-in exit yet.
Example using Valgrind:
```
valgrind -s --show-reachable=yes --leak-check=full ./hsh  
/root/holbertonschool-simple_shell$ exit
==29925== 
==29925== HEAP SUMMARY:
==29925==     in use at exit: 0 bytes in 0 blocks
==29925==   total heap usage: 47 allocs, 47 frees, 14,452 bytes allocated
==29925== 
==29925== All heap blocks were freed -- no leaks are possible
==29925== 
==29925== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

```
### 5. Implement the `env` built-in, that prints the current environment
Requirements:
- Implement the `env built-in`, that prints the current environment
```
/root/holbertonschool-simple_shell$ env
HOSTNAME=daa1255aa733
LANGUAGE=en_US:en
PWD=/root/holbertonschool-simple_shell
TZ=America/Los_Angeles
HOME=/root
LANG=en_US.UTF-8
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
LESSCLOSE=/usr/bin/lesspipe %s %s
TERM=xterm
LESSOPEN=| /usr/bin/lesspipe %s
SHLVL=1
LC_ALL=en_US.UTF-8
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
_=./hsh
OLDPWD=/root
/root/holbertonschool-simple_shell$ exit
root@daa1255aa733:~/holbertonschool-simple_shell#
```
## Advanced Tasks
##H 6. Handle arguments for the built-in `exit`
Requirements:
- Handle arguments for the `built-in exit`
Usage: `exit status`, where `status` is an integer used to exit the shell
Example:
```
root@daa1255aa733:~/holbertonschool-simple_shell# ./hsh
/root/holbertonschool-simple_shell$ exit 55      
root@daa1255aa733:~/holbertonschool-simple_shell# echo $?
55
root@daa1255aa733:~/holbertonschool-simple_shell#
```
### 7. Handle `Ctrl+C` key combination
Requirements:
- Handle `Ctrl+C`: the shell should not quit when the user inputs `^C`
Example:
```
/root/holbertonschool-simple_shell$ ^C
/root/holbertonschool-simple_shell$ ^C
/root/holbertonschool-simple_shell$ ls
alias_utils.c  built-in_cmds2.c  cmds		    dir_utils.c  help		  hsh	main.c	   shell.h
AUTHORS        built-in_cmds.c	 command_manager.c  errors.c	 history_utils.c  logo	README.md  string_utils.c
/root/holbertonschool-simple_shell$ ^C
/root/holbertonschool-simple_shell$ ^C
/root/holbertonschool-simple_shell$ ^C
/root/holbertonschool-simple_shell$ exit
root@daa1255aa733:~/holbertonschool-simple_shell#
```
### 8. Implement the `setenv` and `unsetenv` builtin commands
Implement the `setenv` and `unsetenv` builtin commands
Requirements for setenv:
- Initialize a new environment variable, or modify an existing one
- Command syntax: `setenv VARIABLE VALUE`
- Should print something on stderr on failure
Requirements for unsetenv:
- Remove an environment variable
- Command syntax: `unsetenv VARIABLE`
- Should print something on stderr on failure
```
/root/holbertonschool-simple_shell$ setenv TEST1 VALUE1 
/root/holbertonschool-simple_shell$ setenv TEST2 VALUE2
/root/holbertonschool-simple_shell$ echo $TEST1
VALUE1
/root/holbertonschool-simple_shell$ echo $TEST2
VALUE2
/root/holbertonschool-simple_shell$ unsetenv TEST1
/root/holbertonschool-simple_shell$ echo TEST1
TEST1
/root/holbertonschool-simple_shell$ unsetenv TEST9
Error: Variable TEST9 not found
/root/holbertonschool-simple_shell$ setenv TEST5
Error: Not valid sintax. Use: setenv (var) (value)
```
### 9. Implement the builtin command `cd`
Implement the builtin command `cd`:
Requirements:
Changes the current directory of the process.
Command syntax: `cd [DIRECTORY]`
If no argument is given to `cd` the command must be interpreted like `cd $HOME`
You have to handle the command `cd -`
You have to update the environment variable `PWD` when you change directory
### 10. Handle the commands separator `;`
Requirements:
Handle the commands separator ;
Example:
```
/root/holbertonschool-simple_shell$ pwd ; pwd
/root/holbertonschool-simple_shell
/root/holbertonschool-simple_shell
/root/holbertonschool-simple_shell$ ls /var ; ls /var
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
/root/holbertonschool-simple_shell$ ls /invalid ; ls /var             
ls: cannot access '/invalid': No such file or directory
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
/root/holbertonschool-simple_shell$ ls /var ; ls /invalid
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
ls: cannot access '/invalid': No such file or directory
/root/holbertonschool-simple_shell$ ls /var ; ls /invalid ; ls /var ; pwd
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
ls: cannot access '/invalid': No such file or directory
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
/root/holbertonschool-simple_shell

```
### 11. Handle the `&&` and `||` shell logical operators
Requirements:
Handle the `&&` and `||` shell logical operators
Example: (partially working)
```
/root/holbertonschool-simple_shell$ ls /var && ls /var && ls /var && ls /hbtn && ls /invalid
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
ls: cannot access '/hbtn': No such file or directory
ls: cannot access '/invalid': No such file or directory
/root/holbertonschool-simple_shell$ ls /invalid && ls /var && ls /var && ls /hbtn && ls /hbtn
ls: cannot access '/invalid': No such file or directory
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
backups  cache	lib  local  lock  log  mail  opt  run  spool  tmp
ls: cannot access '/hbtn': No such file or directory
ls: cannot access '/hbtn': No such file or directory

```
### 12. Implement the `alias` builtin command
Requirements:
- Implement the alias builtin command
Usage: `alias [name[='value'] ...]`
  - alias: Prints a list of all aliases, one per line, in the form `name='value'`
  - `alias name [name2 ...]`: Prints the aliases `name`, `name2`, etc 1 per line, in the form `name='value'`
  - `alias name='value' [...]`: Defines an alias for each `name` whose `value` is given. If `name` is already an alias, replaces its value with value
Example:
```
/root/holbertonschool-simple_shell$ alias
hola='hola2'
ls='list'
/root/holbertonschool-simple_shell$ alias list=ls
/root/holbertonschool-simple_shell$ alias
hola='hola2'
ls='list'
list='ls'
/root/holbertonschool-simple_shell$ alias invalid
Error: Alias not found.
/root/holbertonschool-simple_shell$ alias list=pwd
/root/holbertonschool-simple_shell$ alias
hola='hola2'
ls='list'
list='pwd'
```
### 13. Handle variables replacement
Requirements:
- Handle variables replacement
- Handle the `$?` variable
- Handle the `$$` variable
Example:
```
/root/holbertonschool-simple_shell$ ls
alias_utils.c  built-in_cmds2.c  cmds		    dir_utils.c  help		  hsh	main.c	   shell.h
AUTHORS        built-in_cmds.c	 command_manager.c  errors.c	 history_utils.c  logo	README.md  string_utils.c
/root/holbertonschool-simple_shell$ echo $?
0
/root/holbertonschool-simple_shell$ invalid command
./hsh: 1: invalid: not found
/root/holbertonschool-simple_shell$ echo $?
127
/root/holbertonschool-simple_shell$ echo $$
18837
/root/holbertonschool-simple_shell$ ps
  PID TTY          TIME CMD
18823 pts/203  00:00:00 bash
18837 pts/203  00:00:00 hsh
18875 pts/203  00:00:00 ps
```
### 14. Handle comments (`#`)
Requirements:
- Handle comments (`#`)
Example:
```
/root/holbertonschool-simple_shell$ echo $$ # ls -la
18837
/root/holbertonschool-simple_shell$ ls # clear      
alias_utils.c  built-in_cmds2.c  cmds		    dir_utils.c  help		  hsh	main.c	   shell.h
AUTHORS        built-in_cmds.c	 command_manager.c  errors.c	 history_utils.c  logo	README.md  string_utils.c

```
### 15. Implement the `help` built-in
Requirements:
- Implement the help built-in
- Usage: `help [BUILTIN]`
Example:
```
/root/holbertonschool-simple_shell$ help exit
exit: exit [status]
    Exit the shell with the given status or 0 if not stated.
    
    If the command receives a letter as a status, it exits with value 0.
    
    Exit Status:
    Returns 0 unless status argument is received.
/root/holbertonschool-simple_shell$ help history
history: history
    Prints the history of commands.
    
    When executing a command it is registered in the history for later use.
		On exiting the shell all the commands executed during the session will be saved in a file.
    
    Exit Status:
    Returns 0.
```
### 16. Implement the `history built-in`, without any argument
Requirements:
- Implement the history built-in, without any argument
- The `history` built-in displays the history list, one command by line, preceded with line numbers (starting at `0`)
- On `exit`, write the entire history, without line numbers, to a file named `.simple_shell_history` in the directory `$HOME`
- When the shell starts, read the file `.simple_shell_history` in the directory `$HOME` if it exists, and set the first line number to the total number of lines in the file modulo `4096`
```
/root/holbertonschool-simple_shell$ ls
alias_utils.c  built-in_cmds2.c  cmds		    dir_utils.c  help		  hsh	main.c	   shell.h
AUTHORS        built-in_cmds.c	 command_manager.c  errors.c	 history_utils.c  logo	README.md  string_utils.c
/root/holbertonschool-simple_shell$ ls -la
total 152
drwxr-xr-x 5 root root  4096 Apr 29 17:35 .
drwx------ 1 root root  4096 Apr 29 14:43 ..
-rw-r--r-- 1 root root    34 Apr 29 17:35 .aliases
-rw-r--r-- 1 root root  2201 Apr 29 14:43 alias_utils.c
-rw-r--r-- 1 root root   118 Apr 29 14:43 AUTHORS
-rw-r--r-- 1 root root  3367 Apr 29 14:43 built-in_cmds2.c
-rw-r--r-- 1 root root  2748 Apr 29 14:43 built-in_cmds.c
/root/holbertonschool-simple_shell$ pwd
/root/holbertonschool-simple_shell
/root/holbertonschool-simple_shell$ echo $$
19392
/root/holbertonschool-simple_shell$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
/root/holbertonschool-simple_shell$ exit

root@daa1255aa733:~/holbertonschool-simple_shell# cat .simple_shell_history 
ls
ls -la
ls
ls -la
pwd
echo $$
echo $PATH
cat .simple_shell_history
exit
```
### 17. Handle files as input
Requirements:
Usage: `simple_shell [filename]`
- Your shell can take a file as a command line argument
- The file contains all the commands that your shell should run before exiting
- The file should contain one command per line
- In this mode, the shell should not print a prompt and should not read from `stdin`
---------------------------------------------------------------------------------

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

## Authors

[Cristian Encalada](https://github.com/cristian-encalada)

[Hiojam Rodríguez](https://github.com/Hiojam)
