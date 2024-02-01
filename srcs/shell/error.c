#include "minishell.h"

int	ft_error(char *str)
{
	if (ft_strlen(str))
	{
		printf("%s\n", str);
		rl_on_new_line();
	}
	return (-1);
}

int	cmd_line_error(t_vec *cmd_lines)
{
	vec_iter(cmd_lines, free_cmd_line_str);
	vec_free(cmd_lines);
	return (ft_error("error allocating memory\n"));
}

int	minishell_error(char *str, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	return (-1);
}
