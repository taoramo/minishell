#include "minishell.h"

int	calculate_exit(t_vec *argv)
{
	int		i;
	char	*arg;

	arg = *(char **)vec_get(argv, 1);
	i = 0;
	while (arg[i])
	{
		if (i == 0 && arg[i] == '-')
			i++;
		if (!arg[i] || !ft_isdigit(arg[i]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, arg, ft_strlen(arg));
			write(2, ": numeric argument required\n", 28);
			return (255);
		}
		i++;
	}
	return ((INT_MIN + (ft_atoi(arg) & 255)));
}
