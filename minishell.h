#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
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
	line,
	cmd_line_group,
	cmd_line,
	cmd,
	param
}	t_syntax;

typedef struct s_token
{
	t_vec		*str;
	t_syntax	type;
}	t_token;

typedef struct s_cmd_line_group
{
	char	*str;
	int		index;
}	t_cmd_line_group;

typedef struct s_cmd_line
{
	t_vec	*cmds;
	int		execute;
}	t_cmd_line;

typedef struct s_group_tree
{
	char				*group;
	struct s_group_tree	*left;
	struct s_group_tree	*right;
	struct s_group_tree	*parent;
}	t_group_tree;

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

#endif
