#include "ft_ls.h"

int 	stat_needed(t_input *input)
{
	ls_nullptr(input);
	if (input->list == TRUE || input->time_sort == TRUE)
		return (TRUE);
	return (FALSE);
}

t_entry			*entry_list_reverse(t_entry *temp)
{
	t_entry		*reversed;
	t_entry		*to_do;

	ls_nullptr(temp);
	if (temp->entry_next == NULL)
		return (temp);
	to_do = temp->entry_next;
	reversed = temp;
	reversed->entry_next = NULL;
	while (to_do != NULL)
	{
		temp = to_do;
		to_do = to_do->entry_next;
		temp->entry_next = reversed;
		reversed = temp;
	}
	return (reversed);
}

t_ls_order	*order_list_revert(t_ls_order *temp)
{
	t_ls_order		*reversed;
	t_ls_order		*to_do;

	ls_nullptr(temp);
	ls_nullptr(temp->list = entry_list_reverse(temp->list));
	if (temp->next == NULL)
		return (temp);
	to_do = temp->next;
	reversed = temp;
	reversed->next = NULL;
	while (to_do != NULL)
	{
		temp = to_do;
		ls_nullptr(to_do->list = entry_list_reverse(to_do->list));
		to_do = to_do->next;
		temp->next = reversed;
		reversed = temp;
	}
	return (reversed);
}

int		main(int ac, char **av)
{
	t_input		input;
	t_ls_order	*order_list;
	t_ls_order	*list_second_elem;

	ft_bzero(&input, sizeof(t_input));
	ls_flags(ac, av, &input);

	ls_nullptr((order_list = ls_order_list_create(&input)));

//
//	ft_printf("\n------before sort:\n");
//	print_order_list(order_list);

	if (stat_needed(&input))
		order_list_fill_stat(order_list, &input);

//	ft_printf("main\n");
	//print_order_list(order_list);
//	ft_printf("\n------after sort:\n");

	list_second_elem = order_list->next;
	order_list->next = NULL;

	//sorting
	ls_nullptr((order_list = ls_order_list_sort(order_list, &input)));
	if (list_second_elem != NULL)
		ls_nullptr((list_second_elem = ls_order_list_sort(list_second_elem, &input)));

//	ft_printf("\n------after sort:\n");
//	print_order_list(order_list);


	//reverting
	if (input.rev == TRUE)
	{
		ls_nullptr(order_list = order_list_revert(order_list));
		if (list_second_elem != NULL)
			ls_nullptr(list_second_elem = order_list_revert(list_second_elem));
	}

	order_list->next = list_second_elem;

	ls_print(order_list, &input);

//	print_order_list(order_list);
	free_order_list(order_list);
	free(input.order_names);

	return (0);
}
