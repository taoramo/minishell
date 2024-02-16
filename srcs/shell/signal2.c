/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 08:52:14 by toramo            #+#    #+#             */
/*   Updated: 2024/02/16 08:52:15 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_new_line(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	signal_non_interactive(void)
{
	struct sigaction	sa;
	struct sigaction	sb;

	toggle_carret(1);
	ft_bzero(&sa, sizeof(sa));
	ft_bzero(&sb, sizeof(sb));
	sa.sa_handler = print_new_line;
	sb.sa_handler = print_quit_signal;
	sigaction(SIGINT, &sa, 0);
	sigaction(SIGQUIT, &sb, 0);
}
