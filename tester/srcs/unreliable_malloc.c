/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unreliable_malloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:39:24 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/20 14:41:20 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/unreliable_malloc.h"

void	*unreliable_malloc(size_t size)
{
	static int	malloc_count;
	static int	fail_index = 1;

	malloc_count += 1;
	if (malloc_count == fail_index)
	{
		return (0);
	}
	return (malloc(size));
}
