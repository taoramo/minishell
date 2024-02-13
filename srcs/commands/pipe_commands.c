/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:15:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/13 18:36:27 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	run_single_pipe_command(t_command *command, int pipe_fds[], int pipe2_fds[], int pos)
{
	command->process_id = fork();
	if (command->process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (command->process_id == 0)
		handle_child(command, pipe_fds, pipe2_fds, pos);
	else
		handle_parent(pos, pipe_fds, pipe2_fds);
	return (command->process_id);
}

int first_pipe_commmand(char *str, int pipe_fds[], t_vec *env, int last_return)
{
	t_command	command;
	
	prepare_command(&command, str, env, last_return);
	if (command.argv.len != 0)
	{
		if (builtin_index(*(char **)vec_get(&command.argv, 0)) != -1)
			return (run_builtin_pipe(&command, 0, pipe_fds, 0));
	}
	return (run_single_pipe_command(&command, pipe_fds, 0, 0));
}

int last_pipe_command(char *str, int pipe_fds[], t_vec *env)
{
	t_command	command;
	
	prepare_command(&command, str, env, 0);
	if (command.argv.len != 0)
	{
		if (builtin_index(*(char **)vec_get(&command.argv, 0)) != -1)
			return (run_builtin_pipe(&command, 1, pipe_fds, 0));
	}
	return (run_single_pipe_command(&command, pipe_fds, 0, 1));
}

int	middle_pipe_command(char *str, int pipe_fds[], t_vec *env)
{
	int			pipe2_fds[2];
	t_command	command;

	if (pipe(pipe2_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	prepare_command(&command, str, env, 0);
	if (command.argv.len != 0)
	{
		if (builtin_index(*(char **)vec_get(&command.argv, 0)) != -1)
			return (run_builtin_pipe(&command, 2, pipe_fds, pipe2_fds));
	}
	return (run_single_pipe_command(&command, pipe_fds, pipe2_fds, 2));
}

int	pipe_commands(char **strs, int **p_ids, t_vec *env, int last_return)
{
	int	pipe_fds[2];
	int	i;

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	i = 0;
	while (i < count_commands(strs))
	{
		if (i == 0)
			(*p_ids)[i] = first_pipe_commmand(strs[i], pipe_fds, env, last_return);
		else if (i == count_commands(strs) - 1)
			(*p_ids)[i] = last_pipe_command(strs[i], pipe_fds, env);
		else
			(*p_ids)[i] = middle_pipe_command(strs[i], pipe_fds, env);
		if ((*p_ids)[i] == -1)
			return (-1);
		i++;
	}
	return (1);
}
