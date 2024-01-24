/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipex_vec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:24:11 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/19 15:24:11 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	split_command(t_vec *strs, char *str);

void	print_commands(void *src)
{
	char	**command;
	int		i;

	command = *((char ***) src);
	i = 0;
	while (command[i] != 0)
	{
		ft_printf("[%s] ", command[i]);
		i++;
	}
	ft_printf("\n");
}

void print_command(void *src)
{
	ft_printf("[%s]", *(char **)src);
}

int	main(void)
{
	// t_vec	commands;

	t_vec	command1;
	t_vec	command2;

	vec_new(&command1, 1, sizeof(char *));
	vec_new(&command2, 1, sizeof(char *));

	ft_printf("Splitting:\n");
	split_command(&command1, "echo hi ok \"hello\" hi \"hello \'world\' \"");
	split_command(&command2, "/usr/bin/wc -l");

	ft_printf("Printing:\n");
	vec_iter(&command1, print_command);
	ft_printf("\n");
	vec_iter(&command2, print_command);
	ft_printf("\n");

	//ft_printf("%s\n", *(char **)vec_get(&command1, 0));

	// vec_new(&commands, 2, sizeof(char **));
	// vec_push(&commands, &command1);
	// vec_push(&commands, &command2);

	// ft_printf("commands:\n");
	// vec_iter(&commands, &print_vec_commands);
}