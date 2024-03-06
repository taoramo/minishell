/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:09:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/22 12:33:01 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	replace_argv(t_vec *argv, t_vec *src, size_t i)
{
	size_t	j;
	char	*original_str;

	original_str = *(char **) vec_get(argv, i);
	if (vec_remove(argv, i) == -1)
		return (-1);
	free(original_str);
	j = 0;
	while (j < src->len)
	{
		if (vec_insert(argv, (char **) vec_get(src, j), i + j) < 0)
			return (-1);
		j++;
	}
	return (1);
}

int	handle_split_results(t_vec *argv, t_vec split, size_t i)
{
	char	*old;

	old = *(char **) vec_get(argv, i);
	if (split.len == 1
		&& !ft_strncmp(old, *(char **) vec_get(&split, 0), ft_strlen(old)))
		free_split_vec(&split);
	else if (split.len >= 1)
	{
		if (replace_argv(argv, &split, i) == -1)
		{
			vec_free(&split);
			return (-1);
		}
		i += split.len - 1;
		vec_free(&split);
	}
	else
	{
		free_split_vec(&split);
		old = *(char **) vec_get(argv, i);
		if (vec_remove(argv, i) == -1)
			return (-1);
		free(old);
	}
	return (1);
}

int	split_expanded_command(t_vec *argv)
{
	t_vec	split;
	size_t	i;

	i = 0;
	while (i < argv->len)
	{
		if (vec_new(&split, 4, sizeof(char *)) == -1)
			return (-1);
		if (split_command(&split, *(char **) vec_get(argv, i)) == -1)
		{
			vec_free(&split);
			return (-1);
		}
		if (handle_split_results(argv, split, i) == -1)
			return (-1);
		i++;
	}
	return (1);
}
