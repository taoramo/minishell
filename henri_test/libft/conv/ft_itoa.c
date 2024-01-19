/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:30:14 by hpatsi            #+#    #+#             */
/*   Updated: 2023/10/27 14:55:53 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	size;

	size = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		size++;
	}
	if (n < 0)
		size++;
	return (size);
}

static int	ten_to_power(int pow)
{
	int	num;

	num = 1;
	while (pow > 0)
	{
		num *= 10;
		pow--;
	}
	return (num);
}

static void	add_numbers(int n, char *str, int size, int i)
{
	while (i < size)
	{
		str[i] = (n / ten_to_power(size - 1 - i)) + '0';
		n %= ten_to_power(size - 1 - i);
		i++;
	}
	str[i] = 0;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	size = get_size(n);
	str = malloc(size + 1);
	if (str == 0)
		return (0);
	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		i++;
	}
	add_numbers(n, str, size, i);
	return (str);
}
