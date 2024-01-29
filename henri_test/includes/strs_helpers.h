/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strs_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:40:57 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/29 13:40:18 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRS_HELPERS_H
# define STRS_HELPERS_H

# include "libft.h"

void	ft_strsfree(char **strs);
void	ft_strsprint(char **strs);
char	**ft_strsaddstr(char **strs, char *str);

#endif
