/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:15:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/02 16:04:44 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static void	apply_pipe_redirect(t_command *command, int in_fd, int out_fd)
{
	if (in_fd != 0)
	{
		if (dup2(in_fd, 0) == -1)
			perror("dup failed");
	}
	if (out_fd != 1)
	{
		if (dup2(out_fd, 1) == -1)
			perror("dup failed");
	}
	vec_iter(&command->redirects, apply_redirect);
}

void	handle_parent(t_vec comms, size_t i, int pipe_fds[], int pipe2_fds[])
{
	if (i == 0)
		close(pipe_fds[1]);
	else if (i == comms.len - 1)
		close(pipe_fds[0]);
	else
	{
		close(pipe_fds[0]);
		close(pipe2_fds[1]);
		pipe_fds[0] = pipe2_fds[0];
	}
}

void	handle_child(t_vec comms, size_t i, int pipe_fds[], int pipe2_fds[])
{
	t_command	*command;

	command = (t_command *) vec_get(&comms, i);
	if (i == 0)
	{
		close(pipe_fds[0]);
		apply_pipe_redirect(command, 0, pipe_fds[1]);
	}
	else if (i == comms.len - 1)
		apply_pipe_redirect(command, pipe_fds[0], 1);
	else
	{
		close(pipe2_fds[0]);
		apply_pipe_redirect(command, pipe_fds[0], pipe2_fds[1]);
	}
	execute_command(command->argv);
	exit (1);
}

int	pipe_command(t_vec comms, size_t i, int pipe_fds[])
{
	int	process_id;
	int	pipe2_fds[2];

	if (i != 0 && i < comms.len - 1 && pipe(pipe2_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (process_id > 0)
		handle_parent(comms, i, pipe_fds, pipe2_fds);
	else
		handle_child(comms, i, pipe_fds, pipe2_fds);
	return (process_id);
}

int	pipe_commands(t_vec comms, int **p_ids)
{
	int		pipe_fds[2];
	size_t	i;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	i = 0;
	while (i < comms.len)
	{
		(*p_ids)[i] = pipe_command(comms, i, pipe_fds);
		if ((*p_ids)[i] == -1)
			return (-1);
		i++;
	}
	return (1);
}
