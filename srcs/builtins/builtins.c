#include "minishell.h"

int	ft_echo(t_vec *argv)
{
	char	**strs;
	size_t	i;
	int		print_nl;
	int		r;
	
	strs = (char **)argv->memory;
	if (!strs[1])
		return (0);
	if (!ft_strncmp(strs[1], "-n", 3))
	{
		print_nl = 0;
		i = 2;
	}
	else
	{
		print_nl = 1;
		i = 1;
	}
	while (i < argv->len)
	{
		r = ft_putstr_fd(strs[i], 1);
		if (r == -1)
			return (1);
		if (i < argv->len - 1)
			r = write(1, " ", 1);
		if (r == -1)
			return (1);
		i++;
	}
	if (print_nl)
		write(1, "\n", 1);
	return (0);
}

int	relative_parent(char *path)
{
	int	i;
	int	len;

	if (!getcwd(path, MAXPATHLEN))
	{
		perror("minishell: cd:");
		return (-1);
	}
	len = ft_strlen(path);
	i = len;
	while (i >= 0 && path[i] != '/')
		i--;
	while (i < len)
	{
		path[i] = 0;
		i++;
	}
	chdir(path);
	return (0);
}

char	*ft_getenv(char *arg, t_vec *env)
{
	size_t	i;
	int		j;
	char	**entries;
	char	*str;

	entries = (char **)env->memory;
	i = 0;
	j = 0;
	while (i < env->len)
	{
		if (!ft_strncmp(arg, entries[i], ft_strlen_member(entries[i], '=')))
		{
			while (entries[i][j] && entries[i][j] != '=')
				j++;
			j++;
			str = ft_calloc(ft_strlen(&entries[i][j]) + 1, sizeof(char));
			if (!str)
				return (0);
			ft_strlcpy(str, &entries[i][j], ft_strlen(&entries[i][j]) + 1);
			return (str);
		}
		i++;
	}
	return (0);
}

char	*change_directory(t_vec *argv)
{
	t_vec	pathstrs;

	if (vec_split(&pathstrs, *(char **)vec_get(argv, 1), '/') < 0)
	{
		ft_error("minishell: cd: memory error\n"));
		return (0);
	}

}

int	ft_cd(t_vec *argv, t_vec *env)
{
	char	**strs;
	char	*path;
	int		r;

	strs = (char **)argv->memory;
	if (strs[1] && ft_strlen(strs[1]) > MAXPATHLEN)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(strs[1], 2);
		ft_putstr_fd(": File name too long\n", 2);
		return (1);
	}
	if (strs[1] && ft_strlen(strs[1]))
	{
		path = change_directory(argv);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: path too long\n", 2);
			return (1);
		}
	r = chdir(path);
	}
	else
	{
		path = ft_getenv("HOME", env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: error\n", 2);
			return (1);
		}
		r = chdir(path);
		free(path);
	}
	if (r == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(strs[1]);
		return (1);
	}
	return (r);
}

int	ft_pwd(t_vec *argv)
{
	char	str[MAXPATHLEN];
	char	*check;

	(void)argv;
	check = getcwd(str, MAXPATHLEN);
	if (!check)
	{
		ft_putstr_fd("minishell: pwd:", 2);
		ft_putstr_fd(str, 2);
		perror(0);
		return (-1);
	}
	else
	{
		ft_putstr_fd(str, 1);
		write(1, "\n", 1);
		return (0);
	}
}

int	contains_equals(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_env(t_vec *env)
{
	size_t	i;

	i = 0;
	while (i < env->len)
	{
		if (contains_equals(*(char **)vec_get(env, i)))
			ft_putstr_fd(*(char **)vec_get(env, i), 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int	ft_unset(t_vec *argv, t_vec *env)
{
	size_t	i;
	int		j;
	char	**strs;
	char	**args;

	i = 0;
	j = 0;

	strs = (char **)env->memory;
	args = (char **)argv->memory;
	if (argv->len < 2)
		return (0);
	while (i < env->len)
	{
		while (strs[i][j] && strs[i][j] != '=')
			j++;
		if (!ft_strncmp(args[1], strs[i], j))
		{
			vec_remove(env, i);
			return (1);
		}
		j = 0;
		i++;
	}
	return (1);
}
