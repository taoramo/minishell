/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:00:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/16 10:39:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	remove_invalid_prefix(t_vec *strs, char *str, size_t *i)
{
	int		n;
	char	*substr;
	int		is_digit;

	is_digit = 1;
	n = 0;
	while ((str[n] != 0 && str[n] != '>' && str[n] != '<')
		|| ft_is_inside_any(str, n))
	{
		if (!ft_isdigit(str[n]))
			is_digit = 0;
		n++;
	}
	if (!is_digit)
	{
		substr = ft_substr(str, 0, n);
		if (substr == 0)
			return (-1);
		if (vec_insert(strs, &substr, *i) == -1)
			return (-1);
		*i += 1;
		str = &str[n];
		return (n);
	}
	return (0);
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
		if (substr == 0)
			return (-1);
		if (vec_insert(strs, &substr, *i) == -1)
			return (-1);
	}
	else
	{
		substr = ft_strjoin(str, *(char **)vec_get(strs, *i));
		if (substr == 0)
			return (-1);
		if (vec_remove(strs, *i) == -1 || vec_insert(strs, &substr, *i) == -1)
			return (-1);
	}
	return (1);
}

int	split_multiple_redirects(t_vec *strs, char *str, size_t *i)
{
	int		s;
	int		e;
	char	*substr;

	s = 0;
	e = 0;
	if (vec_remove(strs, *i) == -1)
		return (-1);
	while (str[e] != 0)
	{
		while (str[e] == '<' || str[e] == '>')
			e++;
		while ((str[e] != 0 && str[e] != '<' && str[e] != '>')
			|| ft_is_inside_any(str, e))
			e++;
		substr = ft_substr(str, s, e - s);
		if (substr == 0)
			return (-1);
		if (vec_insert(strs, &substr, *i) == -1)
			return (-1);
		s = e;
	}
	free(str);
	return (1);
}

int	format_redirect(t_vec *strs, char *str, size_t *i)
{
	int	rem;
	int	pre;

	if (vec_remove(strs, *i) == -1)
		return (-1);
	rem = remove_invalid_prefix(strs, str, i);
	if (rem == -1)
		return (-1);
	pre = 0;
	while (str[rem + pre] != 0 && str[rem + pre] != '>'
		&& str[rem + pre] != '<')
		pre++;
	if (insert_redirect(strs, &str[rem], pre, i) == -1)
		return (-1);
	free(str);
	if (split_multiple_redirects(strs, *(char **)vec_get(strs, *i), i) == -1)
		return (-1);
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
		if (contains_unquoted(str, '>') || contains_unquoted(str, '<'))
		{
			if (format_redirect(strs, str, &i) == -1)
				return (-1);
		}
		i++;
	}
	return (1);
}
