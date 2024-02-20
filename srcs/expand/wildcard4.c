/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpatsi <hpatsi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:13:54 by toramo            #+#    #+#             */
/*   Updated: 2024/02/19 10:09:02 by hpatsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	push_matches(t_vec *dst, char *arg, DIR *ptr, int redirect)
{
	struct dirent	*ep;
	int				j;
	char			*path;

	ep = readdir(ptr);
	j = 0;
	while (ep)
	{
		if (is_wildcard_match(ep->d_name, arg))
		{
			path = ft_strdup(ep->d_name);
			if (!path)
				return (exp_wc_err(dst, "error allocating memory"));
			if (!j && redirect && vec_push(dst, &path) < 0)
				return (exp_wc_err(dst, "error allocating memory"));
			if (j > 0 && redirect)
				return (ambiguous_wildcard(arg));
			if (!redirect && ft_strlen(path) && vec_push(dst, &path) < 0)
				return (exp_wc_err(dst, "error parsing wildcard"));
			j++;
		}
		ep = readdir(ptr);
	}
	closedir(ptr);
	return (after_wildcard_pushing(dst, arg, j, redirect));
}

int	skip_redirect(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && (arg[i] == '<' || arg[i] == '>' || ft_isdigit(arg[i])))
		i++;
	return (i);
}

int	add_redirect_str(t_vec *dst, char *arg)
{
	char	*redirect;
	char	**last;
	char	*str;

	last = (char **)vec_get(dst, dst->len - 1);
	redirect = ft_substr(arg, 0, skip_redirect(arg));
	if (!redirect)
		return (-1);
	str = ft_strjoin(redirect, *last);
	free(redirect);
	free(*last);
	*last = str;
	return (0);
}

int	push_expanded(t_vec *dst, char **strs, int i)
{
	DIR				*ptr;
	int				redirect;
	int				result;

	ptr = opendir("./");
	readdir(ptr);
	readdir(ptr);
	if (!ptr)
		return (exp_wc_err(dst, "error opening directory"));
	redirect = is_rdrct(strs[i]);
	if (redirect)
		result = push_matches(dst,
				&strs[i][skip_redirect(strs[i])], ptr, redirect);
	else
		result = push_matches(dst, strs[i], ptr, redirect);
	if (redirect && result == 1 && add_redirect_str(dst, strs[i]) < 0)
		return (ft_error("minishell: memory error"));
	if (redirect && result == 0 && vec_push(dst, &strs[i]) < 0)
		return (ft_error("minishell: memory error"));
	return (result);
}
