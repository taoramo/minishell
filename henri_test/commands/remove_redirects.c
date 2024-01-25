/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:32:44 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/25 11:21:14 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	remove_redirect(char **str, int i)
{
	(*str)[i] = ' ';
	while (ft_isspace((*str)[i]))
		i++;
	while ((*str)[i] != 0 && !ft_isspace((*str)[i]))
	{
		(*str)[i] = ' ';
		i++;
	}
}

void	remove_redirects(char **str)
{
	int		i;

	i = 0;
	while ((*str)[i] != 0)
	{
		if ((*str)[i] == '\"' || (*str)[i] == '\'')
			i += quote_length(&((*str)[i]));
		if ((*str)[i] == '<' || (*str)[i] == '>')
			remove_redirect(str, i);
		i++;
	}
}