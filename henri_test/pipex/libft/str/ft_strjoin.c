/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:25:56 by hpatsi            #+#    #+#             */
/*   Updated: 2023/10/31 10:48:50 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	char	*tab;

	if (s1 == 0 || s2 == 0)
		return (0);
	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (joined == 0)
		return (0);
	tab = joined;
	while (*s1 != 0)
	{
		*joined = *s1;
		s1++;
		joined++;
	}
	while (*s2 != 0)
	{
		*joined = *s2;
		s2++;
		joined++;
	}
	*joined = 0;
	return (tab);
}
