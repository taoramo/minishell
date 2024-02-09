/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:09:12 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:09:24 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_line(const char *line, int *last_return, t_vec *env)
{
	t_vec	cmd_lines;

	if (check_parenthesis_count(line) < 0 || check_open_quotes(line) < 0)
	{
		free_split_vec(env);
		return (-1);
	}
	if (vec_new(&cmd_lines, 16, sizeof(char *)) < 0)
	{
		free_split_vec(env);
		return (ft_error("malloc"));
	}
	*last_return = make_cmd_line_groups(&cmd_lines, line, last_return, env);
	return (*last_return);
}

int	copy_env(t_vec *env, char **environ)
{
	char		*temp;
	int			i;

	i = 0;
	vec_new(env, 64, sizeof(char *));
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

	using_history();
	read_history(0);
	while (1)
	{
		*last_return = 0;
		signal_interactive();
		line = readline("minishell> ");
		if (line && ft_strlen(line) > 0)
		{
			signal_non_interactive();
			add_history(line);
			write_history(0);
			parse_line(line, last_return, env);
		}
		else if (!line)
			break ;
		free(line);
	}
	toggle_carret(1);
	clear_history();
	free(line);
	return (*last_return);
}

int	main(int argc, char **argv, char **envp)
{
	int		last_return;
	t_vec	env;

	if (copy_env(&env, envp) < 0)
	{
		ft_error("error allocating memory\n");
		return (-1);
	}
	last_return = 0;
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		last_return = parse_line(argv[2], &last_return, &env);
		free_split_vec(&env);
		return (last_return);
	}
	if (argc == 1)
	{
		last_return = interactive(&last_return, &env);
		free_split_vec(&env);
		return (last_return);
	}
	free_split_vec(&env);
}
