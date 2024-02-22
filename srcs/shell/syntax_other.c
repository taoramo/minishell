/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:01:34 by toramo            #+#    #+#             */
/*   Updated: 2024/02/22 09:37:35 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_check_error(char c)
{
	if (c != 0)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, &c, 1);
		write(2, "'\n", 2);
	}
	else
	{
		write(2, "minishell: syntax error", 23);
		write(2, "\n", 2);
	}
	return (-1);
}

int	check_redirect_cmdline(char *s)
{
	int		i;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			c = s[i];
			if ((c == '<' && s[i + 1] == '>') || (c == '>' && s[i + 1] == '<')
				|| !ft_strncmp(&s[i], "<<<", 3) || !ft_strncmp(&s[i], ">>>", 3))
				return (redirect_check_error(c));
			if (s[i] && s[i + 1] == s[i])
				i++;
			i++;
			while (ft_isspace(s[i]))
				i++;
			if (!s[i] || s[i] == '|' || s[i] == '&'
				|| s[i] == '(' || s[i] == ')' || s[i] == '>' || s[i] == '<')
				return (redirect_check_error(c));
		}
		i++;
	}
	return (1);
}

int	check_redirect(t_vec *cmd_lines)
{
	size_t	i;

	i = 0;
	while (i < cmd_lines->len)
	{
		if (check_redirect_cmdline(*(char **)vec_get(cmd_lines, i)) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	is_empty_line(const char *line)
{
	while (*line != 0)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
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
