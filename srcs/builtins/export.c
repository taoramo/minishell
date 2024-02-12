/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:31:29 by toramo            #+#    #+#             */
/*   Updated: 2024/02/12 13:14:21 by hpatsi           ###   ########.fr       */
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
	size_t	i;

	strs = (char **)argv->memory;
	i = 1;
	while (i < argv->len)
	{
		str = ft_strdup(strs[i]);
		if (!str)
			return (ft_error("minishell: export: failed to allocate memory"));
		if (!ft_isalpha(str[0]) && str[0] != '_')
			return (ft_error("minishell: export: not a valid identifier"));
		if (contains_equals(str) && env_entry_exists(str, env))
			remove_entry(str, env);
		if (!contains_equals(str) && env_entry_exists(str, env))
			return (0);
		else if (vec_push(env, &str) < 0)
			return (ft_error("minishell: \
				export: failed to allocate memory"));
		i++;
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
		write(1, "=", 1);
			j++;
		write(1, "\"", 1);
		while (environment[i][j])
		{
			write(1, &environment[i][j], 1);
			j++;
		}
		write(1, "\"\n", 2);
	}
	else
		ft_printf("%s\n", environment[i]);
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
