#include "ft_ls.h"

int 	stat_needed(t_input *input)
{
	ls_nullptr(input);
	if (input->list == TRUE || input->time == TRUE)
		return (TRUE);
	return (FALSE);
}

/*
** TODO implement order_list_fill_stat(t_ls_order *order_list)
*/

void	order_list_fill_stat(t_ls_order *order_list)
{
	t_passwd	*passwd;
	t_group		*group;
	t_entry		*entry;

	while (order_list != NULL)
	{
		entry = order_list->list;
		while (entry != NULL)
		{
			if (stat(entry->name, &(entry->stat)) != 0)
				ls_unknown_error(errno);
			if ((passwd = getpwuid(entry->stat.st_uid)) != NULL)
				entry->owner = ft_strdup(passwd->pw_name);
			else
				ls_unknown_error(errno);
			if ((group = getgrgid(entry->stat.st_gid)) != NULL)
				entry->group = ft_strdup(group->gr_name);
			else
				ls_unknown_error(errno);
			entry = entry->entry_next;
		}
		order_list = order_list->next;
	}
}

t_ls_order	*order_list_revert(t_ls_order *temp)
{
	t_ls_order		*reversed;
	t_ls_order		*to_do;

	ls_nullptr(temp);
	if (temp->next == NULL)
		return (temp);
	to_do = temp->next;
	reversed = temp;
	reversed->next = NULL;
	while (to_do != NULL)
	{
		temp = to_do;
		to_do = to_do->next;
		temp->next = reversed;
		reversed = temp;
	}
	return (reversed);
}

int		main(int ac, char **av)
{
//	size_t		i = 0;

	t_input		input;
	t_ls_order	*order_list;

	ft_bzero(&input, sizeof(t_input));
	ls_flags(ac, av, &input);

	ls_nullptr((order_list = ls_order_list_create(&input)));
//
//	ft_printf("\n------before sort:\n");
//	print_order_list(order_list);

	if (stat_needed(&input))
		order_list_fill_stat(order_list);

//	print_order_list(order_list);

	//sorting
	ls_nullptr((order_list = ls_order_list_sort(order_list, &input)));

//	ft_printf("\n------after sort:\n");
//	print_order_list(order_list);

	//reverting
	if (input.rev == TRUE)
		ls_nullptr((order_list = order_list_revert(order_list)));

//	ft_printf("\n------after revert>\n");
//	print_order_list(order_list);
//	ft_printf("\n------after revert>\n");


	ls_print(order_list, &input);

//	print_order_list(order_list);
	free_order_list(order_list);
	free(input.order_names);

	return (0);
}
