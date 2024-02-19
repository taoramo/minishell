/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:48:28 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:48:30 by toramo           ###   ########.fr       */
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

int	check_line_after_parenth(char *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_line[i])
	{
		if (i != 0 && cmd_line[i] == ')'
			&& !ft_is_inside(cmd_line, i, '"')
			&& !ft_is_inside(cmd_line, i, 39))
		{
			j = i + 1;
			while (ft_isspace(cmd_line[j]) && j >= 0)
				j++;
			if (cmd_line[j] != '&' && cmd_line[j] != '|' && cmd_line[j] != 0)
				return (ft_error("syntax error near unexpected token `)’"));
		}
		i++;
	}
	return (0);
}
