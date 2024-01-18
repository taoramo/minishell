/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:02:31 by hpatsi            #+#    #+#             */
/*   Updated: 2023/10/31 10:53:28 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapped;
	unsigned int	i;

	if (s == 0)
		return (0);
	mapped = malloc(ft_strlen(s) + 1);
	if (mapped == 0)
		return (0);
	i = 0;
	while (s[i] != 0)
	{
		mapped[i] = f(i, s[i]);
		i++;
	}
	mapped[i] = 0;
	return (mapped);
}
