/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:19:48 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/03 12:00:09 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_line(int *pipe_fds, char *read_str)
{
	if (write(pipe_fds[1], read_str, ft_strlen(read_str)) == -1)
	{
		free(read_str);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	return (1);
}

int	read_input(char **argv, int *pipe_fds)
{
	char	*read_str;

	while (1)
	{
		ft_printf("pipe heredoc> ");
		read_str = get_next_line(0);
		if (read_str == 0)
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			return (-1);
		}
		if (ft_strncmp(read_str, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		if (write_line(pipe_fds, read_str) == -1)
			return (-1);
		free(read_str);
	}
	free(read_str);
	return (1);
}

int	infile_from_stdin(char **argv, int *file_fds)
{
	int		pipe_fds[2];

	if (pipe(pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	if (read_input(argv, pipe_fds) == -1)
		return (-1);
	close(pipe_fds[1]);
	file_fds[0] = pipe_fds[0];
	return (1);
}

int	set_here_doc(int argc, char **argv, int *file_fds)
{
	if (infile_from_stdin(argv, file_fds) == -1)
		return (-1);
	file_fds[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (file_fds[1] == -1)
	{
		perror(argv[argc - 1]);
		return (-1);
	}
	return (1);
}

int	set_files(int argc, char **argv, int *file_fds)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (set_here_doc(argc, argv, file_fds));
	file_fds[0] = open(argv[1], O_RDONLY);
	if (file_fds[0] == -1)
		perror(argv[1]);
	file_fds[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file_fds[1] == -1)
	{
		perror(argv[argc - 1]);
		if (file_fds[0] != -1)
			close(file_fds[0]);
		return (-1);
	}
	return (1);
}
