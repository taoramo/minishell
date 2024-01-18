/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:31:15 by hpatsi            #+#    #+#             */
/*   Updated: 2023/10/26 09:17:58 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	cc;
	char	*tab;

	cc = (char) c;
	tab = 0;
	while (*s != 0)
	{
		if (*s == cc)
			tab = (char *) s;
		s++;
	}
	if (cc == 0)
		tab = (char *) s;
	return (tab);
}
