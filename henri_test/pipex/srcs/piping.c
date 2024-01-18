/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:23:00 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/04 12:44:59 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_command(int input_fd, int output_fd, char **command)
{
	if (command[0] == 0)
		return (-1);
	if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
	{
		perror("dup failed");
		return (-1);
	}
	return (execve(command[0], command, NULL));
}

int	file_to_pipe(int *file_fds, int *pipe_fds, char **command)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (process_id > 0)
	{
		if (file_fds[0] != -1)
			close(file_fds[0]);
		close(pipe_fds[1]);
	}
	else
	{
		close(pipe_fds[0]);
		if (file_fds[0] != -1)
			run_command(file_fds[0], pipe_fds[1], command);
		close(pipe_fds[1]);
		return (-1);
	}
	return (process_id);
}

int	pipe_to_file(int *file_fds, int *pipe_fds, char **command)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (process_id > 0)
	{
		close(pipe_fds[0]);
		close(file_fds[1]);
	}
	else
	{
		close(pipe_fds[1]);
		return (run_command(pipe_fds[0], file_fds[1], command));
	}
	return (process_id);
}

int	pipe_to_pipe(int *pipe_fds, char **command)
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
		return (run_command(pipe_fds[0], pipe2_fds[1], command));
	}
	return (process_id);
}

int	pipe_commands(int *file_fds, char ***commands, int **process_ids)
{
	int	pipe_fds[2];
	int	i;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	i = 0;
	(*process_ids)[i] = file_to_pipe(file_fds, pipe_fds, commands[i]);
	if ((*process_ids)[i] == -1)
		return (-1);
	i++;
	while (commands[i + 1] != 0)
	{
		(*process_ids)[i] = pipe_to_pipe(pipe_fds, commands[i]);
		if ((*process_ids)[i] == -1)
			return (-1);
		i++;
	}
	(*process_ids)[i] = pipe_to_file(file_fds, pipe_fds, commands[i]);
	if ((*process_ids)[i] == -1)
		return (-1);
	(*process_ids)[++i] = 0;
	return (0);
}
