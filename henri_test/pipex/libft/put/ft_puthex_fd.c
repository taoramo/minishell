/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:08:32 by hpatsi            #+#    #+#             */
/*   Updated: 2023/11/06 10:58:52 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(unsigned int n, int use_capitals, int fd)
{
	int	dif;

	if (n >= 16)
		ft_puthex_fd(n / 16, use_capitals, fd);
	if (use_capitals)
		dif = ('A' - '9' - 1);
	else
		dif = ('a' - '9' - 1);
	n = (n % 16) + '0';
	if (n > '9')
		n += dif;
	ft_putchar_fd(n, fd);
}
