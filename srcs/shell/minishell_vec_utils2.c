/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_vec_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 09:23:32 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/23 09:25:07 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	vec_insert_substr(t_vec *strs, int i, char *str, int len)
{
	char	*substr;

	substr = ft_substr(str, 0, len);
	if (substr == 0)
		return (-1);
	if (vec_insert(strs, &substr, i) == -1)
	{
		free(substr);
		return (-1);
	}
	return (1);
}

int	vec_remove_insert_str(t_vec *strs, int i, char *str)
{
	if (vec_remove_str(strs, i) == -1)
		return (-1);
	if (vec_insert(strs, &str, i) == -1)
		return (-1);
	return (1);
}
