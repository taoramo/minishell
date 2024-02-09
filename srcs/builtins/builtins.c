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
		if (!ft_strncmp(arg, entries[i], ft_strlen_member(entries[i], '='))
			&& arg[ft_strlen_member(entries[i], '=')] == 0)
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

char	*cd_error(char *str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	return (0);
}

char	*parse_directory(t_vec *pathstrs)
{
	size_t		i;
	char		**dirs;
	char		*path;

	path = ft_calloc(sizeof(char), MAXPATHLEN);
	if (!path)
		return (0);
	dirs = (char **)pathstrs->memory;
	i = 0;
	while (i < pathstrs->len)
	{
		if (i != 0 && !ft_strncmp(dirs[i], "..", 3))
		{
			free(dirs[i]);
			vec_remove(pathstrs, i);
			free(dirs[i - 1]);
			vec_remove(pathstrs, i - 1);
			i--;
		}
		else if (!ft_strncmp(dirs[i], ".", 2) || (i == 0 && !ft_strncmp(dirs[i], "..", 3)))
		{
			free(dirs[i]);
			vec_remove(pathstrs, i);
			i--;
		}
		i++;
	}
	path[0] = '/';
	i = 0;
	while (i < pathstrs->len)
	{
		ft_strlcat(path, *(char **)vec_get(pathstrs, i), MAXPATHLEN);
		ft_strlcat(path, "/", MAXPATHLEN);
		i++;
	}
	return (path);
}

char	*change_directory(t_vec *argv)
{
	t_vec	pathstrs;
	char	*buffer;

	buffer = 0;
	vec_new(&pathstrs, 32, sizeof(char *));
	if (ft_strncmp(*(char **)vec_get(argv, 1), "/", 1))
	{
		buffer = getcwd(0, MAXPATHLEN);
		if (!buffer) 
			return (cd_error("memory_error"));
		if (vec_split(&pathstrs, buffer, '/') < 0)
			return (cd_error("memory_error"));
		free(buffer);
	}
	if (vec_split(&pathstrs, *(char **)vec_get(argv, 1), '/') < 0)
	{
		free_split_vec(&pathstrs);
		return (cd_error("memory_error"));
	}
	buffer = parse_directory(&pathstrs);
	free_split_vec(&pathstrs);
	if (!buffer)
		return (cd_error("memory_error"));
	return (buffer);
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
		free(path);
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
			free(strs[i]);
			vec_remove(env, i);
			return (1);
		}
		j = 0;
		i++;
	}
	return (1);
}
