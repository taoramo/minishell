/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:01:34 by toramo            #+#    #+#             */
/*   Updated: 2024/02/19 17:09:07 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_check_error(char c)
{
	if (c != 0)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, &c, 1);
	}
	else
		write(2, "minishell: syntax error", 23);
	write(2, "'\n", 2);
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

int	check_empty_andor(char **strs, size_t len)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 0;
	while (i < len)
	{
		j = 0;
		c = strs[i][0];
		while (strs[i][j] == '&' || strs[i][j] == '|')
			j++;
		while (ft_isspace(strs[i][j]))
			j++;
		if (strs[i][j] == 0)
			return (redirect_check_error(c));
		i++;
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
			if (strs[i][2] == '|' || (strs[i][0] == '|' && strs[i][1] != '|'))
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
	return (check_empty_andor(strs, len));
}

int	check_pipe_as_last(char *str)
{
	char	*ptr;
	int		i;

	ptr = ft_strrchr(str, '|');
	i = ptr - str;
	while (ptr != ft_strrchr(ptr, '|') && ptr > str
		&& !(!ft_is_inside(str, i, '"') && !ft_is_inside(str, i, 39)))
	{
		ptr = ft_strrchr(str, '|');
		i = ptr - str;
	}
	if (ptr > str)
	{
		i++;
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (!str[i])
			return (ft_error("syntax error near ynexpected token `|'"));
	}
	return (0);
}
