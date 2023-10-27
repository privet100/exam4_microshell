// https://github.com/shackbei/microshell-42/blob/main/microshell.c
// https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/test.sh*/

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int	ft_putstr_fd2(char *s1, char *s2)
{
	while (*s1)
		write(2, s1++, 1);
	while(s2 && *s2)
		write(2, s2++, 1);
	write(2, "\n", 1);
	return (1);
}

int ft_execute(char *argv[], int i, int tmp_fd, char *env[])
{
	// overwrite ; or | or NULL with NULL -> input for execve, no impact in the parent process
	argv[i] = NULL;
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(argv[0], argv, env);
	return (ft_putstr_fd2("error: cannot execute ", argv[0]));
}

int	main(int argc, char *argv[], char *env[])
{
	int	i;
	int fd[2];
	int tmp_fd;
	(void)argc;	// -Wall -Wextra -Werror

	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (argv[i] && argv[i + 1]) //check the end
	{
		argv = &argv[i + 1];	//the new argv start after the ; or |
		i = 0; //count until we have all informations to execute the next child
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[0], "cd") == 0 && i != 2)
			ft_putstr_fd2("error: cd: bad arguments", NULL);
		else if (strcmp(argv[0], "cd") == 0 && i == 2 && chdir(argv[1]) != 0)
			ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]);
		else if (i > 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
		{
			if ( fork() == 0)
				ft_execute(argv, i, tmp_fd, env)
			else
			{
				close(tmp_fd);
				while(waitpid(-1, NULL, WUNTRACED) != -1) ;
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else if(i > 0 && strcmp(argv[i], "|") == 0)
		{
			pipe(fd);
			if ( fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO); //
				close(fd[0]);               //
				close(fd[1]);               //
				if (ft_execute(argv, i, tmp_fd, env))
					return (1);
			}
			else
			{
				close(fd[1]);               //
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	// while (1); // if test
}
