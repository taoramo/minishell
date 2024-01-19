/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:55:07 by hpatsi            #+#    #+#             */
/*   Updated: 2023/10/31 11:01:51 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_substr_match(const char *str, const char *substr)
{
	while (*substr != 0)
	{
		if (*str != *substr)
			return (0);
		str++;
		substr++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *) haystack);
	i = 0;
	while (i < len && haystack[i] != 0)
	{
		if (i > len - needle_len || len < needle_len)
			break ;
		if (check_substr_match(&haystack[i], needle))
			return ((char *) &haystack[i]);
		i++;
	}
	return (0);
}
