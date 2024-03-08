/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:58:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/08 10:31:25 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_argv(t_command *command, char *command_str)
{
	if (vec_new(&command->argv, 4, sizeof(char *)) == -1)
		return (-1);
	if (split_command(&command->argv, command_str) == -1)
	{
		free_split_vec(&command->argv);
		return (-1);
	}
	if (isolate_redirects(&command->argv) == -1)
	{
		free_split_vec(&command->argv);
		return (-1);
	}
	return (1);
}

int	prepare_redirects(t_command *command, int heredoc_fd)
{
	if (vec_new(&command->redirects, 4, sizeof(t_redirect)) == -1)
		return (-1);
	if (extract_files(command, heredoc_fd) == -1)
	{
		vec_free(&command->redirects);
		return (-1);
	}
	return (1);
}

int	expand_command(t_command *command, t_envinfo envinfo, int i)
{
	if (expand_envs(&command->argv, envinfo.env, *envinfo.last_return) == -1)
		return (-1);
	if (expand_star(&command->argv) == -1)
		return (-1);
	if (vec_get(envinfo.heredoc_fds, i) && prepare_redirects(command,
			*(int *)vec_get(envinfo.heredoc_fds, i)) == -1)
		return (-1);
	if (split_expanded_command(&command->argv) == -1)
	{
		vec_free(&command->redirects);
		return (-1);
	}
	if (remove_quotes(&command->argv) == -1)
	{
		vec_free(&command->redirects);
		return (-1);
	}
	return (1);
}

int	prepare_command(t_command *command,
	char *command_str, t_envinfo envinfo, int i)
{
	int	ret;

	if (prepare_argv(command, command_str) == -1)
		return (1);
	if (expand_command(command, envinfo, i) == -1)
	{
		free_split_vec(&command->argv);
		return (1);
	}
	if (command->argv.len != 0)
		ret = find_command((char **) vec_get(&command->argv, 0), envinfo.env);
	else
		ret = 1;
	if (ret != 0)
	{
		free_split_vec(&command->argv);
		vec_free(&command->redirects);
		return (ret);
	}
	command->env = envinfo.env;
	return (0);
}

int	prepare_pipe_command(t_command *command, t_pipe *pipeinfo, int i)
{
	t_envinfo	envinfo;
	int			ret;

	envinfo.env = pipeinfo->env;
	envinfo.last_return = &pipeinfo->last_return;
	envinfo.heredoc_fds = pipeinfo->heredoc_fds;
	ret = prepare_command(command, pipeinfo->command_strs[i], envinfo, i);
	pipeinfo->last_return = 0;
	return (ret);
}
