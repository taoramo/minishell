/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:24:55 by hpatsi            #+#    #+#             */
/*   Updated: 2024/03/08 10:59:39 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

pid_t	execute_command(t_vec argv, t_vec *env)
{
	char	**strs;
	char	**envp;
	char	*nulterm;
	t_vec	sub_env;

	if (copy_split_vec(&sub_env, env) == -1)
		exit(1);
	nulterm = 0;
	if (vec_push(&argv, &nulterm) == -1)
		exit(1);
	if (vec_push(env, &nulterm) == -1)
		exit(1);
	strs = (char **) argv.memory;
	envp = (char **) env->memory;
	execve(strs[0], strs, envp);
	ft_putstr_fd("minishell: execve failed to run ", 2);
	ft_putstr_fd(strs[0], 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	apply_redirect(void	*param)
{
	t_redirect	redirect;

	redirect = *(t_redirect *) param;
	if (dup2(redirect.new_fd, redirect.origial_fd) == -1)
		perror("dup failed");
	close(redirect.new_fd);
}

int	run_single_command(t_command *command)
{
	command->process_id = fork();
	if (command->process_id < 0)
	{
		perror("fork failed");
		return (-1);
	}
	else if (command->process_id == 0)
	{
		vec_iter(&command->redirects, apply_redirect);
		execute_command(command->argv, command->env);
	}
	return (1);
}

int	free_run_command(t_command *command, int ret)
{
	vec_iter(&command->redirects, close_redirect_files);
	free_split_vec(&command->argv);
	vec_free(&command->redirects);
	return (ret);
}

int	run_command(char *str, t_envinfo envinfo)
{
	int			ret;
	t_command	command;

	if (contains_unquoted(str, 0, '|'))
		return (pipex(str, envinfo));
	ret = prepare_command(&command, str, envinfo, 0);
	if (ret != 0)
		return (free_run_command(&command, ret));
	if (command.argv.len == 0)
		return (ret);
	if (builtin_index(*(char **)vec_get(&command.argv, 0)) != -1)
	{
		ret = run_builtin(&command);
		return (free_run_command(&command, ret));
	}
	if (run_single_command(&command) == -1)
	{
		ret = 1;
		return (free_run_command(&command, ret));
	}
	free_run_command(&command, ret);
	waitpid(command.process_id, &ret, 0);
	return (WEXITSTATUS(ret));
}
