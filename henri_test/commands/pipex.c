/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:13:47 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 11:37:19 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static int	count_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i] != 0)
		i++;
	return (i);
}

static int	wait_for_children(int *process_ids)
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
	if (pipe_commands(commands, file_fds, &process_ids) == -1)
	{
		free(process_ids);
		return (-1);
	}
	exit_code = wait_for_children(process_ids);
	free(process_ids);
	return (exit_code);
}