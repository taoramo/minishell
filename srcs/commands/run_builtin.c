/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:25:39 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/06 10:54:58 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

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
	int		stdfd_copy[3];
	int		(*f)(t_vec *);

	redirect_builtin(command, stdfd_copy);
	f = get_builtin(builtin_index(*(char **)vec_get(&command->argv, 0)));
	f(&command->argv);
	reset_stdfd(stdfd_copy);

	return (0);
}
