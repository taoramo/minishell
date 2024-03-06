/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:00:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/23 09:26:40 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

void	close_redirect_files(void *param)
{
	int	fd;

	fd = *(int *) param;
	if (fd <= 2)
		return ;
	close(fd);
}

int	remove_invalid_prefix(t_vec *strs, char *str, size_t *i, int skip)
{
	int		n;
	int		is_digit;

	is_digit = 1;
	n = skip;
	while ((str[n] != 0 && str[n] != '>' && str[n] != '<')
		|| ft_is_inside_any(str, n))
	{
		if (!ft_isdigit(str[n]))
			is_digit = 0;
		n++;
	}
	if (!is_digit)
	{
		if (vec_insert_substr(strs, *i, str, n) == -1)
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
		if (vec_insert_substr(strs, *i, str, ft_strlen(str)) == -1)
			return (-1);
	}
	else
	{
		substr = ft_strjoin(str, *(char **)vec_get(strs, *i));
		if (substr == 0)
			return (-1);
		if (vec_remove_insert_str(strs, *i, substr) == -1)
		{
			free(substr);
			return (-1);
		}
	}
	return (1);
}

int	format_redirect(t_vec *strs, char *str, size_t *i, int skip)
{
	int	rem;
	int	pre;
	int	ret;

	rem = remove_invalid_prefix(strs, str, i, skip);
	if (rem == -1)
	{
		free(str);
		return (-1);
	}
	pre = 0;
	while (str[rem + pre] != 0 && str[rem + pre] != '>'
		&& str[rem + pre] != '<')
		pre++;
	ret = insert_redirect(strs, &str[rem], pre, i);
	free(str);
	return (ret);
}

int	isolate_redirects(t_vec *strs)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (i < strs->len)
	{
		j = 0;
		str = *(char **)vec_get(strs, i);
		while (contains_unquoted(str, j, '>') || contains_unquoted(str, j, '<'))
		{
			if (vec_remove(strs, i) == -1)
				return (-1);
			if (format_redirect(strs, str, &i, j) == -1)
				return (-1);
			str = *(char **)vec_get(strs, i);
			j = 1;
			if (str[1] != 0 && (str[1] == '<' || str[1] == '>'))
				j = 2;
		}
		i++;
	}
	return (1);
}
