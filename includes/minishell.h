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
# include <sys/ioctl.h>
# include <curses.h>
# include "libft.h"
# include "commands.h"

typedef enum e_syntax
{
	string,
	greater,
	greatergreater,
	smaller,
	smallersmaller,
	pipechar,
	asterisk
}	t_syntax;

typedef enum e_group_type
{
	group,
	cmd_line
}	t_group_type;

typedef struct s_token
{
	t_vec		*str;
	t_syntax	type;
}	t_token;

typedef struct s_cmd_line
{
	char			*str;
	int				return_value;
}	t_cmd_line;

int		parse_line(const char *line, int *last_return);
int		check_line_parentheses(const char *line);
int		make_cmd_line_groups(t_vec *cmd_lines,
			const char *line, int *last_return);
int		next_cmd_line_length(const char *line);
int		handle_pipelines(t_vec *cmd_lines, int *last_return);
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
#endif
