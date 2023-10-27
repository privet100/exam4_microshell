#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>

# define ERR_MSG 		"error: fatal\n"

typedef struct s_cmd
{
	char			*path;
	char			**cmd;
	int				pid;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_sh
{
	char			*line;
	t_cmd			*cmd;
	int				fd_stdin;
	int				fd_stdout;
	int				end[4];
}	t_sh;

/* executor.c */
int		executor(t_sh *sh, char **envp);
void	ft_fork(t_sh *sh, t_cmd *cmd, int nb, char **envp);
void	exit_fork(t_sh *sh, int ret, char *error);

/* utils.c */
char	**ft_arrdup(char **arr, int size);
int		ft_arrlen(char **arr);
void	free_arr(char **arr);
void	lstcmd_add_back(t_cmd **cmd, t_cmd *new);
void	free_lstcmd(t_cmd **cmd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
#endif
