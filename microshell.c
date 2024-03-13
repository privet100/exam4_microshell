#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define CHILDOUT    pip[1]
#define NXT_CHILDIN pip[0]

void	write_fd2(char *s1, char *s2) {
	while (*s1)
		write(2, s1++, 1);
	while(s2 && *s2)
		write(2, s2++, 1);
	write(2, "\n", 1);
}

int	main(int ac, char **av, char **env) {
	int	i = 0;
	int CHILDIN = dup(STDIN_FILENO);
	int pip[2];
	(void)ac;

	while (av[i] && av[i + 1]) { //check the end 
		for (av = &av[i + 1], i = 0; av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"); i++) ; //new av starts after ; or |
		if (i > 0  && strcmp(av[0], "cd") == 0 && (i != 2 || (i == 2 && av[1][0] == '-')))
			write_fd2("error: cd: bad arguments", NULL);
		if (i == 2 && strcmp(av[0], "cd") == 0 && chdir(av[1]) != 0)
			write_fd2("error: cd: cannot change directory to ", av[1]);
		if (i > 0  && strcmp(av[0], "cd") != 0 && (!av[i] || !strcmp(av[i], "|") || !strcmp(av[i], ";")) && !pipe(pip)) {
			if (fork() != 0) {
				close(CHILDIN);
				CHILDIN = NXT_CHILDIN;
				close(CHILDOUT);
				waitpid(-1, NULL, WUNTRACED); // child complete / stopped, WUNTRACED = stopped but not traced via ptrace
			}
			else {
				dup2 (CHILDIN, STDIN_FILENO);
				close(CHILDIN);
				if (av[i] != NULL && strcmp(av[i], "|") == 0)
					dup2 (CHILDOUT, STDOUT_FILENO);
				close(CHILDOUT);
				close(NXT_CHILDIN);
				av[i] = NULL; // overwrite ; and |  with NULL, no impact in the parent
				execve(av[0], av, env);
				write_fd2("error: cannot execute ", av[0]);
			}
		}
	}
	close(CHILDIN);
	return (1);
}
