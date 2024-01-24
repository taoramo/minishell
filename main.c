#include "includes/minishell.h"

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
		if (line[i] == ')' && open_parentheses)
			closed_parentheses++;
		if (line[i] == ')' && !open_parentheses)
		{
			ft_printf("syntax error near unexpected token `)'\n");
			rl_on_new_line();
			return (-1);
		}
		i++;
	}
	if (open_parentheses != closed_parentheses)
	{
		ft_printf("syntax error: unclosed parentheses\n");
		rl_on_new_line();
		return (-1);
	}
	else
		return (open_parentheses);
}

int	check_open_quotes(const char *line)
{
	int				i;
	unsigned int	singles;
	unsigned int	doubles;

	i = 0;
	singles = 0;
	doubles = 0;
	while (line[i])
	{
		if (line[i] == 39)
			singles++;
		if (line[i] == 34)
			doubles++;
		i++;
	}
	if (singles % 2 || doubles % 2)
	{
		ft_printf("syntax error: unclosed quotes\n");
		rl_on_new_line();
		return (-1);
	}
	else 
		return (0);
}

int	parse_line(const char *line)
{
	t_vec	cmd_lines;

	if (check_parenthesis_count(line) < 0 || check_open_quotes(line) < 0)
		return (-1);
	if (vec_new(&cmd_lines, 16, sizeof(t_cmd_line)) < 0)
		return (ft_error("malloc"));
	if (make_cmd_line_groups(&cmd_lines, line) < 0)
		return (-1);
	return (0);
}

int	interactive(void)
{
	char				*line;

	using_history();
	read_history(0);
	while (1)
	{
		signal_interactive();
		line = readline("minishell> ");
		if (line && ft_strlen(line) > 0)
		{
			signal_non_interactive();
			add_history(line);
			write_history(0);
			parse_line(line);
		}
		else if (!line)
			break ;
		free(line);
	}
	clear_history();
	free(line);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
		parse_line(argv[2]);
	if (argc == 1)
		interactive();
}
