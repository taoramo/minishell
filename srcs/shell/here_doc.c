/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:15:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/21 11:03:09 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	get_heredoc_from_limiter(char *str, int fd)
{
	char	*limiter;

	if (fd != 0)
		close(fd);
	limiter = get_redirect_filename(&str[2]);
	if (limiter == 0)
		return (-1);
	fd = heredoc_input(limiter);
	free(limiter);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	get_heredoc_fd(char *str)
{
	int		fd;
	int		i;

	fd = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += quote_length(&str[i]);
		if (!ft_strncmp(&str[i], "<<", 2))
		{
			fd = get_heredoc_from_limiter(&str[i], fd);
			if (fd == -1)
				return (-1);
		}
		i++;
	}
	return (fd);
}

int	push_heredoc_fds_list(t_vec *heredoc_fds, t_vec *fds, char **strs)
{
	if (vec_push(heredoc_fds, fds) < 0)
	{
		vec_free(fds);
		ft_free_split(strs);
		return (-1);
	}
	ft_free_split(strs);
	ft_bzero(fds, sizeof(t_vec));
	return (0);
}

int	add_heredoc_fd(char **strs, int j, t_vec *fds)
{
	int	fd;

	fd = get_heredoc_fd(strs[j]);
	if (fd == -1)
	{
		vec_free(fds);
		ft_free_split(strs);
		return (-1);
	}
	if (vec_push(fds, &fd) < 0)
	{
		vec_free(fds);
		ft_free_split(strs);
		return (-1);
	}
	return (0);
}

int	get_heredocs(t_vec *heredoc_fd_list, t_vec *cmd_lines, size_t i, int j)
{
	char	**strs;
	t_vec	fds;

	while (i < cmd_lines->len)
	{
		if (vec_new(&fds, 1, sizeof(int)) < 0)
			return (-1);
		strs = ft_split_pipe(*(char **)vec_get(cmd_lines, i), '|');
		if (!strs)
		{
			vec_free(&fds);
			return (-1);
		}
		j = 0;
		while (strs[j] != 0)
		{
			if (add_heredoc_fd(strs, j, &fds) < 0)
				return (-1);
			j++;
		}
		if (push_heredoc_fds_list(heredoc_fd_list, &fds, strs) == -1)
			return (-1);
		i++;
	}
	return (1);
}
