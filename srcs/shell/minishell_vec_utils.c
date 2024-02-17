/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_vec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:14:46 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:14:48 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_supergroup(void *arg)
{
	char		*ptr;
	int			i;

	ptr = arg;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '(')
			return (1);
		i++;
	}
	return (0);
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
