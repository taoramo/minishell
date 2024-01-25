/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:52:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/25 15:15:17 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	redirect_length(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] == '>' || str[i] == '<')
		i++;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

int	add_str(t_vec *strs, char *str, char *end)
{
	char	*substr;

	if (*(end - 1) == '\"' || *(end - 1) == '\'')
		substr = ft_substr((str + 1), 0, (end - 1) - (str + 1));
	else
		substr = ft_substr(str, 0, end - str);
	if (substr == 0)
		return (-1);
	if (vec_push(strs, &substr) == -1)
	{
		free(substr);
		return (-1);
	}
	return (1);
}

int	split_command(t_vec *strs, char *str)
{
	char	*end;

	end = str;
	while (*end != 0)
	{
		end++;
		if (*end == '\"' || *end == '\'')
			end += quote_length(end);
		if (*end == '>' || *end == '<' || !ft_strncmp(end, "<<", 2) || !ft_strncmp(end, ">>", 2))
			end += redirect_length(end);
		if (ft_isspace(*end) || *end == 0)
		{
			if (str < end)
			{
				if (add_str(strs, str, end) == -1)
					return (-1);
			}
			str = end + 1;
		}
	}
	return (1);
}
