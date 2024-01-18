#include "minishell.h"
#include <readline/history.h>
#include <sys/signal.h>

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
	vec_iter(&cmd_lines, print_cmd_line);
}

void	siginthandler(int signal)
{
	(void)signal;
	rl_cleanup_after_signal();
	return ;
}

void	block_quit_signal(void)
{
	struct sigaction	sa;
	sigset_t			block_mask;
	sigset_t			sa_set;

	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGQUIT);
	sigprocmask(SIG_BLOCK, &block_mask, 0);
	sigemptyset(&sa_set);
	sigaddset(&sa_set, SIGINT);
	sa.sa_handler = siginthandler;
	sa.sa_mask = sa_set;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, 0);
}

int	main(void)
{
	char				*line;

	block_quit_signal();
	using_history();
	read_history(0);
	while (1)
	{
		line = readline("minishell> ");
		if (line && ft_strlen(line) > 0)
		{
			add_history(line);
			write_history(0);
			parse_line(line);
		}
		else
			break ;
		free(line);
	}
	clear_history();
	free(line);
}
