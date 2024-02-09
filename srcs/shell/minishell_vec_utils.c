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

int	contains_supergroup(void *arg)
{
	char		*ptr;
	int			i;

	ptr = arg;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '(')
			return (1);
		i++;
	}
	return (0);
}
