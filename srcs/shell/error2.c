/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:49:20 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/06 11:50:22 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_syntax_error(char c)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, &c, 1);
	write(2, "'\n", 2);
	return (-1);
}
