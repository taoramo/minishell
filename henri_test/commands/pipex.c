/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:13:47 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/29 15:05:48 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

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

int	prepare_pipe(t_vec *commands, char *pipe_str)
{
	char		**strs;
	t_command	*command;
	int			i;

	strs = ft_split(pipe_str, '|');
	if (strs == 0)
		return (0);
	i = 0;
	while (strs[i] != 0)
	{
		command = ft_calloc(1, sizeof(t_command));
		if (prepare_command(command, strs[i]) == -1)
			return (-1);
		vec_push(commands, command);
		i++;
	}
	return (1);
}

int	pipex(char *pipe_str)
{
	t_vec	commands;
	int		*process_ids;
	int		exit_code;

	vec_new(&commands, 1, sizeof(t_command));
	if (prepare_pipe(&commands, pipe_str) == -1)
		return (-1);
	process_ids = ft_calloc(commands.len + 1, sizeof(int));
	if (process_ids == 0)
		return (-1);
	if (pipe_commands(commands, &process_ids) == -1)
	{
		free(process_ids);
		return (-1);
	}
	exit_code = wait_for_children(process_ids);
	free(process_ids);
	return (exit_code);
}
