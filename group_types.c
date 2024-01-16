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
