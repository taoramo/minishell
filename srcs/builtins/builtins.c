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

int	ft_cd(t_vec *argv)
{
	char	**strs;
	int		r;

	strs = (char **)argv->memory;
	if (strs[1] != 0)
		r = chdir(strs[1]);
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
		return (0);
}

int	ft_env(t_vec *env)
{
	size_t	i;

	i = 0;
	while (i < env->len)
	{
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
