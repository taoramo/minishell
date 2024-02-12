/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:10:29 by toramo            #+#    #+#             */
/*   Updated: 2024/02/09 17:10:30 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exp_wc_err(t_vec *new, char *msg)
{
	free_split_vec(new);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int	push_matches(t_vec *dst, char **strs, int i, DIR *ptr)
{
	struct dirent	*ep;
	int				j;
	char			*path;

	ep = readdir(ptr);
	j = 0;
	while (ep)
	{
		if (is_wildcard_match(ep->d_name, strs[i]))
		{
			path = ft_strdup(ep->d_name);
			if (!path)
				return (exp_wc_err(dst, "error allocating memory"));
			if (vec_push(dst, &path) < 0)
				return (exp_wc_err(dst, "error parsing wildcard"));
			j++;
		}
		ep = readdir(ptr);
	}
	closedir(ptr);
	if (!j)
		vec_push(dst, &strs[i]);
	else
		free(strs[i]);
	return (0);
}

int	push_expanded(t_vec *dst, char **strs, int i)
{
	DIR				*ptr;
	struct dirent	*ep;

	ptr = opendir("./");
	ep = readdir(ptr);
	ep = readdir(ptr);
	(void)ep;
	if (!ptr)
		return (exp_wc_err(dst, "error opening directory"));
	return (push_matches(dst, strs, i, ptr));
}

int	push_argv_elem(t_vec *dst, t_vec *argv, int i)
{
	char			**strs;

	strs = (char **)argv->memory;
	if (vec_push(dst, &strs[i]) < 0)
		return (exp_wc_err(dst, "error allocating memory"));
	return (0);
}

int	expand_star(t_vec *argv)
{
	t_vec			dst;
	size_t			i;
	char			**strs;

	if (vec_new(&dst, 32, sizeof(char *)) < 0)
		return (ft_error("minishell: error allocating memory"));
	i = 0;
	while (i < argv->len)
	{
		strs = (char **)argv->memory;
		if (ft_strchr(strs[i], '*'))
		{
			if (push_expanded(&dst, strs, i) < 0)
				return (ft_error("minishell: error creaing argv"));
		}
		else if (push_argv_elem(&dst, argv, i) < 0)
			return (-1);
		i++;
	}
	vec_free(argv);
	ft_memcpy(argv, &dst, sizeof(t_vec));
	return (0);
}
