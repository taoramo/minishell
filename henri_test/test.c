/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:22:53 by hpatsi            #+#    #+#             */
/*   Updated: 2024/01/29 14:50:56 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	test_pipex(void)
{
	int		exit_code;

	ft_printf("TESTING PIPEX\n\n");
	exit_code = run_command("/bin/cat < infile > outfile | /usr/bin/wc \"-l\"");
	exit_code = run_command("cat /dev/random | head -1");
	return (exit_code);
}

int	test_commmands(void)
{
	int	process_id;
	int	ret;
	
	ft_printf("TESTING COMMANDS\n\n");
	process_id = run_command("cat \"infile\"");
	waitpid(process_id, &ret, 0);
	process_id = run_command("/bin/cat	\"infile\"");
	waitpid(process_id, &ret, 0);
	process_id = run_command("/bin/echo \"hello \" amazing \" > tmp/outfile \'wow\' \" \'$?\' \"    a\"");
	waitpid(process_id, &ret, 0);
	process_id = run_command("/usr/bin/awk \'BEGIN { for(i=1;i<=5;i++) print \"10 x\", i, \"is\",10*i; }\'");
	waitpid(process_id, &ret, 0);
	process_id = run_command("cat infile > outfile");
	waitpid(process_id, &ret, 0);
	process_id = run_command("cat infile");
	waitpid(process_id, &ret, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("give one arg with a command (or 'pipex' or 'commands' for tests)\n");
		return (1);
	}
	if (ft_strncmp(argv[1], "pipex", 6) == 0)
		return (test_pipex());
	if (ft_strncmp(argv[1], "commands", 9) == 0)
		return (test_commmands());
	run_command(argv[1]);
}
