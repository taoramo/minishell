/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:24:55 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/26 14:53:54 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	execute_command(t_vec argv)
{
	int 	ret;
	char	**strs;

	strs = (char **) argv.memory;
	ret = execve(strs[0], strs, NULL);
	perror(strs[0]);
	return (ret);
}

void	redirect_file(void	*param)
{
	t_redirect	redirect;

	redirect = *(t_redirect *) param;
	if (dup2(redirect.new_fd, redirect.origial_fd) == -1)
		perror("dup failed");
}

int	run_command(t_command command)
{
	int	process_id;

	process_id = fork();
	if (process_id < 0)
	{
		perror("fork failed");
		command.process_id = -1;
		return (-1);
	}
	else if (process_id == 0)
	{
		vec_iter(&command.redirects, redirect_file);
		return (execute_command(command.argv));
	}
	command.process_id = process_id;
	return (process_id);
}