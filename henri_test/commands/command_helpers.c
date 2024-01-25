/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:14:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/25 13:16:50 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	quote_length(char *str)
{
	char	*end_ptr;

	end_ptr = ft_memchr(str + 1, *str, ft_strlen(str + 1));
	if (end_ptr == 0)
		return (-1);
	return (end_ptr - str);
}