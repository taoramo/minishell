/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:10:29 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 17:10:30 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_argv_elem(t_vec *dst, t_vec *argv, int i)
{
	char			**strs;

	strs = (char **)argv->memory;
	if (vec_push(dst, &strs[i]) < 0)
		return (exp_wc_err(dst, "error allocating memory"));
	return (0);
}

int	expand_args(t_vec *dst, t_vec *argv, t_vec *newargv)
{
	size_t	i;
	char	**strs;

	i = 0;
	strs = (char **)argv->memory;
	while (i < argv->len)
	{
		if (ft_strchr(strs[i], '*')
			&& !ft_is_inside(strs[i], ft_strchr(strs[i], '*') - strs[i], '"')
			&& !ft_is_inside(strs[i], ft_strchr(strs[i], '*') - strs[i], 39))
		{
			if (push_expanded(dst, strs, i) < 0)
				return (ft_error("minishell: error creating argv"));
		}
		else if (push_argv_elem(newargv, argv, i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	expand_star(t_vec *argv)
{
	t_vec			dst;
	t_vec			newargv;

	if (vec_new(&dst, 32, sizeof(char *)) < 0)
		return (ft_error("minishell: error allocating memory"));
	if (vec_new(&newargv, 32, sizeof(char *)) < 0)
		return (ft_error("minishell: error allocating memory"));
	if (expand_args(&dst, argv, &newargv) < 0)
		return (-1);
	vec_append(&newargv, &dst);
	vec_free(argv);
	ft_memcpy(argv, &newargv, sizeof(t_vec));
	vec_free(&dst);
	return (0);
}
