/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:16:04 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/05 09:23:59 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	strsfree(char **strs)
{
	int	i;

	if (strs == 0)
		return ;
	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**strs_addstr(char **strs, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strs[i] != 0)
	{
		tmp = ft_strjoin(strs[i], str);
		if (tmp == 0)
			return (0);
		free(strs[i]);
		strs[i] = tmp;
		i++;
	}
	return (strs);
}

char	**get_paths(void)
{
	char	*path_str;
	char	**paths;

	path_str = getenv("PATH");
	if (path_str == 0)
		return (0);
	paths = ft_split(path_str, ':');
	if (paths == 0)
		return (0);
	if (strs_addstr(paths, "/") == 0)
	{
		strsfree(paths);
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

int	add_path(char **command_ptr)
{
	char	**paths;
	int		i;

	paths = get_paths();
	if (paths == 0)
		return (-1);
	i = 0;
	if (access(*command_ptr, X_OK) != -1)
		return (1);
	while (paths[i] != 0)
	{
		if (check_path(paths[i], command_ptr))
		{
			strsfree(paths);
			return (1);
		}
		i++;
	}
	minishell_error(*command_ptr, "command not found");
	strsfree(paths);
	return (-1);
}
