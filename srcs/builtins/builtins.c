#include "minishell.h"

int	ft_echo(t_vec *argv)
{
	char	**strs;
	size_t	i;
	int		print_nl;
	int		r;

	strs = (char **)argv->memory;
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

int	relative_parent(char *path, char *arg)
{
	int	i;
	int	len;

	getcwd(path, MAXPATHLEN);
	i = ft_strlen(path);
	while (i >= 0 && path[i] != '/')
		i--;
	len = ft_strlen(arg) + i;
	if (len > MAXPATHLEN)
		return (-1);
	ft_strlcpy(&path[i], arg, ft_strlen(arg) + 1);
	return (0);
}

int	relative_current(char *path, char *arg)
{
	int	i;
	int	len;

	getcwd(path, MAXPATHLEN);
	i = ft_strlen(path);
	len = ft_strlen(arg) + i;
	if (len > MAXPATHLEN)
		return (-1);
	ft_strlcpy(&path[i], arg, ft_strlen(arg) + 1);
	return (0);
}

int	ft_cd(t_vec *argv)
{
	char	**strs;
	char	path[MAXPATHLEN];
	int		r;

	strs = (char **)argv->memory;
	if (ft_strlen(strs[1]) > MAXPATHLEN)
	{
		ft_putstr_fd("minishell: cd: path too long\n", 3);
		return (-1);
	}
	if (strs[1] != 0)
	{
		if (!ft_strncmp(strs[1], "../", 3))
		{
			if (relative_parent(path, strs[1]) < 0)
			{
				ft_putstr_fd("minishell: cd: path too long\n", 3);
				return (-1);
			}
		}
		else if (!ft_strncmp(strs[1], "./", 2))
		{
			if (relative_current(path, strs[1]) < 0)
			{
				ft_putstr_fd("minishell: cd: path too long\n", 3);
				return (-1);
			}
		}
		r = chdir(path);
	}
	else
		r = chdir(getenv("HOME"));
	if (r == -1)
	{
		ft_putstr_fd("minishell: cd:", 3);
		ft_putstr_fd(strs[1], 3);
		perror(0);
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
		ft_putstr_fd("minishell: pwd:", 3);
		ft_putstr_fd(str, 3);
		perror(0);
		return (-1);
	}
	else
	{
		ft_putstr_fd(str, 3);
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
	char	*ptr;

	(void)argv;
	i = 0;
	while (i < env->len)
	{
		ptr = *(char **)vec_get(env, i);
		while (ptr[j] && ptr[j] != '=')
			j++;
		if (!ft_strncmp(vec_get(argv, 1), ptr, j))
		{
			vec_remove(env, i);
			return (1);
		}
		j = 0;
		i++;
	}
	return (1);
}
