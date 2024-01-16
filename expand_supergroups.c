#include "minishell.h"

void	set_group_types(void *arg)
{
	t_cmd_line_group	*ptr;
	int					i;

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
	t_cmd_line_group	*ptr;

	ptr = arg;
	if (ptr->type == supergroup)
		return (1);
	else
		return (0);
}

void	free_cmd_line_group_str(void *arg)
{
	t_cmd_line_group	*ptr;

	ptr = arg;
	free(ptr->str);
}

int	handle_supergroup(t_vec *cmd_line_groups, int i, int *group_index)
{
	t_vec				temp;
	t_cmd_line_group	*ptr;
	int					j;

	if (vec_new(&temp, 16, sizeof(t_cmd_line_group)) < 0)
		ft_error();
	if (make_cmd_line_groups(&temp, ptr->str, *group_index) < 0)
		ft_error();
	*group_index = *group_index + 1;
	vec_remove(cmd_line_groups, i);
	while (j < temp.len)
	{
		vec_insert(cmd_line_groups, vec_get(&temp, i), i);
		j++;
	}
	vec_iter(&temp, free_cmd_line_group_str);
	vec_free(&temp);
}

int	expand_supergroups(t_vec *cmd_line_groups)
{
	int					group_index;
	int					i;

	group_index = 1;
	vec_iter(cmd_line_groups, set_group_types);
	while (vec_find(cmd_line_groups, contains_supergroup))
	{
		i = 0;
		while (i < cmd_line_groups->len)
		{
			if (contains_supergroup(vec_get(cmd_line_groups, i)))
				handle_supergroup(cmd_line_groups, i, &group_index);
			i++;
		}
		vec_iter(cmd_line_groups, set_group_types);
	}
}
