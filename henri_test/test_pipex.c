/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:22:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 10:19:33 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_command(char *str);

// void	ft_strsfree(char **strs)
// {
// 	int	i;

// 	i = 0;
// 	while (strs[i] != 0)
// 	{
// 		free(strs[i]);
// 		i++;
// 	}
// 	free(strs);
// }

void	print_command(char **command)
{
	int	i;

	i = 0;
	while (command[i] != 0)
	{
		ft_printf("[%s]", command[i]);
		i++;
	}
	ft_printf("\n");
}

int	main(void)
{
	// char	***commands;
	char	**command1;
	char	**command2;

	// int		file_fds[2];
	// int		exit_code;

	ft_printf("Splitting:\n");
	command1 = split_command("echo hi ok \"hello\" hi \"hello \'world\' \"");
	command2 = split_command("/usr/bin/wc -l");

	ft_printf("Printing:\n");
	print_command(command1);
	print_command(command2);

	// commands = ft_calloc(3, sizeof(char **));
	// commands[0] = command1;
	// commands[1] = command2;

	// file_fds[0] = open("infile", O_RDONLY);
	// file_fds[1] = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	// if (file_fds[0] == -1)
	// 	perror("infile");
	// if (file_fds[1] == -1)
	// 	perror("outfile");

	// ft_printf("Command count: %d\n", count_commands(commands));
	// ft_printf("Commands:\n");
	// print_commands_fd(commands, 1);
	
	// ft_printf("Running pipex\n");
	// exit_code = pipex(commands, file_fds);

	// ft_strsfree(command1);
	// ft_strsfree(command2);
	// free(commands);

	// return (exit_code);
}