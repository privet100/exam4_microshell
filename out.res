/bin/ls
a.out
microshell
microshell.c
out.res
Readme.md
test11.txt
test1.txt
test21.txt
test2.txt
test.sh

/bin/cat microshell.c
// https://github.com/shackbei/microshell-42/blob/main/microshell.c
// https://github.com/Glagan/42-exam-rank-04/blob/master/micro;shell/test.sh

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h> // tmp
#include <stdio.h> // tmp
#define CHILDIN     fd_tmp
#define CHILDOUT    pip[1]
#define NXT_CHILDIN pip[0]
#define STDIN       STDIN_FILENO
#define STDOUT      STDOUT_FILENO

void	write_fd2(char *s1, char *s2)
{
	while (*s1)
		write(2, s1++, 1);
	while(s2 && *s2)
		write(2, s2++, 1);
	write(2, "\n", 1);
}

int	main(int argc, char *argv[], char *env[])
{
	int	i = 0;
	int j = 0;
	int fd_tmp = dup(STDIN);
	int pip[2];
	(void)argc;

	// dprintf(2, "\nGEN-%d %2d -> ... -> %2d,                 %2d\n", j, STDIN, STDOUT, CHILDIN);
	while (argv[i] && argv[i + 1]) //check the end
	{
		argv = &argv[i + 1]; //new argv starts after ; or |
		i = -1;
		while (argv[++i] && strcmp(argv[i], ";") && strcmp(argv[i], "|")) ;
		if (strcmp(argv[0], "cd") == 0 && i == 2)
		{
			if (chdir(argv[1]) != 0)
				write_fd2("error: cd: cannot change directory to ", argv[1]);
		}
		else if (strcmp(argv[0], "cd") == 0 && i != 2)
			write_fd2("error: cd: bad arguments", NULL);
		else if(i > 0 && (argv[i] == NULL || strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0) && pipe(pip) == 0)
		{
			// dprintf(2, "\nGEN-%d                  %2d -> ... -> %2d %2d\n", j, CHILDIN, CHILDOUT, NXT_CHILDIN);
			if (fork() != 0)
			{
				close(CHILDIN);
				CHILDIN = NXT_CHILDIN;
				close(CHILDOUT);
				// dprintf(2, "PAR-%d %2d -> ... -> %2d,                 %2d\n\n", j, STDIN, STDOUT,  NXT_CHILDIN);
				// while(waitpid(-1, NULL, WUNTRACED) != -1) ; // close(tmp_f d), waits child complete / stopped, WUNTRACED = stopped but not traced via ptrace
				waitpid(-1, NULL, WUNTRACED); // close(tmp_f d), waits child complete / stopped, WUNTRACED = stopped but not traced via ptrace
			}
			else
			{
				if (argv[i] == NULL || strcmp(argv[i], ";") == 0)
				{
					close(CHILDOUT);
					CHILDOUT  = dup(STDOUT);
					close(NXT_CHILDIN);
					NXT_CHILDIN = dup(STDIN);
				}
				dup2(CHILDIN, STDIN);
				close(CHILDIN);
				dup2(CHILDOUT, STDOUT); // close(fd[0]);
				close(CHILDOUT);
				argv[i] = NULL; // overwrite ; | NULL with NULL -> no impact in the parent
				// dprintf(2, "CHL-%d %2d -> ... -> %2d, %2d -> ... -> %2d %2d\n", j, CHILDIN, CHILDOUT, CHILDIN, CHILDOUT, NXT_CHILDIN);
				execve(argv[0], argv, env);
				write_fd2("error: cannot execute ", argv[0]);
			}
		}
		j++;
	}
	close(CHILDIN);
	//while (1); // if test
}

/bin/ls microshell.c
microshell.c

/bin/ls salut

;

; ;

; ; /bin/echo OK
OK

; ; /bin/echo OK ;
OK

; ; /bin/echo OK ; ;
OK

; ; /bin/echo OK ; ; ; /bin/echo OK
OK
OK

/bin/ls | /usr/bin/grep microshell
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell
microshell
microshell.c

