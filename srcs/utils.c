#include "microshell.h"

int	ft_putstr_fd2(char *s1, char *s2)
{
	while (*s1)
		write(2, s1++, 1);
	while (*s2)
		write(2, s2++, 1);
	write(2, "\n", 1);
	return (1);
}

void	free_lstcmd(t_cmd **cmd)
{
	t_cmd	*first;
	t_cmd	*mem;

	if (!cmd || !*cmd)
		return ;
	first = *cmd;
	while (first)
	{
		mem = first->next;
		if (first->path)
			free(first->path);
		if (first->cmd)
			free_arr(first->cmd);
		free(first);
		first = mem;
	}
	*cmd = NULL;
}

void	lstcmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*last;

	if (!cmd)
		return ;
	if (!*cmd)
		*cmd = new;
	else
	{
		last = *cmd;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr && arr[++i])
		free(arr[i]);
	free(arr);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char **arr, int size)
{
	char	**dup;
	int		i;

	if (!arr)
		return (NULL);
	dup = malloc((size + 1) * sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			return (free_arr(dup), NULL);
	}
	dup[i] = NULL;
	return (dup);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	src_len;
	size_t	dst_len;

	len = -1;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (size + src_len);
	while (++len < size - dst_len - 1 && src[len])
		dst[len + dst_len] = src[len];
	dst[len + dst_len] = 0;
	return (dst_len + src_len);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	len;
	char	*str;

	len = -1;
	str = (char *)s;
	while (++len < n)
		str[len] = c;
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len < start)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	sub = malloc((len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	sub[len] = 0;
	while (len--)
		sub[len] = s[start + len];
	return (sub);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	len = s1_len + s2_len;
	join = malloc((len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	join[0] = 0;
	ft_strlcat(join, s1, len + 1);
	ft_strlcat(join, s2, len + 1);
	return (join);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	s_len;
	char	*dup;

	s_len = ft_strlen(s);
	dup = malloc((s_len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	len = -1;
	while (s[++len])
		dup[len] = s[len];
	dup[len] = 0;
	return (dup);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len;

	c = (unsigned char)c;
	len = -1;
	while (s[++len])
	{
		if (s[len] == c)
			return ((char *)&s[len]);
	}
	if (c == 0)
		return ((char *)&s[len]);
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set) // not necessary ?
{
	size_t	len;
	size_t	end;
	size_t	start;
	char	*trim;

	start = 0;
	if (!s1)
		return (NULL);
	while (ft_strchr(set, s1[start]) && s1[start])
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]) && s1[end - 1])
		end--;
	len = end - start;
	trim = malloc((len + 1) * sizeof(char));
	if (!trim)
		return (NULL);
	trim[len] = 0;
	while (len--)
		trim[len] = s1[--end];
	return (trim);
}