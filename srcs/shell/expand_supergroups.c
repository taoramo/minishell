/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_supergroups.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:08:24 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:08:41 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_parentheses(t_cmd_line *cmd_line)
{
	size_t	i;
	size_t	open_parentheses;
	size_t	start;
	size_t	end;

	open_parentheses = 0;
	i = 0;
	while (cmd_line->str[i] && cmd_line->str[i] != '(')
		i++;
	open_parentheses++;
	start = i;
	while (cmd_line->str[i] && !(open_parentheses == 0
			&& cmd_line->str[i] == ')'))
	{
		i++;
		if (cmd_line->str[i] == '(')
			open_parentheses++;
		if (cmd_line->str[i] == ')')
			open_parentheses--;
	}
	end = i;
	ft_memmove(&cmd_line->str[start], &cmd_line->str[start + 1],
		ft_strlen(&cmd_line->str[start + 1]));
	cmd_line->str[end - 1] = 0;
}
