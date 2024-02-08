#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <termios.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <sys/errno.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <curses.h>
# include "libft.h"
# include "commands.h"

typedef struct s_cmd_line
{
	char			*str;
	int				return_value;
}	t_cmd_line;

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
void	remove_parentheses(t_cmd_line *cmd_line);
void	free_cmd_line_str(void *arg);
void	print_cmd_line(void *arg);
int		ft_is_inside(const char *line, int i, int open_char);
void	signal_interactive(void);
void	signal_non_interactive(void);
int		ft_error(char *str);
int		minishell_error(char *str, char *message);
int		cmd_line_error(t_vec *cmd_lines);
int		prepare_cmd(t_cmd_line *cmd_line, int *last_return);

int		ft_echo(t_vec *argv);
int		ft_cd(t_vec *argv, t_vec *env);
int		ft_pwd(t_vec *argv);
int		ft_env(t_vec *env);
int		ft_export(t_vec *argv, t_vec *env);
int		ft_unset(t_vec *argv, t_vec *env);
int		builtin_index(char *command);
int		(*get_builtin(int i))(t_vec *);
int		contains_equals(const char *str);
int		expand_star(t_vec *argv);
int		is_wildcard_match(char *string, char *pattern);
int		remove_quotes(t_vec *argv);
int		expand_env(t_vec *argv, t_vec *env);

#endif
