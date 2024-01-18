/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_strutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:25:27 by hpatsi            #+#    #+#             */
/*   Updated: 2023/11/21 14:09:18 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_i_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_i_putstr(char *s)
{
	int	written;

	written = 0;
	while (*s != 0)
	{
		written = ft_add_check_error(written, ft_i_putchar(*s));
		if (written == -1)
			return (-1);
		s++;
	}
	return (written);
}
