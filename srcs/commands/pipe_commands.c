/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:15:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/06 16:01:47 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	apply_pipe_redirect(t_command *command, int in_fd, int out_fd)
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

void	handle_parent(int pos, int pipe_fds[], int pipe2_fds[])
{
	if (pos == 0)
		close(pipe_fds[1]);
	else if (pos == 1)
		close(pipe_fds[0]);
	else
	{
		close(pipe_fds[0]);
		close(pipe2_fds[1]);
		pipe_fds[0] = pipe2_fds[0];
	}
}

void	handle_child(t_command *command, int pos, int pipe_fds[], int pipe2_fds[])
{
	if (pos == 0)
	{
		close(pipe_fds[0]);
		apply_pipe_redirect(command, 0, pipe_fds[1]);
	}
	else if (pos == 1)
		apply_pipe_redirect(command, pipe_fds[0], 1);
	else
	{
		close(pipe2_fds[0]);
		apply_pipe_redirect(command, pipe_fds[0], pipe2_fds[1]);
	}
	execute_command(command->argv, command->env);
	exit (1);
}

int	pipe_command(t_command *command, int pos, int pipe_fds[])
{
	int		process_id;
	int		pipe2_fds[2];

	if (pos == 2 && pipe(pipe2_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	if (command->argv.len != 0)
	{
		if (builtin_index(*(char **)vec_get(&command->argv, 0)) != -1)
			return (run_builtin_pipe(command, pos, pipe_fds, pipe2_fds));
	}
	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (process_id > 0)
		handle_parent(pos, pipe_fds, pipe2_fds);
	else
		handle_child(command, pos, pipe_fds, pipe2_fds);
	return (process_id);
}

int	pipe_commands(t_vec comms, int **p_ids)
{
	int			pipe_fds[2];
	size_t		i;
	t_command	*command;
	int			pos_flag;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	i = 0;
	while (i < comms.len)
	{
		pos_flag = 2;
		if (i == 0)
			pos_flag = 0;
		if (i == comms.len - 1)
			pos_flag = 1;
		command = (t_command *) vec_get(&comms, i);
		(*p_ids)[i] = pipe_command(command, pos_flag, pipe_fds);
		if ((*p_ids)[i] == -1)
			return (-1);
		i++;
	}
	return (1);
}
