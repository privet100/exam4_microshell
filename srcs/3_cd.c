#include "microshell.h"

void	free_(char **s)
{
	if (s != NULL && *s != NULL)
		free(*s);
}

void	remove_the_last_elt(char *path)
{
	int	i;

	if (strcmp(path, "/") == 0)
		return ;
	i = ft_strlen(path) - 1;
	if (path[i] == '/')
		path[i] = '\0';
	while (--i >= 0 && path[i] != '/')
		path[i] = '\0';
	if (path[i] == '/')
		path[i] = '\0';
}

static int	how_many_can_remove_from_path_(char *path)
{
	char	*tmp;
	int		how_many;

	how_many = 0;
	tmp = path;
	while (strncmp(tmp, "../", 3) == 0)
	{
		how_many++;
		tmp = &tmp[3];
	}
	if (strcmp(tmp, "..") == 0)
		how_many++;
	return (how_many);
}

int	how_many_removed_from_pwd(char **pwd, char *path)
{
	int	i;
	int	how_many_can_remove_from_path;

	how_many_can_remove_from_path = how_many_can_remove_from_path_(path);
	i = -1;
	while (++i < how_many_can_remove_from_path && strcmp(*pwd, "") > 0)
		remove_the_last_elt(*pwd);
	return (i);
}

void	remove_k_from_path(char **path, int k)
{
	int		i;
	int		new_begin;
	int		nb_removed_elts;

	new_begin = 0;
	nb_removed_elts = 0;
	while (new_begin < (int)ft_strlen(*path) && nb_removed_elts < k && strncmp(&((*path)[new_begin]), "../", 3) == 0)
	{
		new_begin += 3;
		nb_removed_elts++;
	}
	if (strncmp(&((*path)[new_begin]), "..", 2) == 0 && nb_removed_elts < k)
	{
		new_begin += 2;
		nb_removed_elts++;
	}
	i = -1;
	while (++i < (int)ft_strlen(*path) - new_begin + 1)
		(*path)[i] = (*path)[new_begin + i];
	while (++i < (int)ft_strlen(*path))
		(*path)[i] = '\0';
}

// path_ freed_ in the calling function
// pwd_ freed_ in the calling function
int	join_pwd_to_path(char *pwd, char **path)
{
	int		i;
	int		j;
	char	*abs_path;

	remove_k_from_path(path, how_many_removed_from_pwd(&pwd, *path));
	if (ft_strlen(pwd) == 0 && ft_strlen(*path) == 0)
		return (free(*path), *path = ft_strjoin("/", ""), 0);
	if (ft_strlen(pwd) == 0 && strncmp(*path, "..", 2) == 0)
		return (free(*path), *path = ft_strjoin("/", ""), 0);
	abs_path = (char *)malloc(ft_strlen(pwd) + ft_strlen(*path) + 2);
	if (abs_path == NULL)
		return (ft_putstr_fd2(ERR_MSG, NULL), 1);
	ft_memset(abs_path, '\0', ft_strlen(pwd) + ft_strlen(*path) + 2);
	i = -1;
	while (++i < (int)ft_strlen(pwd))
		abs_path[i] = pwd[i];
	if (ft_strlen(*path) > 0)
	{
		abs_path[i++] = '/';
		j = 0;
		while ((size_t)j < ft_strlen(*path))
			abs_path[i++] = (*path)[j++];
	}
	return (free(*path), *path = ft_strjoin(abs_path, ""), free(abs_path), 0);
}

// called only if cmd1 != NULL
// path_ freed_ in the calling function
int	put_abs_path_to_var_path(char *cmd1, char **path)
{
	char	*pwd;
	char	*path2;
	int		exit_code;

	*path = ft_strjoin(cmd1, "");
	if (*path == NULL)
		return (ft_putstr_fd2(ERR_MSG, NULL), 1);
	if ((*path)[0] == '/')
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_putstr_fd2(ERR_MSG, NULL), 1);
	if (strncmp(*path, "./", 2) == 0)
	{
		path2 = ft_strjoin(&((*path)[2]), "");
		free_(path);
		if (path2 == NULL)
			return (ft_putstr_fd2(ERR_MSG, NULL), free(pwd), 1);
		*path = path2;
	}
	exit_code = join_pwd_to_path(pwd, path);
	if (exit_code != 0)
		return (free(pwd), exit_code);
	return (free(pwd), 0);
}

int	ft_cd(char **cmd)
{
	char	*path;
	int		exit_code;

	if (cmd[1] == NULL || cmd[1][0] == '-' || cmd[2] != NULL)
		return (ft_putstr_fd2("error: cd: bad arguments\n", NULL), 1);
	if (strcmp(cmd[1], ".") == 0 || strcmp(cmd[1], "./") == 0)
		return (0);
	path = NULL;
	exit_code = put_abs_path_to_var_path(cmd[1], &path);
	if (exit_code != 0)
		return (free_(&path), exit_code);
	if (chdir(path) == -1)
		return (ft_putstr_fd2("error: cd: cannot change directory ", cmd[1]), free_(&path), 1);
	if (strcmp(cmd[1], "-") == 0)
		if ((size_t)printf("%s\n", path) != ft_strlen(path) + 1)
			return (ft_putstr_fd2(ERR_MSG, NULL), 1);
	return (free_(&path), 0);
}

int	launch_builtin(char **cmd)
{
	if (!strncmp(cmd[0], "cd", 3))
		return (ft_cd(cmd));
	return (-1);
}

int	dup_builtin_solo(t_sh *sh, t_cmd **cmd, int sof)
{
	if (sof)
	{
		if ((*cmd)->fd_in != -1)
			sh->fd_stdin = dup(STDIN_FILENO);
		if ((*cmd)->fd_out != -1)
			sh->fd_stdout = dup(STDOUT_FILENO);
		if (((*cmd)->fd_in != -1 && dup2((*cmd)->fd_in, 0) == -1) || ((*cmd)->fd_out != -1 && dup2((*cmd)->fd_out, 1) == -1))
		{
			if (((*cmd)->fd_in != -1 && close((*cmd)->fd_in)) || ((*cmd)->fd_out != -1 && close((*cmd)->fd_out)))
				return (perror(ERR_MSG), 1);
			return (perror(ERR_MSG), 1);
		}
		return (0);
	}
	if (((((*cmd)->fd_in != -1 && dup2(sh->fd_stdin, 0) == -1)) || ((*cmd)->fd_out != -1 && dup2(sh->fd_stdout, 1) == -1)))
	{
		if (((*cmd)->fd_in != -1 && close((*cmd)->fd_in)) || ((*cmd)->fd_out != -1 && close((*cmd)->fd_out)))
			return (perror(ERR_MSG), 1);
		return (perror(ERR_MSG), 1);
	}
	return (0);
}

int	builtin_solo(t_sh *sh, t_cmd **cmd)
{
	int	ret;

	ret = dup_builtin_solo(sh, cmd, 1);
	if (!ret)
		ret = launch_builtin((*cmd)->cmd);
	if (dup_builtin_solo(sh, cmd, 0))
		ret = 1;
	if (((*cmd)->fd_in != -1 && (close((*cmd)->fd_in) || (sh->fd_stdin != 0 && close(sh->fd_stdin))))
		|| ((*cmd)->fd_out != -1 && (close((*cmd)->fd_out) || (sh->fd_stdout != 1 && close(sh->fd_stdout)))))
		return (perror(ERR_MSG), 1);
	return (ret);
}
