/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:16:04 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 15:56:37 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

char	*add_path(char *command, char **paths)
{
	char	*path_command;
	int		i;

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