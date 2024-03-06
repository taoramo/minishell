/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:09:12 by toramo            #+#    #+#             */
/*   Updated: 2024/03/06 12:24:50 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_line(const char *line, int *last_return, t_vec *env)
{
	t_vec	cmd_lines;

	if (is_empty_line(line))
		*last_return = 0;
	else if (line[0] == '&' || line[0] == '|')
	{
		*last_return = 1;
		return (print_syntax_error(line[0]));
	}
	else if (check_parenthesis_count(line) < 0 || check_open_quotes(line) < 0
		|| check_consecutive_andor(line) < 0)
		*last_return = 1;
	else if (vec_new(&cmd_lines, 16, sizeof(char *)) < 0)
		return (ft_error("malloc error"));
	else if (make_cmd_line_groups(&cmd_lines, line, last_return, env) == -1)
		*last_return = 1;
	return (1);
}

int	copy_env(t_vec *env, char **environ)
{
	char		*temp;
	int			i;

	i = 0;
	if (vec_new(env, 64, sizeof(char *)) < 0)
		return (-1);
	while (environ[i])
	{
		temp = ft_strdup(environ[i]);
		if (!temp)
			return (free_split_vec(env));
		if (vec_push(env, &temp) < 0)
			return (free_split_vec(env));
		i++;
	}
	return (1);
}

int	interactive(int *last_return, t_vec *env)
{
	char	*line;

	*last_return = 0;
	while (*last_return > INT_MIN + 255)
	{
		signal_interactive();
		line = readline("minishell> ");
		if (line && ft_strlen(line) > 0)
		{
			signal_non_interactive();
			add_history(line);
			parse_line(line, last_return, env);
		}
		else if (!line)
			break ;
		free(line);
	}
	write(2, "exit\n", 5);
	toggle_carret(1);
	rl_clear_history();
	return (0);
}

int	set_shell_level(t_vec	*env)
{
	char	*shell_lvl;
	int		lvl_int;

	shell_lvl = ft_getenv("SHLVL", env);
	if (shell_lvl == 0)
		return (-1);
	lvl_int = ft_atoi(shell_lvl);
	lvl_int++;
	free(shell_lvl);
	shell_lvl = ft_itoa(lvl_int);
	if (shell_lvl == 0)
		return (-1);
	manual_export("SHLVL=", shell_lvl, env);
	free(shell_lvl);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int		last_return;
	t_vec	env;

	if (copy_env(&env, envp) < 0)
	{
		ft_error("error allocating memory\n");
		return (1);
	}
	if (set_shell_level(&env) == -1)
	{
		ft_error("error setting shell level\n");
		free_split_vec(&env);
		return (1);
	}
	last_return = 0;
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
		parse_line(argv[2], &last_return, &env);
	if (argc == 1)
		interactive(&last_return, &env);
	free_split_vec(&env);
	return (last_return & 255);
}
