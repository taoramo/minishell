#include "includes/minishell.h"
#include "readline/readline.h"

int	check_cmd_line_syntax(t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line->str[i])
	{
		if ((cmd_line->str[i] == '|' && i == 0)
			|| (i != 0 && cmd_line->str[i] == '|' && ft_strncmp(&cmd_line->str[i - 1], " || ", 4)))
			return (ft_error("syntax error near unexpected token `|’"));
		if ((cmd_line->str[i] == '&' && i == 0)
			|| (i != 0 && cmd_line->str[i] == '&' && ft_strncmp(&cmd_line->str[i - 1], " && ", 4)))
			return (ft_error("syntax error near unexpected token `&’"));
		i++;
	}
	return (1);
}

int	cmd_line_lexer(t_cmd_line *cmd_line, int *last_return)
{
	if (check_cmd_line_syntax(cmd_line) < 0)
		return (-1);
	if (prepare_cmd(cmd_line, last_return) < 0)
		return (-1);
	return (1);
}

int	handle_pipelines(t_vec *cmd_lines, int *last_return)
{
	size_t		i;
	int			j;
	t_cmd_line	*cmd_line;

	i = 0;
	j = 0;
	while (i < cmd_lines->len)
	{
		cmd_line = vec_get(cmd_lines, i);
		if (cmd_line->str[0] == '&' || cmd_line->str[0] == '|')
			j = j + 2;
		while (ft_isspace(cmd_line->str[j]))
			j++;
		if (cmd_line->str[j] == '(')
		{
			ft_memmove(cmd_line->str, &cmd_line->str[j], ft_strlen(&cmd_line->str[j]));
			remove_parentheses(cmd_line);
			parse_line(cmd_line->str, last_return);
		}
		if (cmd_line_lexer(cmd_line, last_return) < 0)
		{
			vec_iter(cmd_lines, free_cmd_line_str);
			vec_free(cmd_lines);
			return (-1);
		}
		i++;
	}
	return (0);
}
