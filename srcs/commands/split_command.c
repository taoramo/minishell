/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:52:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/21 13:32:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	quote_length(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != str[0])
		i++;
	return (i);
}

int	add_str(t_vec *strs, char *str, int i)
{
	char	*substr;

	substr = ft_substr(str, 0, i);
	if (substr == 0)
		return (-1);
	if (vec_push(strs, &substr) == -1)
	{
		free(substr);
		return (-1);
	}
	return (0);
}

int	split_command(t_vec *strs, char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		while (ft_isspace(str[i]))
			i++;
		str = &str[i];
		i = 0;
		while (str[i] != 0 && !ft_isspace(str[i]))
		{
			if (str[i] == '\"' || str[i] == '\'')
				i += quote_length(&str[i]);
			i++;
		}
		if (i == 0)
			break ;
		if (add_str(strs, str, i) == -1)
			return (-1);
	}
	return (1);
}
