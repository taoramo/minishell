#include "includes/minishell.h"

/* void	set_group_types(void *arg)
{
	t_cmd_line	*ptr;
	size_t		i;

	ptr = arg;
	i = 0;
	while (ptr->str[i])
	{
		if (ptr->str[i] == '(')
		{
			ptr->type = supergroup;
			return ;
		}
		i++;
	}
	ptr->type = group;
} */

void	remove_parentheses(t_cmd_line *cmd_line)
{
	size_t	i;
	size_t	open_parentheses;
	size_t	start;
	size_t	end;

	open_parentheses = 0;
	i = 0;
	while (cmd_line->str[i] && cmd_line->str[i] != '(')
		i++;
	open_parentheses++;
	start = i;
	while (cmd_line->str[i] && !(open_parentheses == 0
			&& cmd_line->str[i] == ')'))
	{
		i++;
		if (cmd_line->str[i] == '(')
			open_parentheses++;
		if (cmd_line->str[i] == ')')
			open_parentheses--;
	}
	end = i;
	ft_memmove(&cmd_line->str[start], &cmd_line->str[start + 1],
		ft_strlen(&cmd_line->str[start + 1]));
	cmd_line->str[end - 1] = 0;
}

int	handle_supergroup(t_vec *cmd_lines, int i)
{
	t_vec		temp;
	t_cmd_line	*ptr;
	size_t		j;

	if (vec_new(&temp, 16, sizeof(t_cmd_line)) < 0)
		return (ft_error("malloc"));
	ptr = vec_get(cmd_lines, i);
	remove_parentheses(ptr);
	if (make_cmd_line_groups(&temp, ptr->str) < 0)
		return (ft_error(""));
	vec_remove(cmd_lines, i);
	j = 0;
	while (j < temp.len)
	{
		if (vec_insert(cmd_lines, vec_get(&temp, j), i) < 0)
			return (ft_error("malloc"));
		j++;
	}
	vec_iter(&temp, free_cmd_line_str);
	vec_free(&temp);
	return (1);
}

void	expand_supergroups(t_vec *cmd_lines)
{
	size_t				i;

//	vec_iter(cmd_lines, set_group_types);
	while (vec_find(cmd_lines, contains_supergroup))
	{
		i = 0;
		while (i < cmd_lines->len)
		{
			if (contains_supergroup(vec_get(cmd_lines, i)))
				handle_supergroup(cmd_lines, i);
			i++;
		}
//		vec_iter(cmd_lines, set_group_types);
	}
}
