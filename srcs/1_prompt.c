#include "microshell.h"

int	skip_quotes(char *line, char type)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != type)
		i++;
	return (i);
}

int	in_quotes(char *str)
{
	return (str[0 + 1] && ((str[0] == '"' && ft_strchr(&str[0 + 1], '"')) || (str[0] == '\'' && ft_strchr(&str[0 + 1], '\''))));
}

int	count_cmd_line(char *str)
{
	int	j;

	j = 0;
	while (str[j] != '|' && str[j])
	{
		if (in_quotes(&str[j]))
			j += skip_quotes(&str[j + 1], str[j]) + 1;
		j++;
	}
	return (j);
}

char	**redo_cmd(char ***og, int *i)
{
	char	**arr;

	if (*og)
	{
		arr = ft_arrdup(*og, ft_arrlen(*og) + 1);
		free_arr(*og);
	}
	else
	{
		arr = malloc(2 * sizeof(char *));
		arr[0] = NULL;
	}
	if (!arr)
		return (NULL);
	*i = 0;
	while (arr && arr[*i])
		(*i)++;
	return (arr);
}

int	ft_is_charset(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_str_size(char *str)
{
	int		i;
	char	type;

	i = 0;
	type = 0;
	while (str[i] && (!ft_is_charset(str[i], " \t<>") || type))
	{
		if (str[i] == '\'' && !type && str[i + 1]
			&& ft_strchr(&str[i + 1], '\''))
		{
			type = '\'';
			i++;
		}
		else if (str[i] == '"' && !type && str[i + 1]
			&& ft_strchr(&str[i + 1], '"'))
		{
			type = '"';
			i++;
		}
		if (type && str[i] == type)
			type = 0;
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	len;

	src_len = ft_strlen(src);
	len = -1;
	if (size > 0)
	{
		while (++len < size - 1 && src[len])
			dst[len] = src[len];
		dst[len] = 0;
	}
	return (src_len);
}

char	*unquote(char *str, int count)
{
	char	*unq;
	int		i;
	int		j;

	if (count < 2 || (!str && !str[0]))
		return (str);
	unq = malloc((ft_strlen(str) - count + 1) * sizeof(char));
	if (!unq)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (in_quotes(&str[i]) && ft_strlcpy(&unq[j], &str[i + 1], skip_quotes(&str[i + 1], str[i]) + 1))
		{
			j += skip_quotes(&str[i + 1], str[i]);
			i += skip_quotes(&str[i + 1], str[i]) + 2;
		}
		else
			unq[j++] = str[i++];
	}
	unq[j] = 0;
	free(str);
	return (unq);
}

int	count_quotes(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (in_quotes(&str[i]))
		{
			i += skip_quotes(&str[i + 1], str[i]) + 1;
			count += 2;
		}
		i++;
	}
	return (count);
}

char	**add_cmd(char *str, char ***og, int *ind)
{
	int		len;
	char	**arr;
	int		i;

	i = 0;
	arr = redo_cmd(og, &i);
	if (!arr)
		return (NULL);
	len = get_str_size(str);
	arr[i] = ft_substr(str, 0, len);
	if (!arr[i])
		return (free_arr(arr), NULL);
	arr[i] = unquote(arr[i], count_quotes(arr[i]));
	if (!arr[i])
		return (free_arr(arr), NULL);
	arr[i + 1] = NULL;
	*og = arr;
	(*ind) = (*ind) + len;
	return (*og);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v');
}

int	add_cmd_lst_loop(char *line, t_cmd **cmd)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!add_cmd(&line[i], &((*cmd)->cmd), &i))
			return (free(line), ft_putstr_fd2(ERR_MSG, NULL), 1);
		if (i < 0)
			return (free(line), ft_putstr_fd2(TOK_SYN_ERR, NULL), 2);
	}
	free(line);
	return (0);
}

t_cmd	*init_cmd_lst(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->path = NULL;
	cmd->cmd = NULL;
	cmd->next = NULL;
	cmd->pid = -1;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	return (cmd);
}

int	add_cmd_lst(t_sh *sh, char *cmd_line)
{
	t_cmd	*cmd;
	char	*line;
	int		ret;

	if (!cmd_line)
		return (ft_putstr_fd2(ERR_MSG, NULL), 1);
	line = ft_strdup(cmd_line); // need strdup ?
	free(cmd_line);
	if (!*line)
		return (free(line), ft_putstr_fd2(PIP_SYN_ERR, NULL), 2);
	cmd = init_cmd_lst();
	if (!cmd)
		return (free(line), ft_putstr_fd2(ERR_MSG, NULL), 2);
	ret = add_cmd_lst_loop(line, &cmd);
	if (ret)
		return (free_lstcmd(&cmd), ret);
	lstcmd_add_back(&(sh->cmd), cmd);
	return (0);
}

char	setup_line(t_sh *sh)
{
	int	i;
	int	j;
	int	ret;

	i = -1;
	while (sh->line[++i])
	{
		j = count_cmd_line(&sh->line[i]);
		if (sh->line[i + j] == '|' || !sh->line[i + j])
		{
			ret = add_cmd_lst(sh, ft_substr(sh->line, i, j));
			if (ret)
				return (ret);
		}
		i = i + j;
		if (!sh->line[i])
			break ;
	}
	if (sh->line[i - 1] == '|')
		return (ft_putstr_fd2(PIP_SYN_ERR, NULL), 2);
	return (0);
}

//	if (unclosed_quote s(sh->line))
//		return (ft_putstr_fd(UNCL_QUOTES, 2), 2);
int	treat_line(t_sh *sh, char **envp)
{
	int		ret;

	if (!sh->line || (sh->line && !*sh->line))
		return (0);
	if (!*sh->line)
		return (0);
	ret = setup_line(sh);
	if (ret)
		return (free_lstcmd(&(sh->cmd)), ret);
	if (sh->cmd)
		ret = executor(sh, envp);
	return (ret);
}

void	reset_sh(t_sh *sh)
{
	// free_lstcmd(&(sh->cmd));
	// if (sh->line != NULL)
	// 	free(sh->line);
	sh->line = NULL;
	sh->cmd = NULL;
	sh->fd_stdin = 0;
	sh->fd_stdout = 1;
	ft_memset(sh->end, -1, 4 * sizeof(int));
}

int	main(int ac, char **av, char **envp)
{
	t_sh	sh;

	while (ac > 1)
	{
		reset_sh(&sh);
		sh.line = readline("microshell$ ");
		if (!sh.line)
			break ;
		if (*(sh.line))
			treat_line(&sh, envp);
	}
	return (exit_fork(&sh, 0, NULL), (void)av, 0);
}
