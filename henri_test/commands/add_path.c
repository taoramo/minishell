/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:16:04 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/25 13:06:09 by hpatsi           ###   ########.fr       */
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

char	*add_path(char *command)
{
	char	**paths;
	char	*path_command;
	int		i;

	paths = get_paths();
	i = 0;
	if (access(command, X_OK) != -1)
		return (ft_strdup(command));
	while (paths[i] != 0)
	{
		path_command = ft_strjoin(paths[i], command);
		if (path_command == 0)
			return (0);
		if (access(path_command, X_OK) != -1)
			return (path_command);
		free(path_command);
		i++;
	}
	return (ft_strdup(command));
}