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

# define UNCL_QUOTES	"minishell: syntax error: unclosed quotes\n"
# define PIP_SYN_ERR	"minishell: syntax error near unexpected token '|'\n"
# define TOK_SYN_ERR	"minishell: syntax error near unexpected token\n"
# define ERR_MSG 		"error: fatal\n"
# define TRUE	1
# define FALSE	0

<<<<<<< HEAD
=======
typedef enum e_redr_type
{
	IN = 1,
	H_DOC,
	OUT,
	OUT_A,
}	t_redr_type;

typedef struct s_redir
{
	char			*file;
	int				type;
	int				fd;
	struct s_redir	*next;
}	t_redir;

>>>>>>> parent of 383ea99 (remove struct redir)
typedef struct s_cmd
{
	char			*path;
	char			**cmd;
	int				pid;
	struct s_redir	*redir;
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
	unsigned char	exit_s;
}	t_sh;

/* executor.c */
int		executor(t_sh *sh, char **envp);
void	ft_fork(t_sh *sh, t_cmd *cmd, int nb, char **envp);
void	exit_fork(t_sh *sh, int ret, char *error);

/* utils.c */
<<<<<<< HEAD
int		ft_putstr_fd2(char *s1, char s2);
=======
int	ft_putstr_fd2(char *s1, char *s2);
>>>>>>> add42958a84c4f6134ee6913937325de6c526cc0
char	**ft_arrdup(char **arr, int size);
int		ft_arrlen(char **arr);
void	free_arr(char **arr);
void	lstcmd_add_back(t_cmd **cmd, t_cmd *new);
<<<<<<< HEAD
void	free_lstcmd(t_cmd **cmd);
int		ft_putstr_fd2(char *s1, char *s2);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
=======
void	lstredir_add_back(t_redir **redir, t_redir *new);

// utils ft
char		**ft_split(char const *s, char c);
void		ft_putstr_fd(char *s, int fd);
char		*ft_itoa(int n);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s);
>>>>>>> parent of 383ea99 (remove struct redir)
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
#endif
