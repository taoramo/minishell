/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:52:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 10:25:57 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strsfree(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

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

int	try_add_str(char **strs, char *str, int end)
{
	static int	i;
	static int	start;
	char		*substr;

	if (end == 1)
	{
		start = 0;
		i = 0;
	}
	if (str[end] == '\"' || str[end] == '\'')
		end += quote_length(&str[end]);
	if (str[end] == ' ' || str[end] == 0)
	{
		if (start < end)
		{
			substr = ft_substr(str, start, end - start);
			if (substr == 0)
				return (-1);
			strs[i] = substr;
			i++;
		}
		start = end + 1;
	}
	return (end);
}

char	**split_command(char *str)
{
	char	**strs;
	int		end;

	strs = ft_calloc(count_splits(str) + 1, sizeof(char *));
	if (strs == NULL)
		return (0);
	end = 0;
	while (str[end] != 0)
	{
		end++;
		end = try_add_str(strs, str, end);
		if (end == -1)
		{
			ft_strsfree(strs);
			return (0);
		}
	}
	return (strs);
}
