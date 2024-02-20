/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:00:23 by toramo            #+#    #+#             */
/*   Updated: 2024/02/20 12:58:00 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_dir_change(t_vec *pathstrs)
{
	size_t	i;
	int		r;
	char	buffer[MAXPATHLEN];

	ft_bzero(buffer, MAXPATHLEN);
	i = 0;
	r = chdir("/");
	while (i < pathstrs->len)
	{
		ft_strlcat(buffer, *(char **)vec_get(pathstrs, i), MAXPATHLEN);
		ft_strlcat(buffer, "/", MAXPATHLEN);
		r = chdir(buffer);
		if (r < 0)
			return (r);
		ft_bzero(buffer, MAXPATHLEN);
		i++;
	}
	return (r);
}

int	construct_path(t_vec *argv)
{
	t_vec	pathstrs;
	char	*buffer;
	int		r;

	buffer = 0;
	if (vec_new(&pathstrs, 32, sizeof(char *)) < 0)
		return (-1);
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
	r = do_dir_change(&pathstrs);
	free_split_vec(&pathstrs);
	return (r);
}

void	change_directory(t_vec *argv, t_vec *env, int *r)
{
	char	**strs;
	char	*path;

	strs = (char **)argv->memory;
	if (strs[1] && ft_strlen(strs[1]))
	{
		*r = construct_path(argv);
	}
	else
	{
		path = ft_getenv("HOME", env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: error\n", 2);
			*r = chdir(path);
			free(path);
		}
	}
}

int	ft_cd(t_vec *argv, t_vec *env)
{
	char	**strs;
	int		r;

	strs = (char **)argv->memory;
	if (strs[1] && ft_strlen(strs[1]) > MAXPATHLEN)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(strs[1], 2);
		ft_putstr_fd(": File name too long\n", 2);
		return (1);
	}
	change_directory(argv, env, &r);
	if (r < 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(strs[1]);
		return (1);
	}
	return (r);
}
