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
	int	i;
	int pip[2];
	int fd_tmp;
	(void)argc;	// -Wall -Wextra -Werror

	i = 0;
	CHILDIN = dup(STDIN);
	dprintf(2, "\nPPP 0   %d -> ... -> %d,               %d\n", STDIN, STDOUT, CHILDIN);
	while (argv[i] && argv[i + 1]) //check the end
	{

		argv = &argv[i + 1]; //new argv start after ; or |
		i = -1;
		while (argv[++i] && strcmp(argv[i], ";") && strcmp(argv[i], "|")) ;
		if (strcmp(argv[0], "cd") == 0 && i == 2)
		{
			if (chdir(argv[1]) != 0)
				write_fd2("error: cd: cannot change directory to ", argv[1]); // do not exit
		}
		else if (strcmp(argv[0], "cd") == 0 && i != 2)
			write_fd2("error: cd: bad arguments", NULL);                      // do not exit
		else if(i > 0 && (argv[i] == NULL || strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0) && pipe(pip) == 0)
		{
			dprintf(2, "\nPPP (%d) %d -> ... -> %d, %d -> ... -> %d %d\n", i, STDIN, STDOUT, CHILDIN, CHILDOUT, NXT_CHILDIN);
			if (fork() != 0)
			{
				CHILDIN = NXT_CHILDIN; // close(fd[1]); close(tmp_f d);
				dprintf(2, "PAR (%d) %d -> ... -> %d, %d -> ... -> %d %d\n", i, STDIN, STDOUT, CHILDIN, CHILDOUT, NXT_CHILDIN);
				// while(waitpid(-1, NULL, WUNTRACED) != -1) ; // close(tmp_f d), waits child complete / enter a stopped state, WUNTRACED = child has stopped (but not traced via ptrace
				wait(NULL);
			}
			else
			{
				if (argv[i] == NULL || strcmp(argv[i], ";") == 0)
					CHILDOUT  = dup(STDOUT);
				if (argv[i] == NULL || strcmp(argv[i], ";") == 0)
					NXT_CHILDIN = dup(STDIN);
				dup2(CHILDIN, STDIN); // close(tmp_f d);
				dup2(CHILDOUT, STDOUT); // close(fd[0]); close(fd[1]);
				argv[i] = NULL; // overwrite ; | NULL with NULL -> input for execve, no impact in the parent process
				dprintf(2, "CHL (%d) %d -> ... -> %d, %d -> ... -> %d %d\n", i, CHILDIN, CHILDOUT, CHILDIN, CHILDOUT, NXT_CHILDIN);
				execve(argv[0], argv, env);
				write_fd2("error: cannot execute ", argv[0]);                // do not exit
			}
		}
		//sleep(1000);
	}
	// close(CHILDIN);
	//while (1); // if test
}
