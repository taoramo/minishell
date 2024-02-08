/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:31:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/08 19:16:15 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_env(t_vec *argv, t_vec *env)
{
	char	**str_ptr;
	char	*new_str;
	size_t	i;

	i = 0;
	while(i < argv->len)
	{
		str_ptr = (char **)vec_get(argv, i);
		if (**str_ptr == '$')
		{
			new_str = ft_calloc(1, 1000); // should be handled in getenv
			ft_getenv(new_str, *str_ptr + 1, env);
			free(*str_ptr);
			*str_ptr = new_str;
		}
		i++;
	}
	return (1);
}
