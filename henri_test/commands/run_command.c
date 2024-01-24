/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:24:55 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 14:33:38 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	execute_command(int input_fd, int output_fd, char **command)
{
	int ret;

	if (command[0] == 0)
		return (-1);
	if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
	{
		perror("dup failed");
		return (-1);
	}
	ret = execve(command[0], command, NULL);
	perror(command[0]);
	return (ret);
}

int	run_command(int input_fd, int output_fd, char **command)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (process_id == 0)
		return (execute_command(input_fd, output_fd, command));
	return (process_id);
}