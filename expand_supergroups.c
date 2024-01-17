#include "minishell.h"

void	set_group_types(void *arg)
{
	t_cmd_line	*ptr;
	int			i;

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
}

int	contains_supergroup(void *arg)
{
	t_cmd_line	*ptr;

	ptr = arg;
	if (ptr->type == supergroup)
		return (1);
	else
		return (0);
}

void	free_cmd_line_group_str(void *arg)
{
	t_cmd_line	*ptr;

	ptr = arg;
	free(ptr->str);
}

int	handle_supergroup(t_vec *cmd_lines, int i, int *group_index)
{
	t_vec		temp;
	t_cmd_line	*ptr;
	int			j;

	if (vec_new(&temp, 16, sizeof(t_cmd_line)) < 0)
		ft_error();
	ptr = vec_get(cmd_lines, i);
	remove_parentheses(ptr);
	if (make_cmd_line_groups(&temp, ptr->str, *group_index) < 0)
		ft_error();
	*group_index = *group_index + 1;
	vec_remove(cmd_lines, i);
	while (j < temp.len)
	{
		if (vec_insert(cmd_lines, vec_get(&temp, j), i) < 0)
			ft_error();
		j++;
	}
	vec_iter(&temp, free_cmd_line_group_str);
	vec_free(&temp);
}

int	expand_supergroups(t_vec *cmd_lines)
{
	int					group_index;
	int					i;

	group_index = 1;
	vec_iter(cmd_lines, set_group_types);
	while (vec_find(cmd_lines, contains_supergroup))
	{
		i = 0;
		while (i < cmd_lines->len)
		{
			if (contains_supergroup(vec_get(cmd_lines, i)))
				handle_supergroup(cmd_lines, i, &group_index);
			i++;
		}
		vec_iter(cmd_lines, set_group_types);
	}
}
