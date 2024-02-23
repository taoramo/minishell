/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_vec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:14:46 by toramo            #+#    #+#             */
/*   Updated: 2024/02/23 08:56:14 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	vec_remove_str(t_vec *vec, size_t i)
{
	char	*str;

	str = *(char **) vec_get(vec, i);
	if (vec_remove(vec, i) == -1)
		return (-1);
	free(str);
	return (1);
}

int	vec_sort_strncmp(void *one, void *two)
{
	char	*sone;
	char	*stwo;

	sone = *(char **)one;
	stwo = *(char **)two;
	return (ft_strncmp(sone, stwo, 1024));
}

int	copy_split_vec(t_vec *dst, t_vec *src)
{
	size_t	i;
	char	*str;

	if (vec_new(dst, src->len, sizeof(char *)) < 0)
		return (-1);
	i = 0;
	while (i < src->len)
	{
		str = ft_strdup(*(char **)vec_get(src, i));
		if (!str)
			return (free_split_vec(dst));
		if (vec_push(dst, &str) < 0)
			return (free_split_vec(dst));
		i++;
	}
	return (0);
}

void	vec_iter_free(void *arg)
{
	vec_free((t_vec *)arg);
}

void	free_heredoc_fd_list(t_vec *heredoc_fd_list)
{
	vec_iter(heredoc_fd_list, vec_iter_free);
	vec_free(heredoc_fd_list);
}
