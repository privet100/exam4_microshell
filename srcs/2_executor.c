#include "microshell.h"

#define DIR_ERR	": Is a directory\n"

int	manage_dup(int end[4], t_cmd *cmd, int nb)
{
	const int	even = !(nb % 2);

	if (cmd->fd_in != -1 && dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (1);
	else if (cmd->fd_in == -1 && nb > 1 && !even && dup2(end[2], 0) == -1)
		return (1);
	else if (cmd->fd_in == -1 && nb > 1 && even && dup2(end[0], 0) == -1)
		return (1);
	if (cmd->fd_out != -1 && dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (1);
	else if (cmd->fd_out == -1 && cmd->next && !even && dup2(end[1], 1) == -1)
		return (1);
	else if (cmd->fd_out == -1 && cmd->next && even && dup2(end[3], 1) == -1)
		return (1);
	return (0);
}

int	close_fork(t_cmd *cmd, int end[4], int nb)
{
	int	ret;

	ret = 0;
	if ((cmd->fd_in != -1 && close(cmd->fd_in)) || (cmd->fd_out != -1 && close(cmd->fd_out)))
		ret = 1;
	if (nb == 1 && !cmd->next)
		return (0);
	else if (nb == 1 && (close(end[0]) || close(end[1])))
		return (1);
	else if (nb > 1 && !cmd->next && !(nb % 2) && (close(end[0]) || close(end[1])))
		return (1);
	else if (nb > 2 && !cmd->next && nb % 2 && (close(end[2]) || close(end[3])))
		return (1);
	else if (nb > 1 && cmd->next && ((end[0] != -1 && close(end[0])) || (end[1] != -1 && close(end[1])) || (end[2] != -1 && close(end[2])) || (end[3] != -1 && close(end[3]))))
		return (1);
	return (ret);
}

void	exit_fork(t_sh *sh, int ret, char *error)
{
	free_lstcmd(&(sh->cmd));
	free(sh->line);
	if (errno && error)
		ft_putstr_fd2(ERR_MSG, NULL);
	exit(ret);
}

void	ft_fork(t_sh *sh, t_cmd *cmd, int nb, char **envp)
{
	int	ret;
	
	if (!cmd->cmd && (close_fork(cmd, sh->end, nb) || 1))
		exit_fork(sh, 0, NULL);
	ret = 0;
	ret = manage_dup(sh->end, cmd, nb);
	if (ret && (close_fork(cmd, sh->end, nb) || 1))
		exit_fork(sh, ret, ERR_MSG);
	cmd->path = ft_strdup(cmd->cmd[0]);
	if (!cmd->path && (close_fork(cmd, sh->end, nb) || 1))
		exit_fork(sh, 1, ERR_MSG);
	if (close_fork(cmd, sh->end, nb))
		exit_fork(sh, ret, ERR_MSG);
	if (execve(cmd->path, cmd->cmd, envp) == -1)
		ft_putstr_fd2("error: cannot execute ", cmd->cmd[1]); // exit
	exit_fork(sh, ret, NULL);
}

int	close_fd(t_cmd *cmd, int end[4], int nb)
{
	const int	even = !(nb % 2);

	if (nb == 1 && !cmd->next)
		return (0);
	if (nb > 1 && even && (close(end[0]) || close(end[1])))
		return (1);
	else if (nb > 2 && !even && (close(end[2]) || close(end[3])))
		return (1);
	return (0);
}

int	open_pipe(t_sh *sh, int nb)
{
	if (nb % 2 && pipe(sh->end))
	{
		if (nb > 1 && (close(sh->end[2]) || close(sh->end[3])))
			ft_putstr_fd2(ERR_MSG, NULL);
		return (1);
	}
	else if (!(nb % 2) && pipe(sh->end + 2))
	{
		if (close(sh->end[0]) || close(sh->end[1]))
			ft_putstr_fd2(ERR_MSG, NULL);
		return (1);
	}
	return (0);
}

int	catch_status(t_cmd *cmd)
{
	int	wstatus;

	while (cmd)
	{
		if (cmd->pid)
			waitpid(cmd->pid, &wstatus, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 2)
	{
		ft_putstr_fd2("\n", NULL);
		rl_on_new_line();
		return (130);
	}
	else if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == 3)
	{
		ft_putstr_fd2(ERR_MSG, NULL);
		rl_on_new_line();
		return (131);
	}
	return (-1);
}

int	executor(t_sh *sh, char **envp)
{
	t_cmd	*tmp;
	int		nb;

	if (sh->cmd->cmd && strcmp(sh->cmd->cmd[0], "cd") == 0)
	{
		if (sh->cmd->cmd[1] == NULL || sh->cmd->cmd[1][0] == '-' || sh->cmd->cmd[2] != NULL)
			return (ft_putstr_fd2("error: cd: bad arguments\n", NULL), 1);
		if (chdir(sh->cmd->cmd[1]) == -1)
			return (ft_putstr_fd2("error: cd: cannot change directory ", sh->cmd->cmd[1]), 1);
		return (0);
	}
	tmp = sh->cmd;
	nb = 0;
	while (tmp && ++nb)
	{
		if (tmp->next && open_pipe(sh, nb))
			return (catch_status(sh->cmd), ft_putstr_fd2(ERR_MSG, NULL), 1);
		tmp->pid = fork();
		if (tmp->pid == -1)
			return (catch_status(sh->cmd), ft_putstr_fd2(ERR_MSG, NULL), 254);
		if (tmp->pid == 0)
			ft_fork(sh, tmp, nb, envp);
		if (close_fd(tmp, sh->end, nb))
			return (catch_status(sh->cmd), ft_putstr_fd2(ERR_MSG, NULL), 1);
		tmp = tmp->next;
	}
	return (catch_status(sh->cmd));
}
