/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:22:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/24 16:27:48 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "strs_helpers.h"

char	**strs_add_str(char **strs, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (strs[i] != 0)
	{
		tmp = ft_strjoin(strs[i], str);
		if (tmp == 0)
			return (0);
		free(strs[i]);
		strs[i] = tmp;
		i++;
	}
	return (strs);
}

char	**get_paths(char *envp[])
{
	char	*path_str;
	char	**paths;

	while (*envp != 0)
	{
		if (ft_strncmp(*envp, "PATH", 4) == 0)
		{
			path_str = ft_substr(*envp, 5, ft_strlen(*envp) - 5);
			if (path_str == 0)
				return (0);
			paths = ft_split(path_str, ':');
			free(path_str);
			if (paths == 0)
				return (0);
			return (strs_add_str(paths, "/"));
		}
		envp++;
	}
	return (0);
}

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

int	test_commmands(void)
{
	int	process_id;
	int	ret;
	
	process_id = run_command(0, 1, split_command("/bin/cat \"infile\""));
	waitpid(process_id, &ret, 0);
	process_id = run_command(0, 1, split_command("/bin/cat	\"infile\""));
	waitpid(process_id, &ret, 0);
	process_id = run_command(0, 1, split_command("/bin/echo \"hello \" amazing \" > tmp/outfile \'wow\' \" \'$?\' \"    a\""));
	waitpid(process_id, &ret, 0);
	process_id = run_command(0, 1, split_command("/usr/bin/awk \'BEGIN { for(i=1;i<=5;i++) print \"10 x\", i, \"is\",10*i; }\'"));
	waitpid(process_id, &ret, 0);
	return (0);
}

int	main(int argc, char **argv, char *envp[])
{
	char	**command_argv;
	char	**paths;

	if (argc < 2)
	{
		ft_printf("give at least one arg");
		return (1);
	}
	if (ft_strncmp(argv[1], "pipex", 6) == 0)
		return (test_pipex());
	if (ft_strncmp(argv[1], "commands", 9) == 0)
		return (test_commmands());
	command_argv = &argv[1];
	paths = get_paths(envp);
	command_argv[0] = add_path(command_argv[0], paths);
	run_command(0, 1, command_argv);
	return (0);
}