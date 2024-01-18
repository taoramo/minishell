/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:10:02 by hpatsi            #+#    #+#             */
/*   Updated: 2023/11/14 15:10:02 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_i_strchr(const char *s, int c)
{
	char	cc;
	size_t	i;

	cc = (char) c;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == cc)
			return (i);
		i++;
	}
	if (cc == 0)
		return (i);
	return (-1);
}

char	*ft_strldup(const char *s1, size_t len)
{
	char	*dup;
	size_t	i;

	dup = malloc(len + 1);
	if (dup == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*ft_stradd(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == 0 || s2 == 0)
		return (0);
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new != 0)
	{
		i = 0;
		while (s1[i] != 0)
		{
			new[i] = s1[i];
			i++;
		}
		j = 0;
		while (s2[j] != 0)
		{
			new[i + j] = s2[j];
			j++;
		}
		new[i + j] = 0;
	}
	free(s1);
	return (new);
}
