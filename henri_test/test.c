/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:22:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/26 14:43:35 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

// int	test_pipex(void)
// {
// 	char	***commands;
// 	char	**command1;
// 	char	**command2;
// 	int		file_fds[2];
// 	int		exit_code;

// 	ft_printf("TESTING PIPEX\n");
// 	ft_printf("Splitting commands\n");
// 	command1 = split_command("/bin/cat");
// 	command2 = split_command("/usr/bin/wc \"-l\"");
// 	ft_printf("Printing commands\n");
// 	ft_strsprint(command1);
// 	ft_strsprint(command2);
// 	commands = ft_calloc(3, sizeof(char **));
// 	commands[0] = command1;
// 	commands[1] = command2;
// 	file_fds[0] = open("infile", O_RDONLY);
// 	file_fds[1] = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	if (file_fds[0] == -1)
// 		perror("infile");
// 	if (file_fds[1] == -1)
// 		perror("outfile");
// 	ft_printf("Running pipex\n");
// 	exit_code = pipex(commands, file_fds);
// 	ft_strsfree(command1);
// 	ft_strsfree(command2);
// 	free(commands);
// 	return (exit_code);
// }

// int	test_commmands(void)
// {
// 	int	process_id;
// 	int	ret;
// 	int	file_fds[2];
	
// 	ft_printf("TESTING COMMANDS");
// 	file_fds[0] = 0;
// 	file_fds[1] = 1;
// 	process_id = run_command(file_fds, split_command("/bin/cat \"infile\""));
// 	waitpid(process_id, &ret, 0);
// 	process_id = run_command(file_fds, split_command("/bin/cat	\"infile\""));
// 	waitpid(process_id, &ret, 0);
// 	process_id = run_command(file_fds, split_command("/bin/echo \"hello \" amazing \" > tmp/outfile \'wow\' \" \'$?\' \"    a\""));
// 	waitpid(process_id, &ret, 0);
// 	process_id = run_command(file_fds, split_command("/usr/bin/awk \'BEGIN { for(i=1;i<=5;i++) print \"10 x\", i, \"is\",10*i; }\'"));
// 	waitpid(process_id, &ret, 0);
// 	return (0);
// }

void	print_string_vec(void	*param)
{
	char	*str;

	str = *(char **) param;
	ft_printf("[%s]", str);
}

void	print_redirects_vec(void *param)
{
	t_redirect	redirect;

	redirect = *(t_redirect *) param;
	ft_printf("redirecting %d to %d\n", redirect.origial_fd, redirect.new_fd);
}

int	main(int argc, char **argv)
{
	t_command	command;

	if (argc != 2)
	{
		ft_printf("give one arg with a command (or 'pipex' or 'commands' for tests)\n");
		return (1);
	}
	// if (ft_strncmp(argv[1], "pipex", 6) == 0)
	// 	return (test_pipex());
	// if (ft_strncmp(argv[1], "commands", 9) == 0)
	// 	return (test_commmands());

	vec_new(&command.argv, 0, sizeof(char *));
	ft_printf("\nSplit:\n");
	if (split_command(&command.argv, argv[1]) == -1)
		return (1);
	vec_iter(&command.argv, print_string_vec);
	ft_printf("\n\n");

	vec_new(&command.redirects, 0, sizeof(t_redirect));
	ft_printf("Extract files:\n");
	if (extract_files(&command) == -1)
		return (1);
	vec_iter(&command.redirects, print_redirects_vec);
	vec_iter(&command.argv, print_string_vec);
	ft_printf("\n\n");
	
	// if not built in command
	ft_printf("Adding path:\n");
	add_path((char **) vec_get(&command.argv, 0));
	vec_iter(&command.argv, print_string_vec);
	ft_printf("\n\n");

	ft_printf("Running command:\n");
	if (run_command(command) == -1)
		return (-1);
	
	// if built in command
	
	// return (0);
}