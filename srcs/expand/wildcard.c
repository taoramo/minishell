#include "minishell.h"

static int	exp_wc_err(t_vec *new, char *msg)
{
	free_split_vec(new);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	push_expanded(t_vec *dst, char **strs, int i)
{
	DIR				*ptr;
	struct dirent	*ep;
	char			*path;

	ptr = opendir("./");
	if (!ptr)
		return (exp_wc_err(dst, "error opening directory"));
	ep = readdir(ptr);
	while (ep)
	{
		if (is_wildcard_match(ep->d_name, strs[i]))
		{
			path = ft_strdup(ep->d_name);
			if (!path)
				return (exp_wc_err(dst, "error allocating memory"));
			if (vec_push(dst, &path) < 0)
				return (exp_wc_err(dst, "error parsing wildcard"));
		}
		ep = readdir(ptr);
	}
	closedir(ptr);
	return (1);
}

int	push_argv_elem(t_vec *dst, t_vec *argv, int i)
{
	char			*str;

	str = strdup((char *)vec_get(argv, i));
	if (!str)
		return (exp_wc_err(dst, "error allocating memory"));
	if (vec_push(dst, str) < 0)
		return (exp_wc_err(dst, "error allocating memory"));
	return (0);
}

int	expand_star(t_vec *argv)
{
	t_vec			new;
	size_t			i;
	char			**strs;

	if (vec_new(&new, 32, sizeof(char *)) < 0)
		return (ft_error("minishell: error allocating memory\n"));
	i = 0;
	while (i < argv->len)
	{
		strs = (char **)argv->memory;
		if (ft_strchr(strs[i], '*'))
		{
			if (push_expanded(&new, strs, i) < 0)
				return (ft_error("minishell: error creaing argv\n"));
		}
		else if (push_argv_elem(&new, argv, i) < 0)
			return (-1);
		i++;
	}
	free_split_vec(argv);
	ft_memcpy(argv, &new, sizeof(t_vec));
	return (0);
}

/* int	ft_error(char *str)
{
	if (ft_strlen(str))
	{
		printf("%s\n", str);
	}
	return (-1);
}

int	main(void)
{
	t_vec	strs;
	t_vec	new;

	vec_split(&strs, "*.c *.o", ' ');
	expand_star(&new, &strs);
	vec_iter(&new, vec_print_elem_str);
} */
