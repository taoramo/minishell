/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:01:12 by toramo            #+#    #+#             */
/*   Updated: 2024/02/16 14:01:13 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words_pipe(const char *str, char sep)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (str[i] != 0)
	{
		while (str[i] == sep && !ft_is_inside(str, i, '"')
			&& !ft_is_inside(str, i, 39))
		{
			i++;
		}
		if (str[i] != 0)
			c++;
		while ((!(str[i] == sep && !ft_is_inside(str, i, '"')
					&& !ft_is_inside(str, i, 39))) && str[i] != 0)
		{
			i++;
		}
	}
	return (c);
}

int	ft_strlen_pipe(const char *str, char sep)
{
	int	n;

	n = 0;
	if (str[0] != 0)
	{
		while (str[n] != 0 && !(str[n] == sep
				&& !ft_is_inside(str, n, '"') && !ft_is_inside(str, n, 39)))
		{
			n++;
		}
	}
	return (n);
}

char	**ft_split_pipe(const char *s, char c)
{
	int		i;
	int		j;
	char	**strs;

	j = 0;
	i = 0;
	strs = (char **)malloc(sizeof(char *) * (count_words_pipe(s, c) + 1));
	if (strs == 0)
		return (0);
	while (i < count_words_pipe(s, c))
	{
		if (s[j] == c && !ft_is_inside(s, j, '"') && !ft_is_inside(s, j, 39))
			j++;
		else
		{
			strs[i] = malloc(sizeof(char) * (ft_strlen_pipe(&s[j], c) + 1));
			if (strs[i] == 0)
				return (ft_free_arr(strs, i));
			ft_strlcpy(strs[i], &s[j], (ft_strlen_pipe(&s[j], c) + 1));
			j = j + ft_strlen_pipe(&s[j], c);
			i++;
		}
	}
	strs[i] = 0;
	return (strs);
}
