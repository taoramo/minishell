/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:48:20 by toramo            #+#    #+#             */
/*   Updated: 2024/02/12 10:03:25 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipelines_error(t_vec *cmd_lines)
{
	free_split_vec(cmd_lines);
	return (-1);
}

void	next_cmd_line(t_vec *cmd_lines, size_t *i, int *last_return)
{
	char	*curr_cmd_line;
	char	**strs;

	strs = (char **)cmd_lines->memory;
	if (*last_return != 0)
	{
		curr_cmd_line = strs[*i];
		while (*i < cmd_lines->len
			&& ft_strncmp(curr_cmd_line, "|| ", 3))
		{
			*i = *i + 1;
			curr_cmd_line = strs[*i];
		}
	}
	else
	{
		curr_cmd_line = strs[*i];
		while (*i < cmd_lines->len
			&& ft_strncmp(curr_cmd_line, "&& ", 3))
		{
			*i = *i + 1;
			curr_cmd_line = strs[*i];
		}
	}
}

int	handle_parentheses(char *cmd_line,
	int *last_return, t_vec *env, size_t j)
{
	ft_memmove(cmd_line, &cmd_line[j], ft_strlen(&cmd_line[j]));
	remove_parentheses(cmd_line);
	if (parse_line(cmd_line, last_return, env) < 0)
		return (-1);
	else
		return (0);
}

int	next_cmd_line_action(char *cmd_line,
	int *last_return, t_vec *env, size_t j)
{
	if (cmd_line[j] == '(')
	{
		if (handle_parentheses(cmd_line, last_return, env, j) < 0)
			return (-1);
	}
	else if (check_cmd_line_syntax(cmd_line) < 0)
		return (-1);
	else
		*last_return = run_command(&cmd_line[j], env, *last_return);
	return (0);
}

int	check_andor_syntax(t_vec *cmd_lines)
{
	size_t	i;
	size_t	j;
	char	**strs;

	strs = (char **)cmd_lines->memory;
	i = 0;
	j = 0;
	while (i < cmd_lines->len)
	{
		if (strs[i][0] == '&' || strs[i][0] == '|')
		{
			if (strs[i][2] != ' ')
				return (ft_error("syntax error near unexpected token `&’"));
			j = j + 2;
			while (ft_isspace(strs[i][j]))
				j++;
			if (strs[i][j] == '|' || strs[i][j] == '&')
				return (ft_error("syntax error near unexpected token `|’"));
		}
		i++;
	}
	return (1);
}

int	handle_pipelines(t_vec *cmd_lines, int *last_return, t_vec *env)
{
	size_t		i;
	size_t		j;
	char		**strs;

	i = 0;
	strs = (char **)cmd_lines->memory;
	if (check_andor_syntax(cmd_lines) < 0)
	{
		free_split_vec(cmd_lines);
		return (*last_return);
	}
	while (i < cmd_lines->len)
	{
		j = 0;
		if (check_parenth_syntax(strs[i]) < 0)
			return (handle_pipelines_error(cmd_lines));
		if (strs[i][0] == '&' || strs[i][0] == '|')
			j = j + 2;
		while (ft_isspace(strs[i][j]))
			j++;
		if (next_cmd_line_action(strs[i], last_return, env, j) < 0)
			return (handle_pipelines_error(cmd_lines));
		i++;
		next_cmd_line(cmd_lines, &i, last_return);
	}
	free_split_vec(cmd_lines);
	return (*last_return);
}
