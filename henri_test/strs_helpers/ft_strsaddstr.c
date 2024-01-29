/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsaddstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:03:37 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/29 13:41:22 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsaddstr(char **strs, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strs[i] != 0)
	{
		tmp = ft_strjoin(strs[i], str);
		if (tmp == 0)
			return (0);
		free(strs[i]);
		strs[i] = tmp;
		i++;
	}
	return (strs);
}
