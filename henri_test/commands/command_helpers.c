/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:14:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/29 10:51:33 by hpatsi           ###   ########.fr       */
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

void	print_string_vec(void	*param)
{
	char	*str;

	str = *(char **) param;
	ft_printf("[%s]", str);
}

void	print_redirects_vec(void *param)
{
	t_redirect	redirect;

	redirect = *(t_redirect *) param;
	ft_printf("redirecting %d to %d\n", redirect.origial_fd, redirect.new_fd);
}