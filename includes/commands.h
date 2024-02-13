/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:09:06 by hpatsi            #+#    #+#             */
/*   Updated: 2024/02/13 10:47:44 by hpatsi           ###   ########.fr       */
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
	t_vec	*env;
}	t_command;

typedef struct s_redirect
{
	int	origial_fd;
	int	new_fd;
}	t_redirect;

int		ft_isspace(int c);
int		quote_length(char *str);

int		prepare_command(t_command *command, char *command_str, t_vec *env, int last_return);
int		split_command(t_vec *strs, char *str);
int		split_expanded_command(t_vec *argv);
int		extract_files(t_command *command);
int		add_path(char **command_ptr, t_vec *env);

int		infile_from_stdin(char *limiter);

int		run_command(char *str, t_vec *env, int last_return);
void	apply_redirect(void	*param);
pid_t	execute_command(t_vec argv, t_vec *env);

int		run_builtin(t_command *command);
int		run_builtin_pipe(t_command *command, int pos, int pipe_fds[], int pipe2_fds[]);

int		pipex(char *pipe_str, t_vec *env, int last_return);
int		count_commands(char **strs);
int		pipe_commands(char **strs, int **p_ids, t_vec *env, int last_return);
void	apply_pipe_redirect(t_command *command, int in_fd, int out_fd);
void	handle_parent(int pos, int pipe_fds[], int pipe2_fds[]);

#endif
