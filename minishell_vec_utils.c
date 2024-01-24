#include "includes/minishell.h"

int	contains_supergroup(void *arg)
{
	t_cmd_line	*ptr;
	int			i;

	ptr = arg;
	i = 0;
	while (ptr->str[i])
	{
		if (ptr->str[i] == '(')
			return (1);
		i++;
	}
	return (0);
}

void	free_cmd_line_str(void *arg)
{
	t_cmd_line	*ptr;

	ptr = arg;
	free(ptr->str);
}

void	print_cmd_line(void *arg)
{
	t_cmd_line	*ptr;

	ptr = arg;
	printf("String:%s\n", ptr->str);
}
