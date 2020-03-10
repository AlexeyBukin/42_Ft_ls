#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_input		input;
	t_entry		**entries;

	(void)input;
	(void)ac;
	(void)av;
	(void)entries;
//	if (ls_get_flags(ac, av, &input) < 0)
//	{
//		// print error
//		return (0);
//	}
//
//	if (input.rec == TRUE)
//		entries = ls_ent_get_rec(input.ent_names, &input);
//	else
//		entries = ls_ent_get(input.ent_names, &input);
//
//	entries = ls_ent_sort(entries, &input);
//
//	if (input.list == TRUE)
//	{
//		entries = ls_get_rights(entries);
//		ls_print_long(entries, &input);
//	}
//	else
//	{
//		ls_print_short(entries, &input);
//	}


	return (0);
}