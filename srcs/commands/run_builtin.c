/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:25:39 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/06 14:34:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	builtin_index(char *command)
{
	static const char	*builtins[7] = {"echo", "cd", "pwd", "env", "unset", "export", NULL};
	int					i;

	i = 0;
	while (builtins[i] != 0)
	{
		if (ft_strncmp(command, builtins[i], ft_strlen(builtins[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	run_builtin_command(t_command *command)
{
	int	command_index;

	command_index = builtin_index(*(char **)vec_get(&command->argv, 0));
	if (command_index == 0)
		ft_echo(&command->argv);
	if (command_index == 1)
		ft_cd(&command->argv);
	if (command_index == 2)
		ft_pwd(&command->argv);
	if (command_index == 3)
		ft_env(command->env);
	if (command_index == 4)
		ft_unset(&command->argv, command->env);
	if (command_index == 5)
		ft_export(&command->argv, command->env);
	return (0);
}

int	save_stdfds(int stdfd_copy[])
{
	stdfd_copy[0] = dup(0);
	stdfd_copy[1] = dup(1);
	stdfd_copy[2] = dup(2);
	if (stdfd_copy[0] == -1 || stdfd_copy[1] == -1 || stdfd_copy[2] == -1)
		return (-1);
	return (1);
}

int	reset_stdfds(int stdfd_copy[])
{
	if (dup2(stdfd_copy[0], 0) == -1)
		return (-1);
	if (dup2(stdfd_copy[1], 1) == -1)
		return (-1);
	if (dup2(stdfd_copy[2], 2) == -1)
		return (-1);
	return (1);
}

int	run_builtin(t_command *command)
{
	int	stdfd_copy[3];

	save_stdfds(stdfd_copy);
	vec_iter(&command->redirects, apply_redirect);
	run_builtin_command(command);
	reset_stdfds(stdfd_copy);
	return (0);
}

int	run_builtin_pipe(t_vec comms, size_t i, int pipe_fds[], int pipe2_fds[])
{
	int			stdfd_copy[3];
	t_command	*command;

	save_stdfds(stdfd_copy);
	command = (t_command *) vec_get(&comms, i);
	if (i == 0)
		apply_pipe_redirect(command, 0, pipe_fds[1]);
	else if (i == comms.len - 1)
		apply_pipe_redirect(command, pipe_fds[0], 1);
	else
		apply_pipe_redirect(command, pipe_fds[0], pipe2_fds[1]);
	run_builtin_command(command);
	handle_parent(comms, i, pipe_fds, pipe2_fds);
	reset_stdfds(stdfd_copy);
	return (0);
}
