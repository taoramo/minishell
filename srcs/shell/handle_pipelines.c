#include "minishell.h"

int	check_parenth_syntax(t_cmd_line *cmd_line)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_line->str[i])
	{
		if (i != 0 && cmd_line->str[i] == '('
			&& !ft_is_inside(cmd_line->str, i, '"')
			&& !ft_is_inside(cmd_line->str, i, 39))
		{
			j = i - 1;
			while (ft_isspace(cmd_line->str[j]))
				j--;
			if (cmd_line->str[j] != '&' && cmd_line->str[j] != '|')
				return (ft_error("syntax error near unexpected token `(’"));
		}
		i++;
	}
	return (1);
}
	

int	check_cmd_line_syntax(t_cmd_line *cmd_line)
{
	int	i;

	i = 0;
	while (cmd_line->str[i])
	{
		// if ((cmd_line->str[0] == '|' && cmd_line->str[1] != '|')
		// 	|| (i != 0 && cmd_line->str[i] == '|' && ft_strncmp(&cmd_line->str[i - 1], " || ", 4)))
		// 	return (ft_error("syntax error near unexpected token `|’"));
		if ((cmd_line->str[0] == '&' && cmd_line->str[1] != '&')
			|| (i != 0 && cmd_line->str[i] == '&' && ft_strncmp(&cmd_line->str[i - 1], " && ", 4)))
			return (ft_error("syntax error near unexpected token `&’"));
		if (!ft_strncmp(&cmd_line->str[i], "&&", 2) || !ft_strncmp(&cmd_line->str[i], "||", 2))
			i = i + 2;
		else
			i++;
	}
	return (1);
}

int	handle_pipelines(t_vec *cmd_lines, int *last_return)
{
	size_t		i;
	int			j;
	t_cmd_line	*cmd_line;
	t_cmd_line	*curr_cmd_line;

	i = 0;
	while (i < cmd_lines->len)
	{
		j = 0;
		cmd_line = vec_get(cmd_lines, i);
		check_parenth_syntax(cmd_line);
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
		else if (check_cmd_line_syntax(cmd_line) < 0)
		{
			vec_iter(cmd_lines, free_cmd_line_str);
			vec_free(cmd_lines);
			return (-1);
		}
		else
			*last_return = run_command(&cmd_line->str[j]);
		i++;
		if (*last_return == 1)
		{
			curr_cmd_line = (t_cmd_line *) vec_get(cmd_lines, i);
			while (i < cmd_lines->len && ft_strncmp(curr_cmd_line->str, "||", 2))
			{
				i++;
				curr_cmd_line = (t_cmd_line *) vec_get(cmd_lines, i);
			}
		}
		if (*last_return == 0)
		{
			curr_cmd_line = (t_cmd_line *) vec_get(cmd_lines, i);
			while (i < cmd_lines->len && ft_strncmp(curr_cmd_line->str, "&&", 2))
			{
				i++;
				curr_cmd_line = (t_cmd_line *) vec_get(cmd_lines, i);
			}
		}
	}
	return (*last_return);
}
