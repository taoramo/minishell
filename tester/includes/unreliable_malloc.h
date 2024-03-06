/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unreliable_malloc.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:07:43 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/20 14:41:39 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNRELIABLE_MALLOC_H
# define UNRELIABLE_MALLOC_H

# include "unistd.h"

# define malloc(x) unreliable_malloc(x)

void	*unreliable_malloc(size_t size);

#endif