/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:45:48 by hpatsi            #+#    #+#             */
/*   Updated: 2023/11/21 15:27:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	get_str_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			if (i != 0 && s[i - 1] != c && s[i + 1] != 0)
				count++;
		}
		i++;
	}
	if (i != 0 && s[i - 1] != c)
		count++;
	return (count);
}

static char const	*get_next_split(char const *s, char c)
{
	while (*s != 0)
	{
		if (*s == c)
			break ;
		s++;
	}
	return (s);
}

static void	free_all(char **strs, size_t *iptr)
{
	size_t	i;

	i = 0;
	while (i < *iptr)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	add_to_strs(char **strs, char const *s, size_t len, size_t *iptr)
{
	if (len == 0)
		return (1);
	strs[*iptr] = ft_substr(s, 0, len);
	if (strs[*iptr] == 0)
		return (0);
	*iptr += 1;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**strs;
	size_t		i;
	const char	*tab;

	if (s == 0)
		return (0);
	strs = malloc((get_str_count(s, c) + 1) * sizeof(char *));
	if (strs == 0)
		return (0);
	i = 0;
	while (*s != 0)
	{
		tab = get_next_split(s, c);
		if (add_to_strs(strs, s, tab - s, &i) == 0)
		{
			free_all(strs, &i);
			return (0);
		}
		if (*tab != 0)
			tab++;
		s = tab;
	}
	strs[i] = 0;
	return (strs);
}