/bin/ls | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo ftest ;
     1	microshell
     2	microshell.c
dernier
ftest

/bin/echo ftest ; /bin/echo ftewerwerwerst ; /bin/echo werwerwer ; /bin/echo qweqweqweqew ; /bin/echo qwewqeqrtregrfyukui ;
ftest
ftewerwerwerst
werwerwer
qweqweqweqew
qwewqeqrtregrfyukui

/bin/ls ; /bin/ls microshell.c ; /bin/ls Readme.md ;
a.out
leaks.res
microshell
microshell.c
out.res
Readme.md
test11.txt
test1.txt
test21.txt
test2.txt
test.sh
microshell.c
Readme.md

/bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ;
microshell
microshell.c
microshell
microshell.c
microshell
microshell.c
microshell
microshell.c

/bin/cat Readme.md | /usr/bin/grep a | /usr/bin/grep b ; /bin/cat Readme.md ;
Ecrire un programme qui aura ressemblera à un executeur de commande shell
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'arguments votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.
N'oubliez pas de passer les variables d'environment à execve
Write a program that will behave like executing a shell command
- The command line to execute will be the arguments of this program
- Executable's path will be absolute or relative but your program must not build a path (from the PATH variable for example)
- You must implement "|" and ";" like in bash
	- we will never try a "|" immediately followed or preceded by nothing or "|" or ";"
- Your program must implement the built-in command cd only with a path as argument (no '-' or without parameters)
	- if cd has the wrong number of argument your program should print in STDERR "error: cd: bad arguments" followed by a '\n'
	- if cd failed your program should print in STDERR "error: cd: cannot change directory to path_to_change" followed by a '\n' with path_to_change replaced by the argument to cd
	- a cd command will never be immediately followed or preceded by a "|"
- You don't need to manage environment variables ($BLA ...)
- If a system call, except execve and chdir, returns an error your program should immediatly print "error: fatal" in STDERR followed by a '\n' and the program should exit
- If execve failed you should print "error: cannot execute executable_that_failed" in STDERR followed by a '\n' with executable_that_failed replaced with the path of the failed executable (It should be the first argument of execve)
- Your program should be able to manage more than hundreds of "|" even if we limit the number of "open files" to less than 30.
Don't forget to pass the environment variable to execve
- Вы должны реализовать " | "и"; " как в bash
- если cd имеет неправильный номер аргумента, ваша программа должна напечатать в STDERR "error: cd: bad arguments", за которым следует '\n'
- Если execve не удалось, вы должны напечатать "error: cannot execute executable_that_failed" в STDERR, а затем '\n ' с executable_that_failed, замененным путем неудачного исполняемого файла (это должен быть первый аргумент execve)
Assignment name  : microshell

Expected files   : microshell.c

Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'arguments votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.
N'oubliez pas de passer les variables d'environment à execve
Ne fuitez pas de file descriptor!

Par exemple, la commande suivante doit marcher:

```
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
```
```
$>./microshell /bin/echo WOOT "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
WOOT ; /bin/echo NOPE; ; ;
YEAH
```

________________________________________________________________________________________________________________________

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

for example this should work:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Hints:
Don't forget to pass the environment variable to execve

Hints:
Do not leak file descriptors!
_____________________________________________________________________________________________________________________________

Напишите программу, которая будет вести себя как выполнение команды оболочки	
- Командной строкой для выполнения будут аргументы этой программы
- Путь исполняемого файла будет абсолютным или относительным, но ваша программа не должна создавать путь (например, из переменной PATH)
- Вы должны реализовать " | "и"; " как в bash
- мы никогда не будем пробовать " | "сразу после или перед ничем или" | " или ";"
- Ваша программа должна реализовывать встроенную команду cd только с путем в качестве аргумента (без '-' или без параметров)
- если cd имеет неправильный номер аргумента, ваша программа должна напечатать в STDERR "error: cd: bad arguments", за которым следует '\n'
- если cd не удался, ваша программа должна напечатать в STDERR "error: cd: cannot change directory to path_to_change", за которым следует '\n ' с path_to_change, замененным аргументом на cd
- команда cd никогда не будет немедленно следовать или предшествовать команде "|"
- Вам не нужно управлять любыми типами подстановочных знаков ( * , ~ и т. д...)
- Вам не нужно управлять переменными окружения ($BLA ...)
- Если системный вызов, кроме execve и chdir, возвращает ошибку, ваша программа должна немедленно напечатать "error: fatal" в STDERR, за которым следует '\n', и программа должна выйти
- Если execve не удалось, вы должны напечатать "error: cannot execute executable_that_failed" в STDERR, а затем '\n ' с executable_that_failed, замененным путем неудачного исполняемого файла (это должен быть первый аргумент execve)
- Ваша программа должна уметь управлять более чем сотнями"|", даже если мы ограничим количество "открытых файлов" менее чем 30.

