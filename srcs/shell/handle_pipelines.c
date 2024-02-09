/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:48:20 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 15:48:21 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipelines_error(t_vec *cmd_lines, t_vec *env)
{
	ft_error("memory error\n");
	vec_iter(cmd_lines, free_cmd_line_str);
	vec_free(cmd_lines);
	free_split_vec(env);
	return (-1);
}

void	next_cmd_line(t_vec *cmd_lines,
		size_t *i, int *last_return)
{
	t_cmd_line	*curr_cmd_line;

	if (*last_return != 0)
	{
		curr_cmd_line = (t_cmd_line *) vec_get(cmd_lines, *i);
		while (*i < cmd_lines->len
			&& ft_strncmp(curr_cmd_line->str, "||", 2))
		{
			*i = *i + 1;
			curr_cmd_line = (t_cmd_line *) vec_get(cmd_lines, *i);
		}
	}
	else
	{
		curr_cmd_line = (t_cmd_line *) vec_get(cmd_lines, *i);
		while (*i < cmd_lines->len
			&& ft_strncmp(curr_cmd_line->str, "&&", 2))
		{
			*i = *i + 1;
			curr_cmd_line = (t_cmd_line *) vec_get(cmd_lines, *i);
		}
	}
}

int	handle_parentheses(t_cmd_line *cmd_line,
	int *last_return, t_vec *env, size_t j)
{
	ft_memmove(cmd_line->str, &cmd_line->str[j],
		ft_strlen(&cmd_line->str[j]));
	remove_parentheses(cmd_line);
	if (parse_line(cmd_line->str, last_return, env) < 0)
		return (-1);
	else
		return (0);
}

int	next_cmd_line_action(t_cmd_line *cmd_line,
	int *last_return, t_vec *env, size_t j)
{
	if (cmd_line->str[j] == '(')
	{
		if (handle_parentheses(cmd_line, last_return, env, j) < 0)
			return (-1);
	}
	else if (check_cmd_line_syntax(cmd_line) < 0)
		return (-1);
	else
		*last_return = run_command(&cmd_line->str[j], env);
	return (0);
}

int	handle_pipelines(t_vec *cmd_lines, int *last_return, t_vec *env)
{
	size_t		i;
	size_t		j;
	t_cmd_line	*cmd_line;

	i = 0;
	while (i < cmd_lines->len)
	{
		j = 0;
		cmd_line = vec_get(cmd_lines, i);
		if (check_parenth_syntax(cmd_line) < 0)
			return (handle_pipelines_error(cmd_lines, env));
		if (cmd_line->str[0] == '&' || cmd_line->str[0] == '|')
			j = j + 2;
		while (ft_isspace(cmd_line->str[j]))
			j++;
		if (next_cmd_line_action(cmd_line, last_return, env, j) < 0)
			return (handle_pipelines_error(cmd_lines, env));
		i++;
		next_cmd_line(cmd_lines, &i, last_return);
	}
	vec_iter(cmd_lines, free_cmd_line_str);
	vec_free(cmd_lines);
	return (*last_return);
}
