#include "minishell.h"

int	check_line_parentheses(const char *line)
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
		if (line[i] == ')')
			closed_parentheses++;
		i++;
	}
	if (open_parentheses != closed_parentheses)
		return (0);
	else
		return (open_parentheses + 1);
}

int	line_to_cmd_line_group(t_vec *cmd_line_groups, const char *line)
{
	int					start;
	int					end;
	int					i;
	t_cmd_line_group	current;

	start = 0;
	end = 0;
	i = 0;
	while (line[start] && line[end] && check_line_parentheses(&line[start]))
	{
		while (line[start] != '(')
			start++;
		while (line[end] != ')')
			end++;
		current.str = ft_substr(line, 1, end - 2);
		if (!current.str)
			return (ft_error());
		vec_push(cmd_line_groups, &current);
		start = end;
	}
}

t_vec	*parse_line(const char *line)
{
	t_vec	*cmd_line_groups;

	if (!check_line_parentheses(line))
		return (0);
	cmd_line_groups = ft_calloc(1, sizeof(t_vec));
	if (!cmd_line_groups)
		return (0);
	vec_new(cmd_line_groups, check_line_parentheses(line), sizeof(t_cmd_line_group));
	line_to_cmd_line_group(cmd_line_groups, line);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("blaa");
		parse_line(line);
		free(line);
	}
}
