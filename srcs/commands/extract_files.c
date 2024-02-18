/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:13:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/16 16:23:33 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

char	*get_redirect_filename(char	*str)
{
	char	*no_quotes;

	while (ft_isspace(*str))
		str++;
	if (!ft_strchr(str, '\"') && !ft_strchr(str, '\''))
		return (ft_strdup(str));
	no_quotes = remove_outer_quotes(str);
	if (no_quotes == 0)
		return (0);
	return (no_quotes);
}

int	set_redirect(t_command *command, int original_fd,
	char **red_comm_file, int heredoc_fd)
{
	int			new_fd;
	t_redirect	*redirect;

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
	if (vec_push(&command->redirects, redirect) < 0)
		return (ft_error("minishell: malloc failed"));
	free(redirect);
	return (1);
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
			free(*(char **)(vec_get(&command->argv, i)));
			vec_remove(&command->argv, i);
			i--;
		}
		i++;
	}
	return (1);
}
