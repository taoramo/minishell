/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command_vec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:47:58 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 09:47:58 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	quote_length(char *str)
{
	char	*end_ptr;

	end_ptr = ft_memchr(str + 1, *str, ft_strlen(str + 1));
	if (end_ptr == 0)
		return (-1);
	return (end_ptr - str);
}

int	add_str(t_vec *strs, char *str, int start, int end)
{
	char	*substr;

	if (start < end)
	{
		substr = ft_substr(str, start, end - start);
		if (substr == 0)
			return (-1);
		vec_push(strs, &substr);
	}
	return (1);
}

int	split_command(t_vec *strs, char *str)
{
	int		start;
	int		end;

	if (str == NULL)
		return (-1);
	start = 0;
	end = 0;
	while (str[end] != 0)
	{
		end++;
		if (str[end] == '\"' || str[end] == '\'')
			end += quote_length(&str[end]);
		if (str[end] == ' ' || str[end] == 0)
		{
			if (add_str(strs, str, start, end) == -1)
				return (-1);
			start = end + 1;
		}
	}
	return (1);
}
