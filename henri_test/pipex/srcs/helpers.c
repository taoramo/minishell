/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:17:11 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/03 12:05:10 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strsfree(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

int	free_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i] != 0)
	{
		ft_strsfree(commands[i]);
		i++;
	}
	free(commands);
	return (0);
}

int	count_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i] != 0)
		i++;
	return (i);
}

char	**strs_add_str(char **strs, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strs[i] != 0)
	{
		tmp = ft_strjoin(strs[i], str);
		if (tmp == 0)
		{
			ft_strsfree(strs);
			return (0);
		}
		free(strs[i]);
		strs[i] = tmp;
		i++;
	}
	return (strs);
}
