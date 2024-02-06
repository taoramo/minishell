/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:09:06 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/06 09:43:29 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "libft.h"
# include "minishell.h"

typedef struct s_command
{
	t_vec	argv;
	t_vec	redirects;
	pid_t	process_id;
}	t_command;

typedef struct s_redirect
{
	int	origial_fd;
	int	new_fd;
}	t_redirect;

int		ft_isspace(int c);

int		prepare_command(t_command *command, char *command_str);
int		split_command(t_vec *strs, char *str);
int		extract_files(t_command *command);
int		add_path(char **command_ptr);

int		infile_from_stdin(char *limiter);

int		run_command(char *command_str);
void	apply_redirect(void	*param);
int		execute_command(t_vec argv);

int		run_builtin(t_command *command);

int		pipex(char *command_str);
int		pipe_commands(t_vec commands, int **process_ids);

#endif
