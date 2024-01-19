/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:10:21 by hpatsi            #+#    #+#             */
/*   Updated: 2023/11/14 15:10:21 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	trim_last_line(char *last_read)
{
	ssize_t	nl_i;
	size_t	i;

	nl_i = ft_i_strchr(last_read, '\n');
	if (nl_i == -1)
	{
		ft_bzero(last_read, BUFFER_SIZE + 1);
		return ;
	}
	i = 0;
	while (last_read[nl_i + 1 + i] != 0)
	{
		last_read[i] = last_read[nl_i + 1 + i];
		i++;
	}
	last_read[i] = 0;
}

static char	*handle_return(char *current_buf, char *last_read)
{
	char	*temp;
	ssize_t	nl_i;

	if (ft_strlen(current_buf) == 0)
	{
		free(current_buf);
		return (0);
	}
	nl_i = ft_i_strchr(current_buf, '\n');
	if (nl_i != -1)
		temp = ft_strldup(current_buf, nl_i + 1);
	else
		temp = ft_strldup(current_buf, ft_strlen(current_buf));
	free(current_buf);
	trim_last_line(last_read);
	if (temp == 0)
		return (0);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	last_read[1024][BUFFER_SIZE + 1];
	ssize_t		last_size;
	char		*current_buf;

	if (fd < 0)
		return (0);
	current_buf = ft_strldup(last_read[fd], ft_strlen(last_read[fd]));
	if (current_buf == 0)
		return (0);
	last_size = BUFFER_SIZE;
	while (ft_i_strchr(last_read[fd], '\n') == -1 && last_size == BUFFER_SIZE)
	{
		ft_bzero(last_read[fd], BUFFER_SIZE + 1);
		last_size = read(fd, last_read[fd], BUFFER_SIZE);
		if (last_size == -1)
		{
			free(current_buf);
			return (0);
		}
		current_buf = ft_stradd(current_buf, last_read[fd]);
		if (current_buf == 0)
			return (0);
	}
	return (handle_return(current_buf, last_read[fd]));
}
