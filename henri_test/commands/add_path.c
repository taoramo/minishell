/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:16:04 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/26 14:29:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

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
	return (ft_strsaddstr(paths, "/"));
	return (0);
}

int	add_path(char **command_ptr)
{
	char	**paths;
	char	*path_command;
	int		i;

	paths = get_paths();
	i = 0;
	if (access(*command_ptr, X_OK) != -1)
		return (1);
	while (paths[i] != 0)
	{
		path_command = ft_strjoin(paths[i], *command_ptr);
		if (path_command == 0)
			return (-1);
		if (access(path_command, X_OK) != -1)
		{
			free(*command_ptr);
			*command_ptr = path_command;
			return (1);
		}
		free(path_command);
		i++;
	}
	return (-1);
}