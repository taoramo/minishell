/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:48:20 by toramo            #+#    #+#             */
/*   Updated: 2024/02/15 10:10:40 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	handle_parentheses(char *cmd_line, int *last_return, t_vec *env)
{
	remove_parentheses(cmd_line);
	if (parse_line(cmd_line, last_return, env) < 0)
		return (-1);
	else
		return (0);
}

int	next_cmd_line_action(char *cmd_line, t_envinfo envinfo)
{
	if (*cmd_line == '(')
	{
		if (handle_parentheses(cmd_line, envinfo.last_return, envinfo.env) < 0)
			return (-1);
	}
	else if (check_cmd_line_syntax(cmd_line) < 0)
		return (-1);
	else
	{
		*envinfo.last_return = run_command(cmd_line, envinfo);
	}
	return (0);
}

int	check_andor_syntax(char **strs, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		if (strs[i][0] == '&' || strs[i][0] == '|')
		{
			j = j + 2;
			if (strs[i][2] == '|')
				return (ft_error("syntax error near unexpected token `|’"));
			if (strs[i][2] == '&')
				return (ft_error("syntax error near unexpected token `&’"));
			while (ft_isspace(strs[i][j]))
				j++;
			if (strs[i][j] == '|')
				return (ft_error("syntax error near unexpected token `|’"));
			if (strs[i][j] == '&')
				return (ft_error("syntax error near unexpected token `&’"));
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
	t_envinfo	envinfo;

	i = 0;
	strs = (char **)cmd_lines->memory;
	if (check_andor_syntax(strs, cmd_lines->len) < 0)
		return (handle_pipelines_error(cmd_lines));
	if (check_parenth_syntax(cmd_lines) < 0)
		return (handle_pipelines_error(cmd_lines));
	if (vec_new(&envinfo.heredoc_fds, cmd_lines->len, sizeof(t_vec)) == -1)
		return (-1);
	if (get_heredocs(&envinfo.heredoc_fds, cmd_lines) < 0)
		return (handle_pipelines_error(cmd_lines));
	envinfo.env = env;
	envinfo.last_return = last_return;
	while (i < cmd_lines->len && *last_return != INT_MIN)
	{
		j = 0;
		if (strs[i][0] == '&' || strs[i][0] == '|')
			j = j + 2;
		while (ft_isspace(strs[i][j]))
			j++;
		if (next_cmd_line_action(&strs[i][j], envinfo) < 0)
			return (handle_pipelines_error(cmd_lines));
		i++;
		next_cmd_line(cmd_lines, &i, envinfo.last_return);
	}
	free_split_vec(cmd_lines);
	return (*envinfo.last_return);
}
