/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:31:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/09 13:25:46 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(t_vec *str_vec, size_t start)
{
	size_t	i;
	char	c;

	i = 0;
	start++;
	while (start + i < str_vec->len)
	{
		c = *(char *)vec_get(str_vec, start + i);
		if (c == '\'' || c == '\"' || c == '$')
			return (ft_substr((char *) str_vec->memory, start, i));
		if (c == '*' && !ft_is_inside((char *) str_vec->memory, start + i, '\'') &&
				!ft_is_inside((char *) str_vec->memory, start + i, '\"'))
			return (ft_substr((char *) str_vec->memory, start, i));
		i++;
	}
	return (ft_substr((char *) str_vec->memory, start, i));
}

int	expand_substr_env(t_vec *str_vec, size_t i, t_vec *env)
{
	char	*env_name;
	char	*env_expanded;
	size_t	j;

	env_name = get_env_name(str_vec, i);
	if (env_name == 0)
		return (-1);
	env_expanded = ft_getenv(env_name, env);
	if (env_expanded == 0)
		env_expanded = ft_strdup("");
	j = 0;
	while (j < ft_strlen(env_name) + 1)
	{
		vec_remove(str_vec, i);
		j++;
	}
	j = 0;
	while (env_expanded[j] != 0)
	{
		vec_insert(str_vec, &env_expanded[j], i + j);
		j++;
	}
	free(env_name);
	free(env_expanded);
	return (1);
}

int	expand_str_envs(char	**str_ptr, t_vec *env)
{
	t_vec	str_vec;
	size_t	i;

	vec_from(&str_vec, *str_ptr, ft_strlen(*str_ptr), sizeof(char));
	i = 0;
	while (i < str_vec.len)
	{
		if (*(char *)vec_get(&str_vec, i) == '\'')
		{
			i++;
			while (i < str_vec.len && *(char *)vec_get(&str_vec, i) != '\'')
				i++;
		}
		if (*(char *)vec_get(&str_vec, i) == '$')
		{
			if (expand_substr_env(&str_vec, i, env) == -1)
				return (-1);
			continue ;
		}
		i++;
	}
	free(*str_ptr);
	vec_push(&str_vec, 0);
	*str_ptr = (char *) str_vec.memory;
	return (1);
}

int	expand_envs(t_vec *argv, t_vec *env)
{
	char	**str_ptr;
	size_t	i;

	i = 0;
	while(i < argv->len)
	{
		str_ptr = (char **)vec_get(argv, i);
		if (ft_strchr(*str_ptr, '$') != 0)
			expand_str_envs(str_ptr, env);
		i++;
	}
	return (1);
}
