#include "minishell.h"

void	new_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	signal_interactive(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = new_prompt; 
	sigaction(SIGINT, &sa, 0);
	ft_bzero(&sb, sizeof(sa));
	sb.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sb, 0);
}

void	print_new_line(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	signal_non_interactive(void)
{
	struct sigaction	sa;
	
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = print_new_line;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sa, 0);
}