Подсказки:
Не забудьте передать переменную окружения в execve

Подсказки:
Не допускайте утечки файловых дескрипторов!

/bin/cat Readme.md ; /bin/cat Readme.md | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat Readme.md
Assignment name  : microshell

Expected files   : microshell.c

Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'arguments votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.
N'oubliez pas de passer les variables d'environment à execve
Ne fuitez pas de file descriptor!

Par exemple, la commande suivante doit marcher:

```
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
```
```
$>./microshell /bin/echo WOOT "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
WOOT ; /bin/echo NOPE; ; ;
YEAH
```

________________________________________________________________________________________________________________________

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

for example this should work:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Hints:
Don't forget to pass the environment variable to execve

Hints:
Do not leak file descriptors!
_____________________________________________________________________________________________________________________________

Напишите программу, которая будет вести себя как выполнение команды оболочки	
- Командной строкой для выполнения будут аргументы этой программы
- Путь исполняемого файла будет абсолютным или относительным, но ваша программа не должна создавать путь (например, из переменной PATH)
- Вы должны реализовать " | "и"; " как в bash
- мы никогда не будем пробовать " | "сразу после или перед ничем или" | " или ";"
- Ваша программа должна реализовывать встроенную команду cd только с путем в качестве аргумента (без '-' или без параметров)
- если cd имеет неправильный номер аргумента, ваша программа должна напечатать в STDERR "error: cd: bad arguments", за которым следует '\n'
- если cd не удался, ваша программа должна напечатать в STDERR "error: cd: cannot change directory to path_to_change", за которым следует '\n ' с path_to_change, замененным аргументом на cd
- команда cd никогда не будет немедленно следовать или предшествовать команде "|"
- Вам не нужно управлять любыми типами подстановочных знаков ( * , ~ и т. д...)
- Вам не нужно управлять переменными окружения ($BLA ...)
- Если системный вызов, кроме execve и chdir, возвращает ошибку, ваша программа должна немедленно напечатать "error: fatal" в STDERR, за которым следует '\n', и программа должна выйти
- Если execve не удалось, вы должны напечатать "error: cannot execute executable_that_failed" в STDERR, а затем '\n ' с executable_that_failed, замененным путем неудачного исполняемого файла (это должен быть первый аргумент execve)
- Ваша программа должна уметь управлять более чем сотнями"|", даже если мы ограничим количество "открытых файлов" менее чем 30.

Подсказки:
Не забудьте передать переменную окружения в execve

Подсказки:
Не допускайте утечки файловых дескрипторов!
N'oubliez pas de passer les variables d'environment à execve
Assignment name  : microshell

Expected files   : microshell.c

Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'arguments votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.
N'oubliez pas de passer les variables d'environment à execve
Ne fuitez pas de file descriptor!

Par exemple, la commande suivante doit marcher:

```
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
```
```
$>./microshell /bin/echo WOOT "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
WOOT ; /bin/echo NOPE; ; ;
YEAH
```

________________________________________________________________________________________________________________________

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

for example this should work:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Hints:
Don't forget to pass the environment variable to execve

Hints:
Do not leak file descriptors!
_____________________________________________________________________________________________________________________________

