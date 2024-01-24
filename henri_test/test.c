/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:22:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 11:38:48 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "strs_helpers.h"

char	**split_command(char *str);
int		run_command(int file_fds[], char **command);

int	test_pipex(void)
{
	char	***commands;
	char	**command1;
	char	**command2;
	int		file_fds[2];
	int		exit_code;

	ft_printf("TESTING PIPEX\n");
	ft_printf("Splitting commands\n");
	command1 = split_command("/bin/cat");
	command2 = split_command("/usr/bin/wc \"-l\"");
	ft_printf("Printing commands\n");
	ft_strsprint(command1);
	ft_strsprint(command2);
	commands = ft_calloc(3, sizeof(char **));
	commands[0] = command1;
	commands[1] = command2;
	file_fds[0] = open("infile", O_RDONLY);
	file_fds[1] = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file_fds[0] == -1)
		perror("infile");
	if (file_fds[1] == -1)
		perror("outfile");
	ft_printf("Running pipex\n");
	exit_code = pipex(commands, file_fds);
	ft_strsfree(command1);
	ft_strsfree(command2);
	free(commands);
	return (exit_code);
}

int	main(void)
{
	//test_pipex();

	char	**command;
	int		file_fds[2];
	
	command = split_command("/bin/cat infile");
	file_fds[0] = 0;
	file_fds[1] = 1;
	run_command(file_fds, command);
}