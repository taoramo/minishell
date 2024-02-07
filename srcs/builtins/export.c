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

	str = ft_strdup(*(char **)vec_get(argv, 1));
	if (!str)
	{
		ft_putstr_fd("minishell: export: failed to allocate memory\n", 2);
		return (-1);
	}
	if (!contains_equals(str) && env_entry_exists(str, env))
		return (0);
	else
	{
		if (vec_push(env, str) < 0)
		{
			ft_putstr_fd("minishell: export: failed to allocate memory\n", 2);
			return (-1);
		}
	}
	if (contains_equals(str) && env_entry_exists(str, env))
		remove_entry(str, env);
	return (0);
}

int	ft_export(t_vec *argv, t_vec *env)
{
	char	**arguments;
	char	**environment;
	size_t	i;
	int		j;

	arguments = (char **)argv->memory;
	environment = (char **)env->memory;
	if (arguments[1] == 0)
	{
		i = 0;
		while (i < env->len)
		{
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
			i++;
		}
		return (0);
	}
	else
		return (export_variable(argv, env));
}
