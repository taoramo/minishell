#include "minishell.h"

int	next_start(const char *line, int index)
{
	int	i;

	i = index;
	while (ft_isspace(line[i]) && line[i])
		i++;
	return (i);
}

int	length_next_in_parenth(const char *line, int index, int i)
{
	int	open_parentheses;

	open_parentheses = 0;
	while (line[index + i] && !(open_parentheses == 0
			&& line[index + i - 1] == ')'))
	{
		if (line[index + i] == '(')
			open_parentheses++;
		if (line[index + i] == ')' && open_parentheses)
			open_parentheses--;
		i++;
	}
	return (i);
}

int	length_next_outside_parenth(const char *line, int index, int i)
{
	while (line[index + i] && line[index + i] != '(')
		i++;
	if (line[index + i] == '(')
	{
		i--;
		while (ft_isspace(line[index + i]) && line[i])
			i--;
		if (!ft_strncmp(&line[index + i - 2], " && ", 4)
			|| !ft_strncmp(&line[index + i -2], " || ", 4))
			i = i - 2;
		while (ft_isspace(line[index + i]) && line[i])
			i--;
		i++;
	}
	return (i);
}

int	next_length(const char *line, int index)
{
	int	i;

	i = 0;
	if (line[index + i] == 0)
		return (0);
	if (index)
	{
		while (ft_isspace(line[index + i]) && line[index + i])
			i++;
		if (!ft_strncmp(&line[index + i], "&&", 2)
			|| !ft_strncmp(&line[index + i -2], "||", 2))
			i = i + 2;
		while (ft_isspace(line[index + i]) && line[index + i])
			i++;
	}
	if (line[index + i] == '(')
		return (length_next_in_parenth(line, index, i));
	else
		return (length_next_outside_parenth(line, index, i));
}

int	make_cmd_line_groups(t_vec *cmd_line_groups, const char *line, int index)
{
	int					i;
	int					start;
	int					length;
	t_cmd_line_group	current;

	i = 0;
	while (line[i] != 0)
	{
		start = next_start(line, i);
		length = next_length(line, start);
		ft_memset(&current, 0, sizeof(t_cmd_line_group));
		current.str = ft_substr(line, start, length);
		if (!current.str)
			return (1);
		current.index = index;
		printf("%s\n", current.str);
		vec_push(cmd_line_groups, &current);
		i = start + length + 1;
	}
	return (0);
}
