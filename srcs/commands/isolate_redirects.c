/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:00:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/16 09:25:13 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	substr_isdigit(char *str, int len)
{
	while (*str != 0 && len > 0)
	{
		if (!ft_isdigit(*str))
			return (0);
		len--;
		str++;
	}
	return (1);
}

int	remove_invalid_prefix(t_vec *strs, char *str, size_t *i)
{
	int		n;
	char	*substr;

	n = 0;
	while (str[n] != 0 && str[n] != '>' && str[n] != '<')
		n++;
	if (!substr_isdigit(str, n))
	{
		substr = ft_substr(str, 0, n);
		if (substr == 0)
			return (-1);
		if (vec_insert(strs, &substr, *i) == -1)
			return (-1);
		*i += 1;
		str = &str[n];
	}
	else
		n = 0;
	return (n);
}

int	insert_redirect(t_vec *strs, char *str, int pre, size_t *i)
{
	int		r;
	int		f;
	char	*substr;

	r = 1;
	if (!ft_strncmp(&str[pre], ">>", 2) || !ft_strncmp(&str[pre], "<<", 2))
		r = 2;
	f = ft_strlen(&str[pre + r]);
	if (f > 0)
	{
		substr = ft_strdup(str);
		vec_insert(strs, &substr, *i);
	}
	else
	{
		substr = ft_strjoin(str, *(char **)vec_get(strs, *i));
		vec_remove(strs, *i);
		vec_insert(strs, &substr, *i);
	}
	return (1);
}

int	format_redirect(t_vec *strs, char *str, size_t *i)
{
	int	removed;
	int	prefix;

	vec_remove(strs, *i);
	removed = remove_invalid_prefix(strs, str, i);
	if (removed == -1)
		return (-1);
	str = &str[removed];
	prefix = 0;
	while (str[prefix] != 0 && str[prefix] != '>' && str[prefix] != '<')
		prefix++;
	if (insert_redirect(strs, str, prefix, i) == -1)
		return (-1);
	free(str);
	return (1);
}

int	isolate_redirects(t_vec *strs)
{
	size_t	i;
	char	*str;

	i = 0;
	while (i < strs->len)
	{
		str = *(char **)vec_get(strs, i);
		if ((ft_strchr(str, '>') 
				&& !ft_is_inside(str, ft_strchr(str, '>') - str, '"')
				&& !ft_is_inside(str, ft_strchr(str, '>') - str, 39)) 
				|| (ft_strchr(str, '<')
				&& !ft_is_inside(str, ft_strchr(str, '<') - str, '"')
				&& !ft_is_inside(str, ft_strchr(str, '<') - str, 39)))
			if (format_redirect(strs, str, &i) == -1)
				return (-1);
		i++;
	}
	return (1);
}
