/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:37:26 by hpatsi            #+#    #+#             */
/*   Updated: 2023/10/26 10:46:40 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*ucs1;
	const unsigned char	*ucs2;
	size_t				i;

	ucs1 = (const unsigned char *) s1;
	ucs2 = (const unsigned char *) s2;
	i = 0;
	while ((ucs1[i] != 0 || ucs2[i] != 0) && i < n)
	{
		if (ucs1[i] != ucs2[i])
			return (ucs1[i] - ucs2[i]);
		i++;
	}
	return (0);
}
