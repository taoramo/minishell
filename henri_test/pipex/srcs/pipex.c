/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:51:47 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/18 15:12:58 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	handle_processes(int *file_fds, char ***commands)
{
	int		*process_ids;
	int		exit_code;
	char	*last_command;

	process_ids = ft_calloc(count_commands(commands) + 1, sizeof(int));
	if (process_ids == 0)
	{
		free(commands);
		return (1);
	}
	if (pipe_commands(file_fds, commands, &process_ids) == -1)
	{
		free_commands(commands);
		free(process_ids);
		return (1);
	}
	exit_code = wait_for_children(process_ids);
	last_command = *commands[count_commands(commands) - 1];
	if (access(last_command, X_OK) == -1)
		exit_code = 127;
	free(process_ids);
	free_commands(commands);
	return (exit_code);
}

int	main(int argc, char **argv, char *envp[])
{
	char	***commands;
	int		file_fds[2];
	int		exit_code;

	if (argc < 5 || (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6))
	{
		errno = EINVAL;
		perror("not enough arguments");
		return (1);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
		commands = set_commands(argc - 4, argv + 3, envp);
	else
		commands = set_commands(argc - 3, argv + 2, envp);
	if (commands == 0)
		return (1);
	if (set_files(argc, argv, file_fds) == -1)
	{
		free_commands(commands);
		return (1);
	}
	exit_code = handle_processes(file_fds, commands);
	return (exit_code);
}
