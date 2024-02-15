/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:52:19 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/15 18:35:14 by hpatsi           ###   ########.fr       */
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

int	format_redirect(t_vec *strs, char *str, size_t *i)
{
	int		n;
	int		r;
	int		f;
	char	*substr;

	ft_printf("redstr = %s\n", str);

	n = 0;
	while (str[n] != 0 && str[n] != '>' && str[n] != '<')
		n++;
	r = 1;
	if (!ft_strncmp(&str[n], ">>", 2) || !ft_strncmp(&str[n], "<<", 2))
		r = 2;
	f = ft_strlen(&str[n + r]);
	ft_printf("n = %d, r = %d, f = %d\n", n, r, f);

	vec_remove(strs, *i);

	if (n > 0 && !substr_isdigit(str, n))
	{
		substr = ft_substr(str, 0, n);
		vec_insert(strs, &substr, *i);
		*i += 1;
	}

	vec_iter(strs, vec_print_elem_str);
		

	return (1);	
}

int	join_redirects(t_vec *strs)
{
	size_t	i;
	char	*str;

	i = 0;
	while (i < strs->len)
	{
		str = *(char **)vec_get(strs, i);
		if (ft_strchr(str, '>') || ft_strchr(str, '<'))
			format_redirect(strs, str, &i);
		i++;
	}

	return (1);
}

int	quote_length(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != str[0])
		i++;
	return (i);
}

int	add_str(t_vec *strs, char *str, int i)
{
	char	*substr;
	
	substr = ft_substr(str, 0, i);
	if (substr == 0)
		return (-1);
	if (vec_push(strs, &substr) == -1)
		return (-1);
	ft_printf("substr = %s\n", substr);
	return (0);
}

int	split_command(t_vec *strs, char *str)
{
	int	i;
	
	while (ft_isspace(*str))
		str++;
	i = 0;
	while (str[i] != 0)
	{
		i++;
		if (str[i] == '\"' || str[i] == '\'')
			i += quote_length(&str[i]);
		if (str[i] == 0 || ft_isspace(str[i]))
		{
			if (add_str(strs, str, i) == -1)
			{
				free_split_vec(strs);
				return (-1);
			}
			if (str[i] == 0)
				break ;
			str = &str[i] + 1;
			i = 0;
		}
	}
	join_redirects(strs);
	return (1);
}
