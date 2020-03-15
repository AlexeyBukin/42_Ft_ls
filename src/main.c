#include "ft_ls.h"

void	print_order_list(t_ls_order *order_list)
{
	t_ls_order *tmp_ord = order_list;
	while (tmp_ord != NULL)
	{
		ft_printf("main dir : \'%s\', p=%p\n", tmp_ord->name, tmp_ord->name);
		t_entry *temp = tmp_ord->list;
		while (temp != NULL)
		{
			ft_printf("     ent : \'%20s\', p=%p, prev=%p, next=%p\n", temp->name, temp, temp->prev, temp->entry_next);
			temp = temp->entry_next;
		}
		tmp_ord = tmp_ord->next;
	}
}

void	free_entry_list(t_entry *e_list)
{
	t_entry *temp = e_list;
	while (e_list != NULL)
	{
		temp = e_list->entry_next;
		free(e_list);
		e_list = temp;
	}
	free(e_list);
}

void	free_order_list(t_ls_order *order_list)
{
	t_ls_order *tmp_ord = order_list;
	while (order_list != NULL)
	{
		free_entry_list(tmp_ord->list);
		tmp_ord = order_list->next;
		free(order_list);
		order_list = tmp_ord;
	}
}

void	print_flags(t_input *input)
{
	ft_printf("R = %c\n", input->rec + '0');
	ft_printf("a = %c\n", input->all + '0');
	ft_printf("l = %c\n", input->list + '0');
	ft_printf("r = %c\n", input->rev + '0');
	ft_printf("t = %c\n", input->time + '0');
}

int is_first = 1;

int		main(int ac, char **av)
{
size_t i = 0;//	int			res;
	t_input		input;
	t_ls_order	*order_list;
//	t_entry		*en;

	ft_bzero(&input, sizeof(t_input));
	ls_flags(ac, av, &input);

//	ft_printf("dirnum = %lu\n", input.order_num );
//
//	i = 0;
//	while (i < input.order_num)
//	{
//		ft_printf(" dir %s\n", input.order_names[i]);
//		i++;
//	}
//	ft_printf("\n");
//	print_flags(&input);


	i = 0;
	ls_nullptr((order_list = ls_order_list_create(&input)));
//	ft_putstr("back in main!\n");
	i = 0;

	print_order_list(order_list);
	free_order_list(order_list);
	free(input.order_names);

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
