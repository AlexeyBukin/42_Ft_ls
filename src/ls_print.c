/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:46:58 by hush              #+#    #+#             */
/*   Updated: 2020/12/03 22:25:07 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_print_order(t_ls_order *order, t_input *input, t_bool is_first,
															char *str_rwx)
{
	t_entry		*entry;
	t_ls_max	max_len;
	size_t		dirsize;

	if (order == NULL || input == NULL || str_rwx == NULL)
		return ;
	ls_print_order_header(order, input, is_first);
	entry = order->list;
	dirsize = 0;
	ft_bzero(&max_len, sizeof(t_ls_max));
	while (entry != NULL)
	{
		ls_print_order_entry_helper(entry, &max_len, &dirsize);
		entry = entry->entry_next;
	}
	if (order->list != NULL && order->is_dir == TRUE)
		ft_printf("total %llu\n", dirsize);
	entry = order->list;
	while (entry != NULL)
	{
		ls_print_order_helper(entry, &max_len, input, str_rwx);
		entry = entry->entry_next;
	}
}

void	print_plain_helper(t_ls_order *order_list, t_entry **entry)
{
	if (order_list->error == E_LS_NONE)
	{
		*entry = order_list->list;
		while (*entry != NULL)
		{
			ft_printf("%s\n", (*entry)->name);
			*entry = (*entry)->entry_next;
		}
	}
	else if (order_list->error == E_LS_PERMISSION_DENIED)
	{
		ft_printf("ft_ls: %s: Permission denied\n", order_list->name);
	}
}

void	ls_print_plain(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	t_entry		*entry;

	is_first = TRUE;
	ls_nullptr(order_list);
	while (order_list != NULL)
	{
		// ft_printf("%d\n", order_list->error);
		if (order_list->error != E_LS_NO_SUCH_FILE)
		{
			if (is_first == FALSE)
				ft_printf("\n");
			if ((input->order_num > 1 ||
			(input->rec == TRUE && is_first == FALSE))
			&& order_list->is_dir == TRUE)
				ft_printf("%s:\n", order_list->name);
		}
		print_plain_helper(order_list, &entry);
		is_first = FALSE;
		order_list = order_list->next;
	}
}

void	ls_print(t_ls_order *order_list, t_input *input)
{
	ls_nullptr(input);
	if (input->list == TRUE)
	{
		// ft_printf("here\n");
		ls_print_list(order_list, input);
	}
	else
	{
		// ft_printf("plain\n");
		ls_print_plain(order_list, input);
	}
}
