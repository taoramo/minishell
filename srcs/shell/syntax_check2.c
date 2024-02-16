#include "minishell.h"

int	redirect_check_error(char c)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, &c, 1);
	write(2, "'\n", 2);
	return (-1);
}

int	check_redirect_cmdline(char *cmd_line)
{
	int		i;
	char	c;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '<' || cmd_line[i] == '>')
		{
			c = cmd_line[i];
			if ((c == '<' && cmd_line[i + 1] == '>')
				|| (c == '>' && cmd_line[i + 1] == '<'))
				return (redirect_check_error(c));
			if (cmd_line[i] && cmd_line[i + 1] == cmd_line[i])
				i++;
			i++;
			while (ft_isspace(cmd_line[i]))
				i++;
			if (!cmd_line[i] || cmd_line[i] == '|' || cmd_line[i] == '&'
				|| cmd_line[i] == '(' || cmd_line[i] == ')')
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
