#include "minishell.h"

int	too_many_arguments(void)
{
	const char	str[] = "minishell: exit: too many arguments\n";

	write(2, str, ft_strlen(str));
	return (255);
}

int	calculate_exit(t_vec *argv)
{
	int		i;
	char	*arg;

	arg = *(char **)vec_get(argv, 1);
	i = 0;
	if (argv->len > 2)
		return (too_many_arguments());
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
