#include "includes/minishell.h"

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
