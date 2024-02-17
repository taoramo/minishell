/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:01:21 by toramo            #+#    #+#             */
/*   Updated: 2024/02/16 11:01:25 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(t_vec *str_vec, size_t start)
{
	size_t	i;
	char	c;

	i = 0;
	start++;
	while (start + i < str_vec->len)
	{
		c = *(char *)vec_get(str_vec, start + i);
		if (c == '\'' || c == '\"' || c == '$')
			return (ft_substr((char *) str_vec->memory, start, i));
		if (c == '*' && !ft_is_inside((char *) str_vec->memory, start + i, '\'')
			&& !ft_is_inside((char *) str_vec->memory, start + i, '\"'))
			return (ft_substr((char *) str_vec->memory, start, i));
		i++;
	}
	return (ft_substr((char *) str_vec->memory, start, i));
}
