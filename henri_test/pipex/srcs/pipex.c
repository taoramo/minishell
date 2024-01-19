/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:13:47 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/19 14:22:36 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// input e.g.
/*
commands = [["echo", "hello", "mom !"],
			["wc", "-l"],
			["awk", "'{print $1}'"]]
file_fds[0] = infile fd
file_fds[1] = outfile fd
*/

#include "pipex.h"

int	wait_for_children(int *process_ids)
{
	int	i;
	int	ret;

	i = 0;
	while (process_ids[i] != 0)
	{
		waitpid(process_ids[i], &ret, 0);
		i++;
	}
	return (WEXITSTATUS(ret));
}

int	pipex(char ***commands, int file_fds[])
{
	int	*process_ids;
	int	exit_code;

	process_ids = ft_calloc(count_commands(commands) + 1, sizeof(int));
	if (process_ids == 0)
		return (-1);
	ft_printf("Running pipes\n");
	if (pipe_commands(commands, file_fds, &process_ids) == -1)
	{
		free(process_ids);
		return (-1);
	}
	ft_putstr_fd("Waiting for children\n", 2);
	exit_code = wait_for_children(process_ids);
	ft_putstr_fd("Children finished\n", 2);
	free(process_ids);
	return (exit_code);
}