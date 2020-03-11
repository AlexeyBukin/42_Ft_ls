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
//	t_entry		**entries;

	ls_get_flags(ac, av, &input);

	size_t i = 0;
	while (input.ent_names[i] != NULL)
	{
		printf(" dir %s\n", input.ent_names[i]);
		i++;
	}
	print_flags(&input);

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
