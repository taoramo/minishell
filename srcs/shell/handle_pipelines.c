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

#include "libft.h"
#include "minishell.h"

int	handle_pipelines_error(t_vec *cmd_lines, t_vec *env)
{
	free_split_vec(cmd_lines);
	free_split_vec(env);
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
			&& ft_strncmp(curr_cmd_line, "||", 2))
		{
			*i = *i + 1;
			curr_cmd_line = strs[*i];
		}
	}
	else
	{
		curr_cmd_line = strs[*i];
		while (*i < cmd_lines->len
			&& ft_strncmp(curr_cmd_line, "&&", 2))
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
		*last_return = run_command(&cmd_line[j], env);
	return (0);
}

int	handle_pipelines(t_vec *cmd_lines, int *last_return, t_vec *env)
{
	size_t		i;
	size_t		j;
	char		**strs;

	i = 0;
	strs = (char **)cmd_lines->memory;
	while (i < cmd_lines->len)
	{
		j = 0;
		if (check_parenth_syntax(strs[i]) < 0)
			return (handle_pipelines_error(cmd_lines, env));
		if (strs[i][0] == '&' || strs[i][0] == '|')
			j = j + 2;
		while (ft_isspace(strs[i][j]))
			j++;
		if (next_cmd_line_action(strs[i], last_return, env, j) < 0)
			return (handle_pipelines_error(cmd_lines, env));
		i++;
		next_cmd_line(cmd_lines, &i, last_return);
	}
	free_split_vec(cmd_lines);
	return (*last_return);
}
