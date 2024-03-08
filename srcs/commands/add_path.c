/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:16:04 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/08 13:20:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

char	**strs_addstr(char **strs, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strs[i] != 0)
	{
		tmp = ft_strjoin(strs[i], str);
		free(strs[i]);
		if (tmp == 0)
			return (0);
		strs[i] = tmp;
		i++;
	}
	return (strs);
}

char	**get_paths(t_vec *env)
{
	size_t	i;
	char	*path_str;
	char	**paths;

	i = 0;
	path_str = ft_getenv("PATH", env);
	if (path_str == 0)
	{
		paths = ft_calloc(1, sizeof(char *));
		if (paths == 0)
			return (0);
		return (paths);
	}
	if (i == env->len)
		return (ft_calloc(1, sizeof(char *)));
	paths = ft_split(path_str, ':');
	free(path_str);
	if (paths == 0)
		return (0);
	if (strs_addstr(paths, "/") == 0)
	{
		ft_free_split(paths);
		return (0);
	}
	return (paths);
}

int	check_path(char *path, char **command_ptr)
{
	char	*path_command;

	path_command = ft_strjoin(path, *command_ptr);
	if (path_command == 0)
		return (0);
	if (access(path_command, X_OK) != -1)
	{
		free(*command_ptr);
		*command_ptr = path_command;
		return (1);
	}
	free(path_command);
	return (0);
}

int	check_local(char **command_ptr)
{
	char	*path_command;

	path_command = ft_strjoin("./", *command_ptr);
	if (path_command == 0)
		return (-1);
	if (access(path_command, X_OK) != -1)
	{
		free(*command_ptr);
		*command_ptr = path_command;
		return (0);
	}
	free(path_command);
	minishell_error(*command_ptr, "No such file or directory");
	return (127);
}

int	add_path(char **command_ptr, t_vec *env)
{
	char	**paths;
	int		i;

	paths = get_paths(env);
	if (paths == 0)
		return (-1);
	if (paths[0] == 0)
	{
		ft_free_split(paths);
		return (check_local(command_ptr));
	}
	i = 0;
	while (paths[i] != 0)
	{
		if (check_path(paths[i], command_ptr))
		{
			ft_free_split(paths);
			return (0);
		}
		i++;
	}
	minishell_error(*command_ptr, "command not found");
	ft_free_split(paths);
	return (127);
}
