#include "ft_ls.h"

void	print_flags(t_input *input)
{
	printf("R = %c\n", input->rec + '0');
	printf("a = %c\n", input->all + '0');
	printf("l = %c\n", input->list + '0');
	printf("r = %c\n", input->rev + '0');
	printf("t = %c\n", input->time + '0');
}

int		main(int ac, char **av)
{
//	int			res;
	t_input		input;
	t_entry		**entries;
	t_entry		*en;

	ls_get_flags(ac, av, &input);

//	printf("dirnum = %lu\n", input.ent_num );
//	size_t i = 0;
//	while (input.ent_names[i] != NULL)
//	{
//		printf(" dir %s\n", input.ent_names[i]);
//		i++;
//	}
//	print_flags(&input);

	size_t i = 0;
	ls_nullptr((entries = ls_ent_get(&input)));
	//ft_putstr("back in main!\n");
	i = 0;

	while (entries[i] != NULL)
	{
		en = entries[i];
		if (entries[i]->error != E_LS_NO_SUCH_FILE)
			ft_printf("%s:\n", entries[i]->name);
		if (entries[i]->error != LS_OK)
		{
//			if (entries[i]->error == E_LS_NO_SUCH_FILE)
//			{
//				ft_putstr("ft_ls: ");
//				ft_putstr(entries[i]->name);
//				ft_putstr(": No such file or directory\n");
//			}
//			else
			if (entries[i]->error == E_LS_PERMISSION_DENIED)
			{
				ft_putstr("ft_ls: ");
				ft_putstr(entries[i]->name);
				ft_putstr(": Permission denied");
//				if (entries[i + 1] != NULL)
//					if (entries[i + 1]->error != E_LS_NO_SUCH_FILE)
//						ft_putstr("\n");
			}
			//ft_putstr("some err\n");
		}
		//ls_nullptr(en->next);
		while ((en = en->next) != NULL)
		{
			ft_printf("%s \t", en->name);
		}
//		ft_putstr("\n");

		t_bool is_last = TRUE;
		size_t new_i = i;
		while (entries[new_i] != NULL)
		{
			if (entries[new_i]->error != E_LS_NO_SUCH_FILE)
				is_last = FALSE;
			new_i++;
		}

		if (is_last == FALSE)
		{
			ft_putstr("\n");
		}

		i++;
	}
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