Напишите программу, которая будет вести себя как выполнение команды оболочки	
- Командной строкой для выполнения будут аргументы этой программы
- Путь исполняемого файла будет абсолютным или относительным, но ваша программа не должна создавать путь (например, из переменной PATH)
- Вы должны реализовать " | "и"; " как в bash
- мы никогда не будем пробовать " | "сразу после или перед ничем или" | " или ";"
- Ваша программа должна реализовывать встроенную команду cd только с путем в качестве аргумента (без '-' или без параметров)
- если cd имеет неправильный номер аргумента, ваша программа должна напечатать в STDERR "error: cd: bad arguments", за которым следует '\n'
- если cd не удался, ваша программа должна напечатать в STDERR "error: cd: cannot change directory to path_to_change", за которым следует '\n ' с path_to_change, замененным аргументом на cd
- команда cd никогда не будет немедленно следовать или предшествовать команде "|"
- Вам не нужно управлять любыми типами подстановочных знаков ( * , ~ и т. д...)
- Вам не нужно управлять переменными окружения ($BLA ...)
- Если системный вызов, кроме execve и chdir, возвращает ошибку, ваша программа должна немедленно напечатать "error: fatal" в STDERR, за которым следует '\n', и программа должна выйти
- Если execve не удалось, вы должны напечатать "error: cannot execute executable_that_failed" в STDERR, а затем '\n ' с executable_that_failed, замененным путем неудачного исполняемого файла (это должен быть первый аргумент execve)
- Ваша программа должна уметь управлять более чем сотнями"|", даже если мы ограничим количество "открытых файлов" менее чем 30.

Подсказки:
Не забудьте передать переменную окружения в execve

Подсказки:
Не допускайте утечки файловых дескрипторов!

; /bin/cat Readme.md ; /bin/cat Readme.md | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat Readme.md
Assignment name  : microshell

Expected files   : microshell.c

Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'arguments votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.
N'oubliez pas de passer les variables d'environment à execve
Ne fuitez pas de file descriptor!

Par exemple, la commande suivante doit marcher:

```
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
```
```
$>./microshell /bin/echo WOOT "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
WOOT ; /bin/echo NOPE; ; ;
YEAH
```

________________________________________________________________________________________________________________________

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

for example this should work:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Hints:
Don't forget to pass the environment variable to execve

Hints:
Do not leak file descriptors!
_____________________________________________________________________________________________________________________________

Напишите программу, которая будет вести себя как выполнение команды оболочки	
- Командной строкой для выполнения будут аргументы этой программы
- Путь исполняемого файла будет абсолютным или относительным, но ваша программа не должна создавать путь (например, из переменной PATH)
- Вы должны реализовать " | "и"; " как в bash
- мы никогда не будем пробовать " | "сразу после или перед ничем или" | " или ";"
- Ваша программа должна реализовывать встроенную команду cd только с путем в качестве аргумента (без '-' или без параметров)
- если cd имеет неправильный номер аргумента, ваша программа должна напечатать в STDERR "error: cd: bad arguments", за которым следует '\n'
- если cd не удался, ваша программа должна напечатать в STDERR "error: cd: cannot change directory to path_to_change", за которым следует '\n ' с path_to_change, замененным аргументом на cd
- команда cd никогда не будет немедленно следовать или предшествовать команде "|"
- Вам не нужно управлять любыми типами подстановочных знаков ( * , ~ и т. д...)
- Вам не нужно управлять переменными окружения ($BLA ...)
- Если системный вызов, кроме execve и chdir, возвращает ошибку, ваша программа должна немедленно напечатать "error: fatal" в STDERR, за которым следует '\n', и программа должна выйти
- Если execve не удалось, вы должны напечатать "error: cannot execute executable_that_failed" в STDERR, а затем '\n ' с executable_that_failed, замененным путем неудачного исполняемого файла (это должен быть первый аргумент execve)
- Ваша программа должна уметь управлять более чем сотнями"|", даже если мы ограничим количество "открытых файлов" менее чем 30.

Подсказки:
Не забудьте передать переменную окружения в execve

Подсказки:
Не допускайте утечки файловых дескрипторов!
N'oubliez pas de passer les variables d'environment à execve
Assignment name  : microshell

Expected files   : microshell.c

Allowed functions: malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp

