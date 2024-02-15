/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:58:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/15 10:11:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_argv(t_command *command, char *command_str)
{
	if (vec_new(&command->argv, 0, sizeof(char *)) == -1)
		return (-1);
	if (split_command(&command->argv, command_str) == -1)
	{
		free_split_vec(&command->argv);
		return (-1);
	}
	return (1);
}

int	prepare_redirects(t_command *command)
{
	if (vec_new(&command->redirects, 0, sizeof(t_redirect)) == -1)
	{
		free_split_vec(&command->argv);
		return (-1);
	}
	if (extract_files(command) == -1)
	{
		free_split_vec(&command->argv);
		vec_free(&command->redirects);
		return (-1);
	}
	return (1);
}

int	expand_command(t_vec *argv, t_vec *env,  int last_return)
{
	expand_envs(argv, env, last_return);
	expand_star(argv);
	split_expanded_command(argv);
	remove_quotes(argv);

	return (1);
}

int	prepare_command(t_command *command, char *command_str, t_envinfo envinfo)
{
	if (prepare_argv(command, command_str) == -1)
		return (1);
	if (expand_command(&command->argv, envinfo.env, *envinfo.last_return) == -1)
	{
		free_split_vec(&command->argv);
		return (-1);
	}
	if (prepare_redirects(command) == -1)
		return (1);
	if (command->argv.len != 0 && add_path((char **) vec_get(&command->argv, 0), envinfo.env) == -1)
	{
		free_split_vec(&command->argv);
		vec_free(&command->redirects);
		return (127);
	}
	command->env = envinfo.env;
	return (0);
}

int	prepare_pipe_command(t_command *command, char *command_str, t_pipe *pipeinfo)
{
	t_envinfo	envinfo;
	int			ret;

	envinfo.env = &pipeinfo->env;
	envinfo.last_return = &pipeinfo->last_return;
	envinfo.heredoc_fds = *pipeinfo->heredoc_fds;
	ret = prepare_command(command, command_str, envinfo);
	pipeinfo->last_return = 0;
	return (ret);
}
