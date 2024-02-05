/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:15:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/05 10:14:08 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	read_input(char *limiter, int *pipe_fds)
{
	char	*read_str;

	while (1)
	{
		ft_printf("> ");
		read_str = get_next_line(0);
		if (read_str == 0)
			return (-1);
		if (ft_strncmp(read_str, limiter, ft_strlen(read_str)) == 0)
			break ;
		if (write(pipe_fds[1], read_str, ft_strlen(read_str)) == -1)
		{
			free(read_str);
			return (-1);
		}
		free(read_str);
	}
	free(read_str);
	return (1);
}

int	infile_from_stdin(char *limiter)
{
	int		pipe_fds[2];
	char	*nl_limiter;

	nl_limiter = ft_strjoin(limiter, "\n");
	if (nl_limiter == 0)
		return (-1);
	if (pipe(pipe_fds) < 0)
	{
		free(nl_limiter);
		perror("pipe failed");
		return (-1);
	}
	if (read_input(nl_limiter, pipe_fds) == -1)
	{
		free(nl_limiter);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	free(nl_limiter);
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}
