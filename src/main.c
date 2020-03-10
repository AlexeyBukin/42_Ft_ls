#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_input		input;
	t_entry		**entries;

	if (ls_get_flags(ac, av, &input) != LS_OK)
	{
		// print error
		return (0);
	}

	if (input.rec == TRUE)
		entries = ls_ent_get_rec(input.ent_names, &input);
	else
		entries = ls_ent_get(input.ent_names, &input);

	entries = ls_ent_sort(entries, &input);

	if (input.list == TRUE)
	{
		entries = ls_get_rights(entries);
		ls_print_long(entries, &input);
	}
	else
	{
		ls_print_short(entries, &input);
	}


	return (0);
}


//int					ls_is_unreachable(char *ent_name)
//{
//	struct stat info;
//
//	if (ent_name == NULL)
//		return (E_LS_NULL_POINTER);
//	if (stat(ent_name, &info) != 0)
//	{
//		if (errno == ENOENT)
//		{
//			return (E_LS_NO_SUCH_FILE);
//		}
//		else if (errno == EACCES)
//		{
//			return (E_LS_PERMISSION_DENIED);
//		}
//		return (E_LS_UNKNOWN_ERROR);
//	}
//	return (LS_OK);
//}
