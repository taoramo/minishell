/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:15:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/29 14:06:03 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static int	file_to_pipe(t_command *command, int pipe_fds[])
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (process_id > 0)
		close(pipe_fds[1]);
	else
	{
		close(pipe_fds[0]);
		if (dup2(pipe_fds[1], 1) == -1)
			perror("dup failed");
		vec_iter(&command->redirects, apply_redirect);
		execute_command(command->argv);
		close(pipe_fds[1]);
		return (-1);
	}
	return (process_id);
}

static int	pipe_to_file(t_command *command, int pipe_fds[])
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (process_id > 0)
		close(pipe_fds[0]);
	else
	{
		close(pipe_fds[1]);
		if (dup2(pipe_fds[0], 0) == -1)
			perror("dup failed");
		vec_iter(&command->redirects, apply_redirect);
		execute_command(command->argv);
		close(pipe_fds[0]);
		return (-1);
	}
	return (process_id);
}

static int	pipe_to_pipe(t_command *command, int *pipe_fds)
{
	int	pipe2_fds[2];
	int	process_id;

	if (pipe(pipe2_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	process_id = fork();
	if (process_id < 0)
		perror("fork failed");
	else if (process_id > 0)
	{
		close(pipe_fds[0]);
		close(pipe2_fds[1]);
		pipe_fds[0] = pipe2_fds[0];
		pipe_fds[1] = pipe2_fds[1];
	}
	else
	{
		close(pipe2_fds[0]);
		vec_iter(&command->redirects, apply_redirect);
		if (dup2(pipe_fds[0], 0) == -1)
			perror("dup failed");
		if (dup2(pipe2_fds[1], 1) == -1)
			perror("dup failed");
		return (execute_command(command->argv));
	}
	return (process_id);
}

int	pipe_commands(t_vec commands, int **process_ids)
{
	int		pipe_fds[2];
	size_t	i;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	i = 0;
	(*process_ids)[i] = file_to_pipe((t_command *) vec_get(&commands, 0), pipe_fds);
	if ((*process_ids)[i] == -1)
		return (-1);
	i++;
	while (i < commands.len - 1)
	{
		(*process_ids)[i] = pipe_to_pipe((t_command *) vec_get(&commands, i), pipe_fds);
		if ((*process_ids)[i] == -1)
			return (-1);
		i++;
	}
	(*process_ids)[i] = pipe_to_file((t_command *) vec_get(&commands, i), pipe_fds);
	if ((*process_ids)[i] == -1)
		return (-1);
	(*process_ids)[++i] = 0;
	return (0);
}
