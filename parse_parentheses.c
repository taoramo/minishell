#include "minishell.h"

static int	next_grp_in_par(const char *line)
{
	int	open_parentheses;
	int	i;

	i = 1;
	open_parentheses = 0;
	while (line[i] && !(open_parentheses == 0 && line[i] == ')'))
	{
		if (line[i] == '(')
			open_parentheses++;
		if (line[i] == ')' && open_parentheses)
			open_parentheses--;
		i++;
	}
	return (i - 1);
}

static int	next_grp(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '(')
		i++;
	return (i);
}

int	next_cmd_line_length(const char *line)
{
	if (line[0] == '(')
		return (next_grp_in_par(line));
	else
		return (next_grp(line));
}

int	line_to_cmd_line_group(t_vec *cmd_line_groups, const char *line)
{
	int					i;
	t_cmd_line_group	current;

	i = 0;
	while (next_cmd_line_length(&line[i]) && line[i] != ')')
	{
		ft_memset(&current, 0, sizeof(t_cmd_line_group));
		if (line[i] == '(')
		{
			current.str = ft_substr(line, i + 1, next_grp_in_par(&line[i]));
			i += next_grp_in_par(&line[i]) + 1;
		}
		else
		{
			current.str = ft_substr(line, i, next_grp(&line[i]));
			i += next_grp(&line[i]);
		}
		printf("%s\n", current.str);
		vec_push(cmd_line_groups, &current);
	}
	return (0);
}
