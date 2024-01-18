/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:13:47 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/18 16:29:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// input e.g.
/*
commands = [["echo", "hello", "mom !"],
			["wc", "-l"],
			["awk", "'{print $1}'"]]
file_fds[0] = infile fd
file_fds[1] = outfile fd
*/

#include "pipex.h"

int	wait_for_children(int *process_ids)
{
	int	i;
	int	ret;

	i = 0;
	while (process_ids[i] != 0)
	{
		waitpid(process_ids[i], &ret, 0);
		i++;
	}
	return (WEXITSTATUS(ret));
}

int	count_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i] != 0)
		i++;
	return (i);
}

int	pipex(char ***commands, int file_fds[])
{
	int	*process_ids;
	int	exit_code;

	process_ids = ft_calloc(count_commands(commands) + 1, sizeof(int));
	if (process_ids == 0)
		return (-1);
	if (pipe_commands(commands, file_fds, &process_ids) == -1)
	{
		free(process_ids);
		return (-1);
	}
	exit_code = wait_for_children(process_ids);
	free(process_ids);
	return (exit_code);
}

int	main(void)
{
	char	***commands;
	char	**command1;
	char	**command2;
	char	*exec1 = "cat";
	char	*exec2 = "wc";
	char	*arg2 = "-l";

	int		file_fds[2] = {0, 1};

	command1 = ft_calloc(3, sizeof (char *));
	command2 = ft_calloc(3, sizeof (char *));
	command1[0] = exec1;
	command2[0] = exec2;
	command2[1] = arg2;

	pipex(commands, file_fds);

	return (0);
}