/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:10:23 by toramo            #+#    #+#             */
/*   Updated: 2024/02/20 14:58:18 by hpatsi           ###   ########.fr       */
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
int		check_line_parentheses(const char *line);
int		make_cmd_line_groups(t_vec *cmd_lines,
			const char *line, int *last_return, t_vec *env);
int		next_cmd_line_length(const char *line);
int		handle_pipelines(t_vec *cmd_lines, int *last_return, t_vec *env);
int		check_parenthesis_count(const char *line);
int		check_open_quotes(const char *line);
int		check_parenth_syntax(t_vec *cmd_lines);
void	remove_parentheses(char *cmd_line);
int		redirect_check_error(char c);
void	print_cmd_line(void *arg);
int		ft_is_inside(const char *line, int i, int open_char);
int		ft_is_inside_any(char *str, int i);
int		contains_unquoted(char *str, int start, char c);
void	signal_interactive(void);
void	signal_non_interactive(void);
int		ft_error(char *str);
int		minishell_error(char *str, char *message);
int		cmd_line_error(t_vec *cmd_lines);
int		prepare_cmd(char *cmd_line, int *last_return);

int		ft_echo(t_vec *argv);
int		ft_cd(t_vec *argv, t_vec *env);
int		ft_pwd(t_vec *argv);
int		ft_env(t_vec *env);
int		ft_export(t_vec *argv, t_vec *env);
int		ft_unset(t_vec *argv, t_vec *env);
char	*ft_getenv(char *arg, t_vec *env);
int		builtin_index(char *command);
int		(*get_builtin(int i))(t_vec *);
int		contains_equals(const char *str);
int		expand_star(t_vec *argv);
int		is_wildcard_match(char *string, char *pattern);
int		remove_quotes(t_vec *argv);
char	*remove_outer_quotes(char *str);
int		expand_envs(t_vec *argv, t_vec *env, int last_return);
void	toggle_carret(int is_on);
int		vec_sort_strncmp(void *one, void *two);
int		cd_error(char *str);
void	toggle_echo(int is_on);
int		handle_pipelines_error(t_vec *cmd_lines);
int		env_entry_exists(char *str, t_vec *env);
int		remove_entry(char *str, t_vec *env);
int		contains_plusequals(char *str);
int		get_heredocs(t_vec *heredoc_fds, t_vec *cmd_lines, size_t i, int j);
int		heredoc_input(char *limiter);
int		after_wildcard_pushing(t_vec *dst, char *arg, int j, int redirect);
int		copy_env(t_vec *env, char **environ);
int		exp_wc_err(t_vec *new, char *msg);
int		expnd_rdrct(t_vec *dst, char *path, char *arg);
int		ambiguous_wildcard(char *arg);
int		is_rdrct(char *arg);
int		add_redirect_char(t_vec *dst, char *arg);
void	signal_heredoc(int is_on);
void	vec_free_iter(void *arg);
void	print_quit_signal(int signal);
int		copy_split_vec(t_vec *dst, t_vec *src);
int		push_expanded(t_vec *dst, char **strs, int i);
int		check_andor_syntax(char **strs, size_t len);
int		check_redirect(t_vec *cmd_lines);
int		check_redirect_cmdline(char *cmd_line);
char	*get_env_name(t_vec *str_vec, size_t start);
char	**ft_split_pipe(const char *s, char c);
int		check_pipe_as_last(char *str);
void	vec_iter_free(void *arg);
void	free_heredoc_fd_list(t_vec *heredoc_fd_list);
int		add_new_from_plusequals(t_vec *env, char *str);
int		check_consecutive_andor(const char *line);
int		print_syntax_error(char c);
int		check_line_after_parenth(char *cmd_line);

#endif
