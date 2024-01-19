/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:29:15 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/19 14:42:48 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i] != 0)
		i++;
	return (i);
}

void	print_command_fd(char **command, int fd)
{
	int	i;

	i = 0;
	while (command[i] != 0)
	{
		ft_putstr_fd(command[i], fd);
		ft_putstr_fd(" ", fd);
		i++;
	}
	ft_putstr_fd("\n", fd);
}

void	print_commands_fd(char ***commands, int fd)
{
		int	i;

	i = 0;
	while (commands[i] != 0)
	{
		print_command_fd(commands[i], fd);
		i++;
	}
}