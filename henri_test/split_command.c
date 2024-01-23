/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaned_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:23:15 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/23 12:23:15 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	quote_length(char *str)
{
	char *end_ptr;

	end_ptr = ft_memchr(str + 1, *str, ft_strlen(str + 1));
	if (end_ptr == 0)
		return (-1);
	return end_ptr - str + 1;
}

t_vec	*split_command(char *str)
{
	t_vec	*strs;
	char	*substr;
	int		start;
	int		end;

	if (str == NULL)
		return (0);
	strs = ft_calloc(1, sizeof(t_vec));
	if (strs == 0)
		return (0);
	if (vec_new(strs, 1, sizeof(char *)) == -1)
		return (0);
	start = 0;
	end = 1;
	while (str[end] != 0)
	{
		end++;
		if (str[end] == '\"' || str[end] == '\'')
			end += quote_length(&str[end]);
		if (str[end] == ' ' || str[end] == 0)
		{
			if (start < end)
			{
				substr = ft_substr(str, start, end - start);
				if (substr == 0)
				{
					vec_free(strs);
					free(strs);
					return (0);
				}
				vec_push(strs, &substr);
			}
			start = end + 1;
		}
	}
	return (strs);
}