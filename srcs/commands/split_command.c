/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:52:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/15 16:54:45 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	is_delimeter(char c)
{
	return (c == 0 || ft_isspace(c) || c == '>' || c == '<' || c == '|');
}

int	quote_length(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != str[0])
		i++;
	return (i);
}

int	add_redirect(t_vec *strs, char *str, int i)
{
	int		numlen;
	char	*num;
	char	*redirect;
	char	*filename;

	numlen = 1;
	while (i - numlen >= 0)
	{
		if (!ft_isdigit(str[i - numlen]))
		{
			numlen = 1;
			break ;
		}
		numlen++;
	}
	numlen -= 1;
	
	if (numlen > 0)
		num = ft_substr(str, i - numlen, numlen);
	
	if (!ft_strncmp(&str[i], ">>", 2) || !ft_strncmp(&str[i], "<<", 2))
	{
		redirect = ft_substr(str, i, 2);
		filename = get_redirect_filename(&str[i+2]);
	}
	else
	{
		redirect = ft_substr(str, i, 1);
		filename = get_redirect_filename(&str[i+1]);
	}

	if (numlen > 0)
		redirect = ft_strjoin(num, redirect);
	redirect = ft_strjoin(redirect, filename);

	ft_printf("redirect = %s\n", redirect);
	
	vec_push(strs, &redirect);

	while (str[i] == '>' || str[i] == '<' || ft_isspace(str[i]))
		i++;
	while (str[i] != 0 && str[i] != '>' && str[i] != '<' && !ft_isspace(str[i]))
		i++;
	ft_printf("str[i] = %s\n", &str[i]);

	return (i);
}

int	add_str(t_vec *strs, char *str, int i)
{
	char	*substr;
	
	if (str[i] == '<' || str[i] == '>')
		return (add_redirect(strs, str, i));
	substr = ft_substr(str, 0, i);
	if (substr == 0)
		return (-1);
	if (vec_push(strs, &substr) == -1)
		return (-1);
	return (0);
}

int	split_command(t_vec *strs, char *str)
{
	int	i;
	
	while (ft_isspace(*str))
		str++;
	i = 0;
	while (str[i] != 0)
	{
		i++;
		if (str[i] == '\"' || str[i] == '\'')
			i += quote_length(&str[i]);
		if (is_delimeter(str[i]))
		{
			if (add_str(strs, str, i) == -1)
			{
				free_split_vec(strs);
				return (-1);
			}
			if (str[i] == 0)
				break ;
			str = &str[i] + 1;
			i = 0;
		}
	}
	return (1);
}
