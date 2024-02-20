/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:48:28 by toramo            #+#    #+#             */
/*   Updated: 2024/02/20 12:21:56 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_parenthesis_count(const char *line)
{
	int	i;
	int	open_parentheses;
	int	closed_parentheses;

	i = 0;
	open_parentheses = 0;
	closed_parentheses = 0;
	while (line[i])
	{
		if (line[i] == '(')
			open_parentheses++;
		if (line[i] == ')' && open_parentheses)
			closed_parentheses++;
		if (line[i] == ')' && !open_parentheses)
			return (ft_error("syntax error near unexpected token `)'"));
		i++;
	}
	if (open_parentheses != closed_parentheses)
		return (ft_error("syntax error: unclosed parentheses"));
	else
		return (open_parentheses);
}

int	check_open_quotes(const char *line)
{
	int				i;
	unsigned int	singles;
	unsigned int	doubles;

	i = 0;
	singles = 0;
	doubles = 0;
	while (line[i])
	{
		if (line[i] == 39 && !ft_is_inside(line, i, '"'))
			singles++;
		if (line[i] == 34 && !ft_is_inside(line, i, 39))
			doubles++;
		i++;
	}
	if (singles % 2 || doubles % 2)
		return (ft_error("syntax error: unclosed quotes"));
	else
		return (0);
}

int	check_line_parenth_syntax(char *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd_line[i])
	{
		if (i != 0 && cmd_line[i] == '('
			&& !ft_is_inside(cmd_line, i, '"')
			&& !ft_is_inside(cmd_line, i, 39))
		{
			j = i - 1;
			while (ft_isspace(cmd_line[j]) && j >= 0)
				j--;
			if (cmd_line[j] != '&' && cmd_line[j] != '|' && j != 0)
				return (ft_error("syntax error near unexpected token `(’"));
		}
		i++;
	}
	return (0);
}

int	check_parenth_syntax(t_vec *cmd_lines)
{
	size_t	k;
	char	*cmd_line;

	k = 0;
	while (k < cmd_lines->len)
	{
		cmd_line = *(char **)vec_get(cmd_lines, k);
		if (check_line_parenth_syntax(cmd_line) < 0)
			return (-1);
		if (check_pipe_as_last(cmd_line) < 0)
			return (-1);
		k++;
	}
	return (1);
}
