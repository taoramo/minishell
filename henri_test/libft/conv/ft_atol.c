/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 21:27:44 by hpatsi            #+#    #+#             */
/*   Updated: 2023/11/28 12:41:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	num;
	int		neg;

	while (ft_isspace(*str))
		str++;
	neg = 1;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	num = 0;
	while (*str != 0 && ft_isdigit(*str))
	{
		num *= 10;
		num += (*str - '0');
		str++;
	}
	return (num * neg);
}