Ecrire un programme qui aura ressemblera à un executeur de commande shell
- La ligne de commande à executer sera passer en argument du programme
- Les executables seront appelés avec un chemin relatif ou absolut mais votre programme ne devra pas construire de chemin (en utilisant la variable d environment PATH par exemple)
- Votre programme doit implementer "|" et ";" comme dans bash
	- Nous n'essaierons jamais un "|" immédiatement suivi ou précédé par rien ou un autre "|" ou un ";"
- Votre programme doit implementer la commande "built-in" cd et seulement avec un chemin en argument (pas de '-' ou sans argument)
	- si cd n'a pas le bon nombre d'arguments votre programme devra afficher dans STDERR "error: cd: bad arguments" suivi d'un '\n'
	- si cd a echoué votre programme devra afficher dans STDERR "error: cd: cannot change directory to path_to_change" suivi d'un '\n' avec path_to_change remplacer par l'argument à cd
	- une commande cd ne sera jamais immédiatement précédée ou suivie par un "|"
- Votre programme n'a pas à gerer les "wildcards" (*, ~ etc...)
- Votre programme n'a pas à gerer les variables d'environment ($BLA ...)
- Si un appel systeme, sauf execve et chdir, retourne une erreur votre programme devra immédiatement afficher dans STDERR "error: fatal" suivi d'un '\n' et sortir
- Si execve echoue votre programme doit afficher dans STDERR "error: cannot execute executable_that_failed" suivi d'un '\n' en ayant remplacé executable_that_failed avec le chemin du programme qui n'a pu etre executé (ca devrait etre le premier argument de execve)
- Votre programme devrait pouvoir accepter des centaines de "|" meme si la limite du nombre de "fichier ouvert" est inferieur à 30.
N'oubliez pas de passer les variables d'environment à execve
Ne fuitez pas de file descriptor!

Par exemple, la commande suivante doit marcher:

```
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
```
```
$>./microshell /bin/echo WOOT "; /bin/echo NOPE;" "; ;" ";" /bin/echo YEAH
WOOT ; /bin/echo NOPE; ; ;
YEAH
```

________________________________________________________________________________________________________________________

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

for example this should work:
$>./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell
microshell
i love my microshell
$>

Hints:
Don't forget to pass the environment variable to execve

Hints:
Do not leak file descriptors!
_____________________________________________________________________________________________________________________________

Напишите программу, которая будет вести себя как выполнение команды оболочки	
- Командной строкой для выполнения будут аргументы этой программы
- Путь исполняемого файла будет абсолютным или относительным, но ваша программа не должна создавать путь (например, из переменной PATH)
- Вы должны реализовать " | "и"; " как в bash
- мы никогда не будем пробовать " | "сразу после или перед ничем или" | " или ";"
- Ваша программа должна реализовывать встроенную команду cd только с путем в качестве аргумента (без '-' или без параметров)
- если cd имеет неправильный номер аргумента, ваша программа должна напечатать в STDERR "error: cd: bad arguments", за которым следует '\n'
- если cd не удался, ваша программа должна напечатать в STDERR "error: cd: cannot change directory to path_to_change", за которым следует '\n ' с path_to_change, замененным аргументом на cd
- команда cd никогда не будет немедленно следовать или предшествовать команде "|"
- Вам не нужно управлять любыми типами подстановочных знаков ( * , ~ и т. д...)
- Вам не нужно управлять переменными окружения ($BLA ...)
- Если системный вызов, кроме execve и chdir, возвращает ошибку, ваша программа должна немедленно напечатать "error: fatal" в STDERR, за которым следует '\n', и программа должна выйти
- Если execve не удалось, вы должны напечатать "error: cannot execute executable_that_failed" в STDERR, а затем '\n ' с executable_that_failed, замененным путем неудачного исполняемого файла (это должен быть первый аргумент execve)
- Ваша программа должна уметь управлять более чем сотнями"|", даже если мы ограничим количество "открытых файлов" менее чем 30.

Подсказки:
Не забудьте передать переменную окружения в execve

Подсказки:
Не допускайте утечки файловых дескрипторов!

