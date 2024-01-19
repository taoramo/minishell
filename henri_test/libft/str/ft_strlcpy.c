/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:10:07 by hpatsi            #+#    #+#             */
/*   Updated: 2023/10/26 10:51:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] != 0)
	{
		if (i < dstsize - 1 && dstsize != 0)
			dst[i] = src[i];
		if (i == dstsize - 1 && dstsize != 0)
			dst[i] = 0;
		i++;
	}
	if (i <= dstsize - 1 && dstsize != 0)
		dst[i] = 0;
	return (i);
}
