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
