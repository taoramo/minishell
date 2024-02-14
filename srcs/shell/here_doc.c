/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:15:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/14 14:58:10 by hpatsi           ###   ########.fr       */
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
	toggle_carret(0);
	if (read_input(nl_limiter, pipe_fds) == -1)
	{
		free(nl_limiter);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		toggle_carret(1);
		return (-2);
	}
	toggle_carret(1);
	free(nl_limiter);
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

int read_heredoc(char *str)
{
	char	*limiter;
	int		fd;
	int		i;

	if (*str == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	i = 0;
	while(str[i] != 0 && !ft_isspace(str[i]) && str[i] != '<' && str[i] != '>')
		i++;
	limiter = ft_substr(str, 0, i);
	if (limiter == 0)
		return (0);
	fd = infile_from_stdin(limiter);
	free(limiter);
	return (fd);
}

int	get_heredoc_fd(char *str)
{
	int fd;
	int	i;

	fd = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += quote_length(&str[i]);
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			while (ft_isspace(str[i]))
				i++;
			fd = read_heredoc(&str[i]);
			if (fd == -1)
				return (-1);
		}
		i++;
	}
	return (fd);
}

int	get_heredocs(t_vec *heredoc_fds, t_vec *cmd_lines)
{
	size_t	i;
	char	*str;
	int		fd;

	vec_new(heredoc_fds, cmd_lines->len, sizeof(int));
	i = 0;
	while (i < cmd_lines->len)
	{
		str = *(char **)vec_get(cmd_lines, i);
		fd = get_heredoc_fd(str);
		vec_push(heredoc_fds, &fd);
		i++;
	}
	return (1);
}
