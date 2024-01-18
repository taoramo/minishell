#include "../libft/libft.h"

#include <stdlib.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	handle_input(char *line);

int	execute_parentheses(char *line, void (*f)(char *line))
{
	int	i;
	int	open_parentheses;

	i = 1;
	open_parentheses = 1;
	while (line[i] != 0)
	{
		if (line[i] == '(')
			open_parentheses++;
		if (line[i] == ')')
		{
			open_parentheses--;
			if (open_parentheses == 0)
			{
				f(ft_substr(line, 1, i - 1));
				return (i);
			}
		}
		i++;
	}
	return (0);
}

void	handle_input(char *line)
{
	int i = 0;
	int skip = 0;
	while (line[i] != 0)
	{
		if (line[i] == '(')
		{
			skip = execute_parentheses(&line[i], &handle_input);
			if (skip != 0)
				i += skip;
		}
		i++;
	}
	printf("Executing: %s\n", line);
}

int	main(int argc, char **argv, char *envp[])
{
	char	*line;

	while (1)
	{
		line = readline("minishelll> ");
		handle_input(line);
		free(line);
	}
	return (0);
}