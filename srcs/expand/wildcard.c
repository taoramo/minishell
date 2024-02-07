#include "minishell.h"

static t_wc	*init_i(t_wc *i)
{
	i->pindex = 0;
	i->sindex = 0;
	i->s_backtrack = -1;
	i->last_wildcard = -1;
	i->next_to_wildcard = -1;
	i->i = 0;
	return (i);
}

void	set_indeces_at_wc(t_wc *i)
{
	i->last_wildcard = i->pindex;
	i->next_to_wildcard = ++i->pindex;
	i->s_backtrack = i->sindex;
}

int	check_rest_p(char *p, size_t pindex)
{
	while (pindex < ft_strlen(p))
	{
		if (p[pindex] != '*')
			return (0);
		pindex++;
	}
	return (1);
}

int	is_wildcard_match(char *s, char *p)
{
	t_wc	i;

	init_i(&i);
	while (i.sindex < ft_strlen(s))
	{
		if (i.pindex < ft_strlen(p) && p[i.pindex] == s[i.sindex])
		{
			++i.pindex;
			++i.sindex;
		}
		else if (i.pindex < ft_strlen(p) && p[i.pindex] == '*')
			set_indeces_at_wc(&i);
		else if (i.last_wildcard == -1)
			return (0);
		else
		{
			i.pindex = i.next_to_wildcard;
			i.sindex = ++i.s_backtrack;
		}
	}
	return (check_rest_p(p, i.pindex));
}

int	expand_star(t_vec *argv)
{
	size_t			i;
	char			path[MAXPATHLEN];
	DIR				*ptr;
	char			**strs;
	struct dirent	*ep;

	ptr = opendir("./");
	if (!ptr)
	{
		ft_putstr_fd("minishell: error opening directory\n", 2);
		return (-1);
	}
	i = 0;
	while (i < argv->len)
	{
		strs = (char **)argv->memory;;
		if (ft_strchr(strs[i], '*'))
		{
			ep = readdir(ptr);
			while (ep)
			{
				if (is_wildcard_match(ep->d_name, strs[i]))
				{
					ft_strlcpy(path, ep->d_name, ep->d_namlen + 1);
					if (vec_insert(argv, &path, i + 1) < 0)
					{
						ft_putstr_fd("minishell: error parsing wildcard\n", 2);
						return (-1);
					}
				}
				ep = readdir(ptr);
			}
			closedir(ptr);
			//vec_remove(argv, i);
		}
		i++;
	}
	return (0);
}

int	main(void)
{
	t_vec	strs;

	vec_split(&strs, "*.c", ' ');
	expand_star(&strs);
	vec_iter(&strs, vec_print_elem_str);
}
