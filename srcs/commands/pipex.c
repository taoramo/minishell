/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:13:47 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/13 11:47:18 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static int	wait_for_children(int *process_ids)
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

int	count_commands(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
		i++;
	return (i);
}

int	split_pipe(char ***strs, char *pipe_str)
{
	*strs = ft_split(pipe_str, '|');
	if (*strs == 0)
		return (-1);
	return (1);
}

int	pipex(char *pipe_str, t_vec *env, int last_return)
{
	int		*process_ids;
	int		ret;
	char	**strs;

	if (pipe_str[0] == '|')
		return (ft_error("minishell: syntax error near unexpected token `|'"));
	if (split_pipe(&strs, pipe_str) == -1)
		return (-1);
	process_ids = ft_calloc(count_commands(strs) + 1, sizeof(int));
	if (process_ids == 0)
		return (-1);
		
	pipe_commands(strs, &process_ids, env, last_return);
	
	// vec_new(&commands, 1, sizeof(t_command));
	// last_return = prepare_pipe(&commands, pipe_str);

	// if (pipe_commands(commands, &process_ids) == -1)
	// {
	// 	free(process_ids);
	// 	return (-1);
	// }
	ret = wait_for_children(process_ids);
	// if (last_return == 0)
	// 	last_return = ret;
	free(process_ids);
	return (ret);
}
