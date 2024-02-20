/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_andor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:48:28 by toramo            #+#    #+#             */
/*   Updated: 2024/02/20 14:45:16 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_consecutive_andor(const char *line)
{
	int	i;
	int	consecutive;
	int	last_consecutive_i;

	i = 0;
	consecutive = 0;
	last_consecutive_i = 0;
	while (line[i])
	{
		if ((line[i] == '|' || line[i] == '&') && !ft_is_inside(line, i, '"')
			&& !ft_is_inside(line, i, 39)
			&& (!consecutive || last_consecutive_i == i - 1))
		{
			consecutive++;
			last_consecutive_i = i;
		}
		else
			consecutive = 0;
		if (consecutive > 2)
			return (print_syntax_error(line[i]));
		i++;
	}
	return (0);
}

int	check_empty_andor(char **strs, size_t len)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	while (i < len)
	{
		j = 0;
		c = strs[i][0];
		while (strs[i][j] == '&' || strs[i][j] == '|')
			j++;
		while (ft_isspace(strs[i][j]))
			j++;
		if (strs[i][j] == 0)
			return (redirect_check_error(c));
		i++;
	}
	return (0);
}

int	check_andor_syntax(char **strs, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		if (strs[i][0] == '&' || strs[i][0] == '|')
		{
			j = j + 2;
			if (strs[i][2] == '|' || (strs[i][0] == '|' && strs[i][1] != '|'))
				return (ft_error("syntax error near unexpected token `|’"));
			if (strs[i][2] == '&')
				return (ft_error("syntax error near unexpected token `&’"));
			while (ft_isspace(strs[i][j]))
				j++;
			if (strs[i][j] == '|')
				return (ft_error("syntax error near unexpected token `|’"));
			if (strs[i][j] == '&')
				return (ft_error("syntax error near unexpected token `&’"));
		}
		i++;
	}
	return (check_empty_andor(strs, len));
}
