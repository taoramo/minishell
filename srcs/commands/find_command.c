/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:21:50 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/08 13:14:21 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	check_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir != 0)
	{
		closedir(dir);
		write(2, "minishell: ", 11);
		write(2, path, ft_strlen(path));
		write(2, ": is a directory\n", 17);
		return (126);
	}
	return (0);
}

int	check_command_with_path(char *command)
{
	if (access(command, X_OK) != -1)
		return (check_dir(command));
	if (errno == EACCES)
		return (access_error(command));
	minishell_error(command, "No such file or directory");
	return (127);
}

int	find_command(char **command_ptr, t_vec *env)
{
	if (ft_strlen(*command_ptr) == 0)
		return (command_not_found_error(*command_ptr));
	if (builtin_index(*command_ptr) != -1)
		return (0);
	if (ft_strchr(*command_ptr, '/'))
		return (check_command_with_path(*command_ptr));
	return (add_path(command_ptr, env));
}
