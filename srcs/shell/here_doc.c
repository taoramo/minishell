/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:15:30 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/15 10:10:47 by hpatsi           ###   ########.fr       */
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
	char	*no_quotes;
	int		fd;
	int		i;

	if (*str == 0)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	i = 0;
	while(str[i] != 0 && !ft_isspace(str[i]) 
			&& (str[i] != '<' && (!ft_is_inside(str, i, '\"') && !ft_is_inside(str, i, '\'')))
			&& (str[i] != '>' && (!ft_is_inside(str, i, '\"') && !ft_is_inside(str, i, '\''))))
		i++;
	no_quotes = remove_outer_quotes(str);
	i -= ft_strlen(str) - ft_strlen(no_quotes);
	limiter = ft_substr(no_quotes, 0, i);
	free(no_quotes);
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
			if (fd != 0)
				close(fd);
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
	int		j;
	char	**strs;
	int		fd;
	t_vec	*fds;

	i = 0;
	while (i < cmd_lines->len)
	{
		fds = ft_calloc(1, sizeof(t_vec));
		vec_new(fds, 1, sizeof(int));
		strs = ft_split(*(char **)vec_get(cmd_lines, i), '|');
		j = 0;
		while (strs[j] != 0)
		{
			fd = get_heredoc_fd(strs[j]);
			if (fd == -1)
				return (-1);
			vec_push(fds, &fd);
			j++;
		}
		vec_push(heredoc_fds, fds);
		ft_free_split(strs);
		i++;
	}

	// size_t y = 0;
	// while (y < heredoc_fds->len)
	// {
	// 	ft_printf("heredoc_fds %d\n", y);
	// 	t_vec command_heredoc_fds = *(t_vec *) vec_get(heredoc_fds, y);
	// 	size_t x = 0;
	// 	while (x < command_heredoc_fds.len)
	// 	{
	// 		ft_printf("fds x = %d\n", *(int *)vec_get(&command_heredoc_fds, x));
	// 		x++;
	// 	}
	// 	y++;
	// }

	return (1);
}
