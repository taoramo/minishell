/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:13:47 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/16 15:32:33 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	wait_for_children(t_pipe *pipeinfo)
{
	int	i;
	int	ret;

	i = 0;
	while (i < pipeinfo->command_count)
	{
		if (pipeinfo->process_ids[i] <= 127)
			ret = pipeinfo->process_ids[i];
		else
			waitpid(pipeinfo->process_ids[i], &ret, 0);
		i++;
	}
	if (ret <= 127)
		return (ret);
	return (WEXITSTATUS(ret));
}

int	count_commands(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
		i++;
	return (i);
}

void	free_pipe(t_pipe *pipeinfo)
{
	ft_free_split(pipeinfo->command_strs);
	free(pipeinfo->process_ids);
}

int	initialize_pipe(t_pipe *pipeinfo, char *pipe_str, t_envinfo envinfo)
{
	pipeinfo->command_strs = ft_split_pipe(pipe_str, '|');
	if (pipeinfo->command_strs == 0)
		return (-1);
	pipeinfo->command_count = count_commands(pipeinfo->command_strs);
	pipeinfo->process_ids = ft_calloc(pipeinfo->command_count + 1, sizeof(int));
	if (pipeinfo->process_ids == 0)
	{
		ft_free_split(pipeinfo->command_strs);
		return (-1);
	}
	pipeinfo->env = envinfo.env;
	pipeinfo->last_return = *envinfo.last_return;
	pipeinfo->heredoc_fds = envinfo.heredoc_fds;
	return (1);
}

int	pipex(char *pipe_str, t_envinfo envinfo)
{
	t_pipe	pipeinfo;
	int		ret;

	if (pipe_str[0] == '|')
		return (ft_error("minishell: syntax error near unexpected token `|'"));
	if (initialize_pipe(&pipeinfo, pipe_str, envinfo) == -1)
		return (-1);
	if (pipe_commands(&pipeinfo) == -1)
	{
		free_pipe(&pipeinfo);
		return (-1);
	}
	ret = wait_for_children(&pipeinfo);
	free_pipe(&pipeinfo);
	return (ret);
}
