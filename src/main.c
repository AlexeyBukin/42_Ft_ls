#include "ft_ls.h"

int 	stat_needed(t_input *input)
{
	ls_nullptr(input);
	if (input->list == TRUE || input->time == TRUE)
		return (TRUE);
	return (FALSE);
}

void	order_list_fill_stat(t_ls_order *order_list)
{
	(void)order_list;
}

int		main(int ac, char **av)
{
//	size_t		i = 0;

	t_input		input;
	t_ls_order	*order_list;

	ft_bzero(&input, sizeof(t_input));
	ls_flags(ac, av, &input);

	ls_nullptr((order_list = ls_order_list_create(&input)));

	ft_printf("\n------before sort:\n");
	print_order_list(order_list);

	if (stat_needed(&input))
		order_list_fill_stat(order_list);

	ls_nullptr((order_list = ls_order_list_sort(order_list, &input)));

	ft_printf("\n------after sort:\n");
	print_order_list(order_list);

//	ls_print(order_list);

//	print_order_list(order_list);
	free_order_list(order_list);
	free(input.order_names);

	return (0);
}
