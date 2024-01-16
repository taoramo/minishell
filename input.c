#include "minishell.h"

void	ft_error(void)
{
	printf("Error\n");
}

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
		if (line[i] == ')')
			closed_parentheses++;
		i++;
	}
	if (open_parentheses != closed_parentheses)
		return (0);
	else
		return (open_parentheses);
}

void	parse_line(const char *line)
{
	t_vec	*cmd_line_groups;

	if (!check_parenthesis_count(line))
		ft_error();
	cmd_line_groups = ft_calloc(1, sizeof(t_vec));
	if (!cmd_line_groups)
		ft_error();
	vec_new(cmd_line_groups, 16,
		sizeof(t_cmd_line_group));
	if (make_cmd_line_groups(cmd_line_groups, line, 0) != 0)
		ft_error();
	vec_iter(cmd_line_groups, set_group_types);
	expand_super_groups(cmd_line_groups);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell>");
		parse_line(line);
		free(line);
	}
}
