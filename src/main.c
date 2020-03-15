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
//	size_t		i = 0;

	t_input		input;
	t_ls_order	*order_list;

	ft_bzero(&input, sizeof(t_input));
	ls_flags(ac, av, &input);

	ls_nullptr((order_list = ls_order_list_create(&input)));
//	ls_nullptr((order_list = ls_order_list_sort(order_list)));
//	ls_print(order_list);

	print_order_list(order_list);
	free_order_list(order_list);
	free(input.order_names);

	return (0);
}
