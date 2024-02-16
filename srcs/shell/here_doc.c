/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:15:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/15 13:36:23 by hpatsi           ###   ########.fr       */
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
	signal_heredoc(0);
	if (read_input(nl_limiter, pipe_fds) == -1)
	{
		free(nl_limiter);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		toggle_carret(1);
		return (-2);
	}
	signal_heredoc(1);
	free(nl_limiter);
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

int	handle_heredoc_fd(char *str, int fd, int *i)
{
	char	*limiter;

	*i = *i + 2;
	if (fd != 0)
		close(fd);
	limiter = get_redirect_filename(&str[*i]);
	if (limiter == 0)
		return (-1);
	fd = infile_from_stdin(limiter);
	free(limiter);
	if (fd == -1)
		return (-1);
	return (0);
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
		if (str[i] == '<' && str[i + 1] == '<')
		{
			if (handle_heredoc_fd(str, fd, &i) < 0)
				return (-1);
		}
		i++;
	}
	return (fd);
}

int	push_heredoc_fds(t_vec *heredoc_fds, t_vec *fds, char **strs)
{
	if (vec_push(heredoc_fds, fds) < 0)
		return (-1);
	ft_free_split(strs);
	ft_bzero(fds, sizeof(t_vec));
	return (0);
}

int	get_fds_vec(char *str, t_vec *fds)
{
	int	fd;

	fd = get_heredoc_fd(str);
	if (fd == -1)
		return (-1);
	if (vec_push(fds, &fd) < 0)
		return (-1);
	return (0);
}

int	get_heredocs(t_vec *heredoc_fds, t_vec *cmd_lines, size_t i, int j)
{
	char	**strs;
	t_vec	fds;

	while (i < cmd_lines->len)
	{
		if (vec_new(&fds, 1, sizeof(int)) < 0)
			return (-1);
		strs = ft_split_pipe(*(char **)vec_get(cmd_lines, i), '|');
		if (!strs)
			return (-1);
		j = 0;
		while (strs[j] != 0)
		{
			get_fds_vec(strs[j], &fds);
			j++;
		}
		if (push_heredoc_fds(heredoc_fds, &fds, strs))
			return (-1);
		i++;
	}
	return (1);
}
