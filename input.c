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
		return (-1);
	else
		return (open_parentheses);
}

void	parse_line(const char *line)
{
	t_vec	cmd_lines;

	if (check_parenthesis_count(line) < 0)
		ft_error();
	if (vec_new(&cmd_lines, 16, sizeof(t_cmd_line)) < 0)
		ft_error();
	if (make_cmd_line_groups(&cmd_lines, line) < 0)
		ft_error();
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
