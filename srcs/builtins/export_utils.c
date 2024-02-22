/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:04:39 by toramo            #+#    #+#             */
/*   Updated: 2024/02/22 15:15:08 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_entry_exists(char *str, t_vec *env)
{
	size_t	i;
	char	**entries;

	entries = (char **)env->memory;
	i = 0;
	while (i < env->len)
	{
		if (!ft_strncmp(str, entries[i], ft_strlen_member(entries[i], '=')))
		{
			if (contains_plusequals(str)
				&& ft_strlen_member(entries[i], '=')
				!= ft_strlen_member(str, '+'))
				return (0);
			if (contains_equals(str) && !contains_plusequals(str)
				&& ft_strlen_member(entries[i], '=')
				!= ft_strlen_member(str, '='))
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	remove_entry(char *str, t_vec *env)
{
	size_t	i;
	char	**entries;

	entries = (char **)env->memory;
	i = 0;
	while (i < env->len)
	{
		if (!ft_strncmp(str, entries[i], ft_strlen_member(str, '=')))
		{
			vec_remove_str(env, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	contains_plusequals(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] && i > 0 && str[i - 1] == '+')
		return (1);
	return (0);
}

int	add_new_from_plusequals(t_vec *env, char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strdup(str);
	if (!new)
		return (-1);
	while (new[i] != '+')
		i++;
	ft_memmove(&new[i], &new[i + 1], ft_strlen(&new[i + 1]));
	new[ft_strlen(str) - 1] = 0;
	if (vec_push(env, &new) < 0)
		return (-1);
	return (0);
}
