/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:25:39 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/06 12:39:35 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	builtin_index(char *command)
{
	static const char	*builtins[6] = {"echo", "cd", "pwd", "env", "unset", NULL};
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

int	redirect_builtin(t_command *command, int stdfd_copy[])
{
	stdfd_copy[0] = dup(0);
	stdfd_copy[1] = dup(1);
	stdfd_copy[2] = dup(2);
	if (stdfd_copy[0] == -1 || stdfd_copy[1] == -1 || stdfd_copy[2] == -1)
		return (-1);
	vec_iter(&command->redirects, apply_redirect);
	return (1);
}

int	reset_stdfd(int stdfd_copy[])
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
	int	i;

	redirect_builtin(command, stdfd_copy);
	i = builtin_index(*(char **)vec_get(&command->argv, 0));
	if (i == 0)
		ft_echo(&command->argv);
	if (i == 1)
		ft_cd(&command->argv);
	if (i == 2)
		ft_pwd(&command->argv);
	if (i == 3)
		ft_env(command->env);
	if (i == 4)
		ft_unset(&command->argv, command->env);
	reset_stdfd(stdfd_copy);
	return (0);
}
