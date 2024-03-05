/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:00:23 by toramo            #+#    #+#             */
/*   Updated: 2024/03/05 09:44:36 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_export_pwd(t_vec *env)
{
	char	*strs[2];
	char	*oldpath;
	char	*path;

	oldpath = ft_getenv("PWD", env);
	if (oldpath == 0)
		return ;
	strs[0] = "export";
	strs[1] = ft_calloc(7 + ft_strlen(oldpath) + 1, sizeof(char));
	if (strs[1] == 0)
	{
		free(oldpath);
		return ;
	}
	ft_memcpy(strs[1], "OLDPWD=", 7);
	ft_memcpy(&strs[1][7], oldpath, ft_strlen(oldpath));
	export_variable(2, env, strs);
	free(strs[1]);
	free(oldpath);

	path = getcwd(0, MAXPATHLEN);
	if (path == 0)
		return ;
	strs[1] = ft_calloc(4 + ft_strlen(path) + 1, sizeof(char));
	if (strs[1] == 0)
	{
		free(path);
		return ;
	}
	ft_memcpy(strs[1], "PWD=", 4);
	ft_memcpy(&strs[1][4], path, ft_strlen(path));
	export_variable(2, env, strs);
	free(strs[1]);
	free(path);
}

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
		if (!buffer || vec_split(&pathstrs, buffer, '/') < 0)
		{
			vec_free(&pathstrs);
			return (cd_error("memory_error"));
		}
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
		*r = construct_path(argv);
	else
	{
		path = ft_getenv("HOME", env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: error\n", 2);
			return ;
		}
		*r = chdir(path);
		free(path);
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
	update_export_pwd(env);
	return (r);
}
