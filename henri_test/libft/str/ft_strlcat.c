/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:13:31 by hpatsi            #+#    #+#             */
/*   Updated: 2023/10/30 09:14:14 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst != 0 && dst[i] != 0 && i < dstsize)
	{
		i++;
	}
	j = 0;
	while (src[j] != 0)
	{
		if (i + j < dstsize - 1 && dstsize != 0)
			dst[i + j] = src[j];
		if (i + j == dstsize - 1 && dstsize != 0)
			dst[i + j] = 0;
		j++;
	}
	if (i + j <= dstsize - 1 && dstsize != 0)
		dst[i + j] = 0;
	return (i + j);
}
