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
		if (consecutive > 2)
			return (ft_error("syntax error near unexpected token '|'"));
		i++;
	}
	return (0);
}
