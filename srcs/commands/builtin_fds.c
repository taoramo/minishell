/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:14:41 by toramo            #+#    #+#             */
/*   Updated: 2024/02/16 09:14:49 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_stdfds(int stdfd_copy[])
{
	stdfd_copy[0] = dup(0);
	if (stdfd_copy[0] == -1)
	{
		perror("dup failed");
		return (-1);
	}
	stdfd_copy[1] = dup(1);
	if (stdfd_copy[1] == -1)
	{
		perror("dup failed");
		return (-1);
	}
	stdfd_copy[2] = dup(2);
	if (stdfd_copy[2] == -1)
	{
		perror("dup failed");
		return (-1);
	}
	return (1);
}

int	reset_stdfds(int stdfd_copy[])
{
	if (dup2(stdfd_copy[0], 0) == -1)
	{
		perror("dup failed");
		return (-1);
	}
	if (dup2(stdfd_copy[1], 1) == -1)
	{
		perror("dup failed");
		return (-1);
	}
	if (dup2(stdfd_copy[2], 2) == -1)
	{
		perror("dup failed");
		return (-1);
	}
	return (1);
}
