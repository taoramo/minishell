/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:15:16 by toramo            #+#    #+#             */
/*   Updated: 2024/02/16 09:15:17 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_wc_err(t_vec *new, char *msg)
{
	free_split_vec(new);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	expnd_rdrct(t_vec *dst, char *path, char *arg)
{
	char	*expanded;

	expanded = 0;
	if (arg[0] == '<')
		expanded = ft_strjoin("< ", path);
	if (arg[0] == '>')
		expanded = ft_strjoin("> ", path);
	free(path);
	free(arg);
	if (!expanded)
		return (-1);
	if (vec_push(dst, &expanded) < 0)
		return (-1);
	return (1);
}

int	ambiguous_wildcard(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] == '<' || arg[i] == '>' || ft_isspace(arg[i])))
		i++;
	write(2, "minishell: ", 11);
	write(2, &arg[i], 1);
	write(2, ": ambiguous redirect\n", 21);
	return (-1);
}

int	is_rdrct(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] == '<' || arg[i] == '>')
		return (1);
	return (0);
}
