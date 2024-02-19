/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:25:39 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/19 16:47:27 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	compare_builtins(char *command, const char *builtin)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i] && builtin[j] && command[i] == builtin[j])
	{
		i++;
		j++;
	}
	if (command[i] && builtin[j])
		return (-1);
	while (command[i] && ft_isspace(command[i]))
		i++;
	if (!command[i] && !builtin[j])
		return (1);
	else
		return (-1);
}

int	builtin_index(char *command)
{
	static const char	*builtins[8] = {"echo", "cd", "pwd",
		"env", "unset", "export", "exit", NULL};
	int					i;

	if (ft_strlen(command) == 0)
		return (-1);
	i = 0;
	while (builtins[i] != 0)
	{
		if (compare_builtins(command, builtins[i]) > 0)
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
		return (ft_echo(&command->argv));
	if (command_index == 1)
		return (ft_cd(&command->argv, command->env));
	if (command_index == 2)
		return (ft_pwd(&command->argv));
	if (command_index == 3)
		return (ft_env(command->env));
	if (command_index == 4)
		return (ft_unset(&command->argv, command->env));
	if (command_index == 5)
		return (ft_export(&command->argv, command->env));
	if (command_index == 6)
		return (INT_MIN);
	return (1);
}

int	run_builtin(t_command *command)
{
	int	stdfd_copy[3];
	int	ret;

	if (save_stdfds(stdfd_copy) == -1)
		return (1);
	vec_iter(&command->redirects, apply_redirect);
	ret = run_builtin_command(command);
	if (reset_stdfds(stdfd_copy) == -1)
		return (1);
	return (ret);
}

int	run_builtin_pipe(t_command *command,
		int pipe_fds[], int pipe2_fds[], int pos)
{
	int		stdfd_copy[3];
	t_vec	sub_env;

	if (copy_split_vec(&sub_env, command->env) == -1)
		return (-1);
	command->env = &sub_env;
	save_stdfds(stdfd_copy);
	if (pos == 0)
		apply_pipe_redirect(command, 0, pipe_fds[1]);
	else if (pos == 1)
		apply_pipe_redirect(command, pipe_fds[0], 1);
	else
		apply_pipe_redirect(command, pipe_fds[0], pipe2_fds[1]);
	run_builtin_command(command);
	handle_parent(pipe_fds, pipe2_fds, pos, command);
	reset_stdfds(stdfd_copy);
	free_split_vec(command->env);
	return (0);
}
