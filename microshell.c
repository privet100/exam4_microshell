	// dprintf(2, "\nGEN-%d %2d -> ... -> %2d,                 %2d\n", j, STDIN, STDOUT, CHILDIN);
			// dprintf(2, "\nGEN-%d                  %2d -> ... -> %2d %2d\n", j, CHILDIN, CHILDOUT, NXT_CHILDIN);
				// dprintf(2, "PAR-%d %2d -> ... -> %2d,                 %2d\n\n", j, STDIN, STDOUT,  NXT_CHILDIN);
				// dprintf(2, "CHL-%d %2d -> ... -> %2d, %2d -> ... -> %2d %2d\n", j, CHILDIN, CHILDOUT, CHILDIN, CHILDOUT, NXT_CHILDIN);
// #include <stdlib.h> // tmp
// #include <stdio.h> // tmp
	//while (1); // if test

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
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
			if (fork() != 0)
			{
				close(CHILDIN);
				CHILDIN = NXT_CHILDIN;
				close(CHILDOUT);
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
				execve(argv[0], argv, env);
				write_fd2("error: cannot execute ", argv[0]);
			}
		}
		j++;
	}
	close(CHILDIN);
}
