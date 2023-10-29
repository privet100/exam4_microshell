	// dprintf(2, "\nGEN-%d %2d -> ... -> %2d,                 %2d\n", j, STDIN, STDOUT, CHILDIN);
			// dprintf(2, "\nGEN-%d                  %2d -> ... -> %2d %2d\n", j, CHILDIN, CHILDOUT, NXT_CHILD_WILL_READ);
				// dprintf(2, "PAR-%d %2d -> ... -> %2d,                 %2d\n\n", j, STDIN, STDOUT,  NXT_CHILD_WILL_READ);
				// dprintf(2, "CHL-%d %2d -> ... -> %2d, %2d -> ... -> %2d %2d\n", j, CHILDIN, CHILDOUT, CHILDIN, CHILDOUT, NXT_CHILD_WILL_READ);
#include <stdlib.h> // tmp
#include <stdio.h> // tmp
	//while (1); // if test

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
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
	int CHILDIN = dup(STDIN);
	int pip[2];
	(void)argc;

	dprintf(2, "+ in  %d\n", CHILDIN);
	while (argv[i] && argv[i + 1]) //check the end
	{
		argv = &argv[i + 1]; //new argv starts after ; or |
		i = -1;
		while (argv[++i] && strcmp(argv[i], ";") && strcmp(argv[i], "|")) ;
		if (strcmp(argv[0], "cd") == 0 && i != 2)
			write_fd2("error: cd: bad arguments", NULL);
		if (strcmp(argv[0], "cd") == 0 && i == 2 && chdir(argv[1]) != 0)
			write_fd2("error: cd: cannot change directory to ", argv[1]);
		if (strcmp(argv[0], "cd") != 0 && i > 0 && (argv[i] == NULL || strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0))
		{
			dprintf(2, "- out %d\n", CHILDOUT);
			close(CHILDOUT);
			// dprintf(2, "- nxt %d\n", NXT_CHILDIN);
			// close(NXT_CHILDIN);
			if (pipe(pip) != 0)
				continue ;
			dprintf(2, "+ out %d\n", CHILDOUT);
			dprintf(2, "+ nxt %d\n", NXT_CHILDIN);
			if (fork() != 0)
			{
				dprintf(2, "- in  %d\n", CHILDIN);
				close(CHILDIN);
				dprintf(2, "+ in  %d = nxt\n", CHILDIN);
				CHILDIN = NXT_CHILDIN;
				dprintf(2, "- out %d\n", CHILDOUT);
				close(CHILDOUT);
				waitpid(-1, NULL, WUNTRACED); // waits child complete / stopped, WUNTRACED = stopped but not traced via ptrace
			}
			else
			{
				dup2 (CHILDIN, STDIN);
				close(CHILDIN);
				if (argv[i] != NULL && strcmp(argv[i], "|") == 0)
					dup2 (CHILDOUT, STDOUT);
				close(CHILDOUT);
				close(NXT_CHILDIN);
				argv[i] = NULL; // overwrite ; | NULL with NULL, no impact in the parent
				execve(argv[0], argv, env);
				write_fd2("error: cannot execute ", argv[0]);
			}
		}
	}
	dprintf(2, "- in  %d\n", CHILDIN);
	close(CHILDIN);
}
