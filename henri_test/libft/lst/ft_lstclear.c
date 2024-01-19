/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:26:50 by hpatsi            #+#    #+#             */
/*   Updated: 2023/11/02 12:30:23 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*next;

	if (lst == 0)
		return ;
	node = *lst;
	while (node != 0)
	{
		next = node->next;
		ft_lstdelone(node, del);
		node = next;
	}
	*lst = 0;
}
