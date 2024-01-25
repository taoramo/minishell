/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:13:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/25 15:59:49 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	unquoted_strlen(char *str)
{
	int	i;
	int	len;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	len = 0;
	while (str[i] != 0 && !ft_isspace(str[i]))
	{
		if (str[i] == '\"' || str[i] == '\'')
			i++;
		i++;
		len++;
	}
	return (len);
}
void	unquoted_strcpy(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (ft_isspace(src[i]))
		i++;
	j = 0;
	while (src[i] != 0 && !ft_isspace(src[i]))
	{
		if (src[i] == '\"' || src[i] == '\'')
			i++;
		dst[j] = src[i];
		j++;
		i++;
	}
}

int	set_file(int index, int *fd, char *str)
{
	char	*filename;

	filename = ft_calloc(unquoted_strlen(str) + 1, sizeof(char));
	if (filename == 0)
		return (-1);
	unquoted_strcpy(filename, str);
	if (index == 0)
		*fd = open(filename, O_RDONLY);
	if (index == 1)
		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (*fd == -1)
		perror(filename);
	return (*fd);
}

int	extract_files(int file_fds[], char *str)
{	
	int	i;

	file_fds[0] = 0;
	file_fds[1] = 1;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\"' || str[i] == '\'')
			i += quote_length(&str[i]);
		if (str[i] == '<')
			set_file(0, &file_fds[0], &str[i+1]);
		if (str[i] == '>')
			set_file(1, &file_fds[1], &str[i+1]);
		i++;
	}
	ft_printf("fd1 = %d, fd2 = %d\n", file_fds[0], file_fds[1]);
	return (1);
}