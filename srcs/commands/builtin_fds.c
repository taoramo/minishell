/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:14:41 by toramo            #+#    #+#             */
/*   Updated: 2024/02/28 08:35:58 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_close(int stdfd_copy[], int n)
{
	if (n == 0)
	{
		close(stdfd_copy[0]);
		close(stdfd_copy[1]);
		close(stdfd_copy[2]);
	}
	else if (n == 1)
	{
		close(stdfd_copy[1]);
		close(stdfd_copy[2]);
	}
	else if (n == 2)
		close(stdfd_copy[2]);
}

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
		close(stdfd_copy[0]);
		perror("dup failed");
		return (-1);
	}
	stdfd_copy[2] = dup(2);
	if (stdfd_copy[2] == -1)
	{
		close(stdfd_copy[0]);
		close(stdfd_copy[1]);
		perror("dup failed");
		return (-1);
	}
	return (1);
}

int	reset_stdfds(int stdfd_copy[])
{
	if (dup2(stdfd_copy[0], 0) == -1)
	{
		error_close(stdfd_copy, 0);
		perror("dup failed");
		return (-1);
	}
	close(stdfd_copy[0]);
	if (dup2(stdfd_copy[1], 1) == -1)
	{
		error_close(stdfd_copy, 1);
		perror("dup failed");
		return (-1);
	}
	close(stdfd_copy[1]);
	if (dup2(stdfd_copy[2], 2) == -1)
	{
		error_close(stdfd_copy, 2);
		perror("dup failed");
		return (-1);
	}
	close(stdfd_copy[2]);
	return (1);
}
