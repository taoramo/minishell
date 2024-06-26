/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:13:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/23 08:51:26 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

char	*get_redirect_filename(char	*str)
{
	char	*filename;
	char	*no_quotes;
	int		i;

	while (ft_isspace(*str))
		str++;
	i = 0;
	while (str[i] != 0 && (ft_is_inside_any(str, i)
			|| (!ft_isspace(str[i]) && str[i] != '<' && str[i] != '>'
				&& str[i] != '|' && str[i] != '&')))
		i++;
	filename = ft_substr(str, 0, i);
	if (filename == 0 || (!ft_strchr(str, '\"') && !ft_strchr(str, '\'')))
		return (filename);
	no_quotes = remove_outer_quotes(filename);
	free(filename);
	return (no_quotes);
}

int	set_redirect(t_command *command, int original_fd,
	char **red_comm_file, int heredoc_fd)
{
	int			new_fd;
	t_redirect	*redirect;
	int			ret;

	new_fd = -1;
	if (ft_strncmp(red_comm_file[0], ">>", 2) == 0)
		new_fd = open(red_comm_file[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (ft_strncmp(red_comm_file[0], "<<", 2) == 0)
		new_fd = heredoc_fd;
	else if (ft_strncmp(red_comm_file[0], ">", 1) == 0)
		new_fd = open(red_comm_file[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strncmp(red_comm_file[0], "<", 1) == 0)
		new_fd = open(red_comm_file[1], O_RDONLY);
	if (new_fd == -1)
		return (minishell_error(red_comm_file[1], strerror(errno)));
	redirect = malloc(sizeof(t_redirect));
	if (redirect == 0)
		return (-1);
	redirect->origial_fd = original_fd;
	redirect->new_fd = new_fd;
	ret = vec_push(&command->redirects, redirect);
	free(redirect);
	return (ret);
}

int	get_redirect_command_file(char *red_comm_file[], char *str)
{
	int		i;

	while (*str >= '0' && *str <= '9')
		str++;
	i = 0;
	while (str[i] != 0 && (str[i] == '>' || str[i] == '<'))
		i++;
	red_comm_file[0] = ft_substr(str, 0, i);
	if (red_comm_file[0] == 0)
		return (-1);
	red_comm_file[1] = get_redirect_filename(&str[i]);
	if (red_comm_file[1] == 0)
	{
		free(red_comm_file[0]);
		return (-1);
	}
	return (1);
}

int	get_origfd(char *str)
{
	int		i;

	if (*str == '>')
		return (1);
	else if (*str == '<')
		return (0);
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i == 0 || str[i] == 0 || (str[i] != '<' && str[i] != '>'))
		return (-1);
	return (ft_atoi(str));
}

int	extract_files(t_command *command, int herefd)
{
	char	**strs;
	size_t	i;
	char	*comm_file[2];
	int		ret;

	strs = *(char ***) &command->argv;
	i = 0;
	while (i < command->argv.len)
	{
		if (get_origfd(strs[i]) >= 0)
		{
			if (get_redirect_command_file(comm_file, strs[i]) == -1)
				return (-1);
			ret = set_redirect(command, get_origfd(strs[i]), comm_file, herefd);
			free(comm_file[0]);
			free(comm_file[1]);
			if (ret == -1)
				return (-1);
			if (vec_remove_str(&command->argv, i) == -1)
				return (-1);
			i--;
		}
		i++;
	}
	return (1);
}
