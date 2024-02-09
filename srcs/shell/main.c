#include "minishell.h"

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
			return (ft_error("syntax error near unexpected token `)'\n"));
		i++;
	}
	if (open_parentheses != closed_parentheses)
		return (ft_error("syntax error: unclosed parentheses\n"));
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
		return (ft_error("syntax error: unclosed quotes\n"));
	else
		return (0);
}

int	parse_line(const char *line, int *last_return, t_vec *env)
{
	t_vec	cmd_lines;

	if (check_parenthesis_count(line) < 0 || check_open_quotes(line) < 0)
	{
		free_split_vec(env);
		return (-1);
	}
	if (vec_new(&cmd_lines, 16, sizeof(t_cmd_line)) < 0)
	{
		free_split_vec(env);
		return (ft_error("malloc"));
	}
	*last_return = make_cmd_line_groups(&cmd_lines, line, last_return, env);
	return (*last_return);
}

int	copy_env(t_vec *env, char **environ)
{
	char		*temp;
	int			i;

	i = 0;
	vec_new(env, 64, sizeof(char *));
	while (environ[i])
	{
		temp = ft_strdup(environ[i]);
		if (!temp)
			return (free_split_vec(env));
		if (vec_push(env, &temp) < 0)
			return (free_split_vec(env));
		i++;
	}
	return (1);
}

int	interactive(int *last_return, t_vec *env)
{
	char	*line;

	using_history();
	read_history(0);
	while (1)
	{
		*last_return = 0;
		signal_interactive();
		line = readline("minishell> ");
		if (line && ft_strlen(line) > 0)
		{
			signal_non_interactive();
			add_history(line);
			write_history(0);
			parse_line(line, last_return, env);
		}
		else if (!line)
			break ;
		free(line);
	}
	//toggle_carret(1);
	clear_history();
	free(line);
	return (*last_return);
}

int	main(int argc, char **argv, char **envp)
{
	int		last_return;
	t_vec	env;

	if (copy_env(&env, envp) < 0)
	{
		ft_error("error allocating memory\n");
		return (-1);
	}
	last_return = 0;
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		free_split_vec(&env);
		return (parse_line(argv[2], &last_return, &env));
	}
	if (argc == 1)
	{
		last_return = interactive(&last_return, &env);
		free_split_vec(&env);
		return (last_return);
	}
}
