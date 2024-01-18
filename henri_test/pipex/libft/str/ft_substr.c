/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:51:44 by hpatsi            #+#    #+#             */
/*   Updated: 2023/11/10 14:24:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;

	if (s == 0)
		return (0);
	slen = ft_strlen(s);
	if (start > slen)
		start = slen;
	if (len > slen - start)
		len = slen - start;
	substr = malloc(len + 1);
	if (substr == 0)
		return (0);
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}
