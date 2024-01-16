#include "minishell.h"

static int	next_grp_in_par(const char *line)
{
	int	open_parentheses;
	int	i;

	i = 0;
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	i++;
	open_parentheses = 0;
	while (line[i] && !(open_parentheses == 0 && line[i] == ')'))
	{
		if (line[i] == '(')
			open_parentheses++;
		if (line[i] == ')' && open_parentheses)
			open_parentheses--;
		i++;
	}
	return (i);
}

static int	next_grp(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '(')
		i++;
	return (i);
}

static int	next_grp_copy(const char *line, int index)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '(')
		i++;
	if (line[i] == '(' && index != 0)
	{
		i--;
		while (ft_isspace(line[i]))
			i--;
		i = i - 2;
	}
	return (i);
}

int	next_cmd_line_length(const char *line)
{
	if (line[0] == '(')
		return (next_grp_in_par(line));
	else
		return (next_grp(line));
}

int	reverse_to_op(const char *line, int i)
{
	if (i == 0)
		return (0);
	else
	{
		i--;
		while (ft_isspace(line[i]) && i >= 0)
			i--;
		i = i - 2;
		return (i);
	}
}

int	make_cmd_line_groups(t_vec *cmd_line_groups,
	const char *line, int group_index)
{
	int					i;
	t_cmd_line_group	current;

	i = 0;
	while (next_cmd_line_length(&line[i]))
	{
		ft_memset(&current, 0, sizeof(t_cmd_line_group));
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '(')
		{
			i = reverse_to_op(line, i);
			current.str = ft_substr(line, i, next_grp_in_par(&line[i]) + 1);
			i += next_grp_in_par(&line[i]) + 1;
		}
		else
		{
			current.str = ft_substr(line, i, next_grp_copy(&line[i], 0));
			i += next_grp(&line[i]);
		}
		current.index = group_index;
		printf("%s\n", current.str);
		vec_push(cmd_line_groups, &current);
	}
	return (0);
}
