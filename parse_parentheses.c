#include "minishell.h"

int	next_start(const char *line, int index)
{
	int	i;

	i = index;
	while (ft_isspace(line[i]))
		i++;
	return (i);
}

int	next_length(const char *line, int index)
{
	int	i;
	int	open_braces;
	int	closed_braces;

	i = 0;
	if (index)
	{
		
	
}

int	make_cmd_line_groups(t_vec *cmd_line_groups, const char *line, int index)
{
	int					i;
	int					start;
	int					length;
	t_cmd_line_group	current;

	i = 0;
	while (next_length(line, i))
	{
		start = next_start(line, i);
		length = next_length(line, start);
		ft_memset(&current, 0, sizeof(t_cmd_line_group));
		current.str = ft_substr(line, start, length);
		current.index = index;
		printf("%s\n", current.str);
		vec_push(cmd_line_groups, &current);
		i = start + length + 1;
	}
}
