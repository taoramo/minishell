/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:52:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 11:14:45 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "strs_helpers.h"

int	quote_length(char *str)
{
	char	*end_ptr;

	end_ptr = ft_memchr(str + 1, *str, ft_strlen(str + 1));
	if (end_ptr == 0)
		return (-1);
	return (end_ptr - str);
}

int	count_splits(char *str)
{
	int	start;
	int	end;
	int	count;

	start = 0;
	end = 0;
	count = 0;
	while (str[end] != 0)
	{
		end++;
		if (str[end] == '\"' || str[end] == '\'')
			end += quote_length(&str[end]);
		if (str[end] == ' ' || str[end] == 0)
		{
			if (start < end)
				count++;
			start = end + 1;
		}
	}
	return (count);
}

int	try_add_str(char ***strs, char **str, char **end)
{
	char		*substr;

	if (**end == '\"' || **end == '\'')
		*end += quote_length(*end);
	if (**end == ' ' || **end == 0)
	{
		if (*str < *end)
		{
			if (*(*end - 1) == '\"' || *(*end - 1) == '\'')
				substr = ft_substr((*str + 1), 0, (*end - 1) - (*str + 1));
			else
				substr = ft_substr(*str, 0, *end - *str);
			if (substr == 0)
				return (-1);
			**strs = substr;
			*strs += 1;
		}
		*str = *end + 1;
	}
	return (1);
}

char	**split_command(char *str)
{
	char	**strs;
	char	**tab;
	char	*end;

	strs = ft_calloc(count_splits(str) + 1, sizeof(char *));
	if (strs == NULL)
		return (0);
	tab = strs;
	end = str;
	while (*end != 0)
	{
		end++;
		if (try_add_str(&strs, &str, &end) == -1)
		{
			ft_strsfree(strs);
			return (0);
		}
	}
	return (tab);
}
