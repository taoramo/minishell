/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 09:13:49 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/25 19:50:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

// int	set_file(t_command command, char *filename)
// {
// 	unquoted_strcpy(filename, str);
// 	if (index == 0)
// 		*fd = open(filename, O_RDONLY);
// 	if (index == 1)
// 		*fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	if (*fd == -1)
// 		perror(filename);
// 	return (*fd);
// 	return (1);
// }

int	is_redirect(char *str)
{
	ft_printf("%s\n", str);
	if (*str == '>' || *str == '<' || !ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (1);
	return (0);
}

int	extract_files(t_command *command)
{	
	char	**strs;
	size_t	i;

	strs = *(char ***) &command->argv;
	i = 0;
	while (i < command->argv.len)
	{
		if(is_redirect(strs[i]))
		{
			vec_remove(&command->argv, i);
			set_file(command, strs[i]);
			i--;
		}
		i++;
	}
	return (1);
}