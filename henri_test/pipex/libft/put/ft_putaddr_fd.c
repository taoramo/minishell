/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:20:20 by hpatsi            #+#    #+#             */
/*   Updated: 2023/12/01 10:07:17 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putlonghex_fd(unsigned long n, int fd)
{
	if (n >= 16)
		putlonghex_fd(n / 16, fd);
	n = (n % 16) + '0';
	if (n > '9')
		n += ('a' - '9' - 1);
	ft_putchar_fd(n, fd);
}

void	ft_putaddr_fd(void *ptr, int fd)
{
	ft_putstr_fd("0x", 1);
	putlonghex_fd((unsigned long) ptr, fd);
}
