/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:10:23 by toramo            #+#    #+#             */
/*   Updated: 2024/03/08 09:55:37 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <termios.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <sys/param.h>
# include <sys/wait.h>

# include "libft.h"
# include "commands.h"

typedef struct s_wc
{
	size_t	pindex;
	size_t	sindex;
	int		s_backtrack;
	int		last_wildcard;
	int		next_to_wildcard;
	int		i;
}	t_wc;

int		parse_line(const char *line, int *last_return, t_vec *env);
int		make_cmd_line_groups(t_vec *cmd_lines,
			const char *line, int *last_return, t_vec *env);
int		handle_pipelines(t_vec *cmd_lines, int *last_return, t_vec *env);
int		is_empty_line(const char *line);
int		check_parenthesis_count(const char *line);
int		check_open_quotes(const char *line);
int		check_parenth_syntax(t_vec *cmd_lines);
int		check_pipe_as_last(char *str);
int		check_andor_syntax(char **strs, size_t len);
int		check_consecutive_andor(const char *line);
int		check_redirect(t_vec *cmd_lines);
void	remove_parentheses(char *cmd_line);
int		redirect_check_error(char c);
int		get_heredocs(t_vec *heredoc_fds, t_vec *cmd_lines, size_t i, int j);
int		heredoc_input(char *limiter);
char	**ft_split_pipe(const char *s, char c);

int		ft_echo(t_vec *argv);
int		ft_cd(t_vec *argv, t_vec *env);
int		ft_pwd(t_vec *argv);
int		ft_env(t_vec *env);
int		env_entry_exists(char *str, t_vec *env);
int		remove_entry(char *str, t_vec *env);
int		contains_equals(const char *str);
int		contains_plusequals(char *str);
int		add_new_from_plusequals(t_vec *env, char *str);
int		ft_export(t_vec *argv, t_vec *env);
int		export_variable(size_t len, t_vec *env, char **strs);
void	manual_export(char *var, char *value, t_vec *env);
int		ft_unset(t_vec *argv, t_vec *env);
char	*ft_getenv(char *arg, t_vec *env);
int		builtin_index(char *command);
int		calculate_exit(t_vec *argv);

int		expand_envs(t_vec *argv, t_vec *env, int last_return);
int		finish_expand_str_envs(char **str_ptr, t_vec *str_vec);
char	*get_env_name(t_vec *str_vec, size_t start);
int		expand_star(t_vec *argv);
int		is_wildcard_match(char *string, char *pattern);
int		exp_wc_err(t_vec *new, char *msg);
int		is_rdrct(char *arg);
int		push_expanded(t_vec *dst, char **strs, int i);
int		after_wildcard_pushing(t_vec *dst, char *arg, int j, int redirect);
int		ambiguous_wildcard(char *arg);
int		remove_quotes(t_vec *argv);
char	*remove_outer_quotes(char *str);

int		ft_is_inside(const char *line, int i, int open_char);
int		ft_is_inside_any(char *str, int i);
int		contains_unquoted(char *str, int start, char c);

void	toggle_carret(int is_on);
void	signal_interactive(void);
void	signal_non_interactive(void);
void	signal_heredoc(int is_on);

int		ft_error(char *str);
int		cd_error(char *str);
int		minishell_error(char *str, char *message);
int		cmd_line_error(t_vec *cmd_lines);
int		handle_pipelines_error(t_vec *cmd_lines);
void	print_quit_signal(int signal);
int		print_syntax_error(char c);
int		command_not_found_error(char *cmd);
int		access_error(char *cmd);

int		vec_remove_str(t_vec *vec, size_t i);
int		vec_sort_strncmp(void *one, void *two);
int		copy_split_vec(t_vec *dst, t_vec *src);
void	free_heredoc_fd_list(t_vec *heredoc_fd_list);
int		vec_insert_substr(t_vec *strs, int i, char *str, int len);
int		vec_remove_insert_str(t_vec *strs, int i, char *str);

#endif
