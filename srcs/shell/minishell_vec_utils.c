/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_vec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:14:46 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:14:48 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_supergroup(void *arg)
{
	t_cmd_line	*ptr;
	int			i;

	ptr = arg;
	i = 0;
	while (ptr->str[i])
	{
		if (ptr->str[i] == '(')
			return (1);
		i++;
	}
	return (0);
}

void	free_cmd_line_str(void *arg)
{
	t_cmd_line	*ptr;

	ptr = arg;
	free(ptr->str);
}
