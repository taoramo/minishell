/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipelines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:48:20 by toramo            #+#    #+#             */
/*   Updated: 2024/02/15 10:26:13 by hpatsi           ###   ########.fr       */
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

int	handle_cmd_lines(t_vec *cmd_lines, t_vec *env,
	t_vec *heredoc_fd_list, int *last_return)
{
	t_envinfo	envinfo;
	size_t		i;
	size_t		j;
	char		**strs;

	i = 0;
	envinfo.env = env;
	envinfo.last_return = last_return;
	strs = (char **)cmd_lines->memory;
	while (i < cmd_lines->len && *last_return != INT_MIN)
	{
		envinfo.heredoc_fds = (t_vec *)vec_get(heredoc_fd_list, i);
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
	vec_free(heredoc_fd_list);
	return (*envinfo.last_return);
}

int	handle_pipelines(t_vec *cmd_lines, int *last_return, t_vec *env)
{
	char		**strs;
	t_vec		heredoc_fd_list;

	strs = (char **)cmd_lines->memory;
	if (check_andor_syntax(strs, cmd_lines->len) < 0
		|| check_parenth_syntax(cmd_lines) < 0 || check_redirect(cmd_lines) < 0)
		return (handle_pipelines_error(cmd_lines));
	if (vec_new(&heredoc_fd_list, cmd_lines->len, sizeof(t_vec)) == -1)
		return (-1);
	if (get_heredocs(&heredoc_fd_list, cmd_lines, 0, 0) < 0)
		return (handle_pipelines_error(cmd_lines));
	vec_free(&heredoc_fd_list);
	return (handle_cmd_lines(cmd_lines, env, &heredoc_fd_list, last_return));
}
