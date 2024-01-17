#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <string>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include "libft/libft.h"

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
	supergroup,
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
	int				index;
	t_group_type	type;
}	t_cmd_line;

void	parse_line(const char *line);
int		check_line_parentheses(const char *line);
void	parse_cmd_line_groups(t_vec *cmd_line_groups);
void	parse_cmd_line(char *str);
void	parse_cmd(char *str);
void	parse_param(char *str);
int		make_cmd_line_groups(t_vec *cmd_line_groups,
			const char *line, int index);
int		next_cmd_line_length(const char *line);
void	ft_error(void);
int		check_parenthesis_count(const char *line);
void	set_group_types(void *arg);
int		expand_supergroups(t_vec *cmd_line_groups);

#endif
