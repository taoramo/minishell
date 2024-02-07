/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:58:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/07 13:33:58 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_command(t_vec *argv, t_vec *env)
{
	(void) env;
	
	expand_env(argv, env);
	//expand_star(argv);
	remove_quotes(argv);

	return (1);
}

int	prepare_argv(t_command *command, char *command_str, t_vec *env)
{
	if (vec_new(&command->argv, 0, sizeof(char *)) == -1)
		return (-1);
	if (split_command(&command->argv, command_str) == -1)
	{
		free_split_vec(&command->argv);
		return (-1);
	}
	if (expand_command(&command->argv, env) == -1)
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

int	prepare_command(t_command *command, char *command_str, t_vec *env)
{
	if (prepare_argv(command, command_str, env) == -1)
		return (1);
	if (prepare_redirects(command) == -1)
		return (1);
	if (add_path((char **) vec_get(&command->argv, 0)) == -1)
	{
		free_split_vec(&command->argv);
		vec_free(&command->redirects);
		return (127);
	}
	command->env = env;
	return (0);
}
