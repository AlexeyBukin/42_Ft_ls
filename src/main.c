#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_flags		flags;
	t_entry		**entries;

	(void)av;
	(void)ac;
	if (ls_get_flags(ac, av, &flags) < 0)
	{
		// print error
		return (0);
	}

	if (flags.rec == TRUE)
		entries = ls_ent_get_rec(flags.dirs, &flags);
	else
		entries = ls_ent_get(flags.dirs, &flags);

	entries = ls_ent_sort(entries, &flags);

	if (flags.list == TRUE)
	{
		entries = ls_get_rights(entries);
		ls_print_long(entries, &flags);
	}
	else
	{
		ls_print_short(entries, &flags);
	}

	return (0);
}