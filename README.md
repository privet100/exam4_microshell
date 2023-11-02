## Assignment 

Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp

Write a program that will behave like executing a shell command
- The command line to execute will be the arguments of this program
- Executable's path will be absolute or relative but your program must not build a path (from the PATH variable for example)
- You must implement "|" and ";" like in bash
	- we will never try a "|" immediately followed or preceded by nothing or "|" or ";"
- Your program must implement the built-in command cd only with a path as argument (no '-' or without parameters)
	- if cd has the wrong number of argument your program should print in STDERR "error: cd: bad arguments" followed by a '\n'
	- if cd failed your program should print in STDERR "error: cd: cannot change directory to path_to_change" followed by a '\n' with path_to_change replaced by the argument to cd
	- a cd command will never be immediately followed or preceded by a "|"
- You don't need to manage any type of wildcards (*, ~ etc...)
- You don't need to manage environment variables ($BLA ...)
- If a system call, except execve and chdir, returns an error your program should immediatly print "error: fatal" in STDERR followed by a '\n' and the program should exit
- If execve failed you should print "error: cannot execute executable_that_failed" in STDERR followed by a '\n' with executable_that_failed replaced with the path of the failed executable (It should be the first argument of execve)
- Your program should be able to manage more than hundreds of "|" even if we limit the number of "open files" to less than 30.
- Don't forget to pass the environment variable to execve
- Do not leak file descriptors

Examples:
```
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
```
```
microshell
i love my microshell
```

```
$>./microshell /bin/echo WOOT "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
```
```
WOOT ; /bin/echo NOPE; ; ;
YEAH
```
## Notes
Examshell doesn't test "error: fatal"

## File leaks (open file descriptors)

1) Add `sleep(240)` in the end of the code

2) Run the program

3) Tape in another terminal:
```(bash)
lsof -c microshell
```

File leaks example (= the file descriptors have not been closed):
```
COMMAND     PID USER   FD   TYPE             DEVICE SIZE/OFF    NODE NAME
microshel 45572   an  cwd    DIR                9,0     4096 7081581 /mnt/md0/42/exam04
microshel 45572   an  rtd    DIR               8,20     4096       2 /
microshel 45572   an  txt    REG                9,0    17176 7082016 /mnt/md0/42/exam04/microshell
microshel 45572   an  mem    REG               8,20  2029592 5245077 /usr/lib/x86_64-linux-gnu/libc-2.31.so
microshel 45572   an  mem    REG               8,20   191504 5245069 /usr/lib/x86_64-linux-gnu/ld-2.31.so
microshel 45572   an    0u   CHR              136,0      0t0       3 /dev/pts/0
microshel 45572   an    1u   CHR              136,0      0t0       3 /dev/pts/0
microshel 45572   an    2u   CHR              136,0      0t0       3 /dev/pts/0
microshel 45572   an    3u   CHR              136,0      0t0       3 /dev/pts/0             (!)
microshel 45572   an    4r  FIFO               0,13      0t0  810985 pipe                   (!)
microshel 45572   an    5w  FIFO               0,13      0t0  810985 pipe                   (!)
microshel 45572   an   36w   REG               8,20      488 2891842 /home/an/.config/Code/logs/20231030T080138/ptyhost.log
microshel 45572   an   37u  unix 0x0000000000000000      0t0  764762 type=STREAM
microshel 45572   an   38r   REG                7,4 12795643    9344 /snap/code/143/usr/share/code/resources/app/node_modules.asar
microshel 45572   an  103r   REG                7,4   578186    9650 /snap/code/143/usr/share/code/v8_context_snapshot.bin
```

## Sources

https://github.com/shackbei/microshell-42/blob/main/microshell.c

https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/test.sh

https://stackoverflow.com/questions/77385427/verify-open-file-descriptor-with-lsof/77386331#77386331 
