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
