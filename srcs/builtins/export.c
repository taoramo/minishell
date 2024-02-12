/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:31:29 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 16:31:38 by toramo           ###   ########.fr       */
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
		if (!ft_strncmp(str, entries[i], ft_strlen_member(str, '=')))
			return (1);
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
			vec_remove(env, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export_variable(t_vec *argv, t_vec *env)
{
	char	*str;
	char	**strs;

	strs = (char **)argv->memory;
	str = ft_strdup(strs[1]);
	if (!str)
	{
		ft_putstr_fd("minishell: export: failed to allocate memory\n", 2);
		return (1);
	}
	if (contains_equals(str) && env_entry_exists(str, env))
		remove_entry(str, env);
	if (!contains_equals(str) && env_entry_exists(str, env))
		return (0);
	else
	{
		if (vec_push(env, &str) < 0)
		{
			ft_putstr_fd("minishell: export: failed to allocate memory\n", 2);
			return (1);
		}
	}
	return (0);
}

void	print_env(char **environment, size_t i)
{
	size_t	j;

	ft_putstr_fd("declare -x ", 1);
	j = 0;
	if (contains_equals(environment[i]))
	{
		while (environment[i][j] != '=')
		{
			write(1, &environment[i][j], 1);
			j++;
		}
		write(1, "\"", 1);
		while (environment[i][j])
		{
			write(1, &environment[i][j], 1);
			j++;
		}
		write(1, "\"\n", 2);
	}
	else
		ft_putstr_fd(environment[i], 1);
}

int	ft_export(t_vec *argv, t_vec *env)
{
	char	**arguments;
	char	**environment;
	t_vec	sorted;
	size_t	i;

	arguments = (char **)argv->memory;
	if (arguments[1] == 0)
	{
		vec_new(&sorted, env->len, env->elem_size);
		vec_copy(&sorted, env);
		vec_sort(&sorted, vec_sort_strncmp);
		environment = (char **)sorted.memory;
		i = 0;
		while (i < env->len)
		{
			print_env(environment, i);
			i++;
		}
		vec_free(&sorted);
		vec_clear(&sorted);
		return (0);
	}
	else
		return (export_variable(argv, env));
}
