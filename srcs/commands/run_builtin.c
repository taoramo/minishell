/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:25:39 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/05 15:46:06 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	run_builtin(t_command *command)
{
	int	stdin_copy;
	int	stdout_copy;
	int	stderr_copy;

	stdin_copy = dup(0);
	stdout_copy = dup(1);
	stderr_copy = dup(2);

	free(*(char **)(vec_get(&command->argv, 0))); // TODO better way without this remove?
	vec_remove(&command->argv, 0);

	vec_iter(&command->redirects, apply_redirect);
	ft_echo(&command->argv);
	
	dup2(stdin_copy, 0);
	dup2(stdout_copy, 1);
	dup2(stderr_copy, 2);

	return (0);
}
