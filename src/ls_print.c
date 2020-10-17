/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls__print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:46:58 by hush              #+#    #+#             */
/*   Updated: 2020/10/17 18:47:20 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_print_order(t_ls_order *order, t_input *input, t_bool *is_first,
															char *str_rwx)
{
	t_entry		*entry;
	t_ls_max	max_len;
	size_t		dirsize;

	if (order == NULL || input == NULL || str_rwx == NULL || is_first == NULL)
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

void	ls_print_list(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	char		str_rwx[12];

	str_rwx[11] = '\0';
	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (order_list->error == 0)
			ls_print_order(order_list, input, &is_first, str_rwx);
		order_list = order_list->next;
	}
}

void	ls_print_plain(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	t_entry		*entry;

	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (is_first == FALSE)
			ft_printf("\n");
		if (order_list->error == 0)
		{
			if ((input->order_num > 1 ||
			(input->rec == TRUE && is_first == FALSE))
			&& order_list->is_dir == TRUE)
				ft_printf("%s:\n", order_list->name);
			entry = order_list->list;
			while (entry != NULL)
			{
				ft_printf("%s\n", entry->name);
				entry = entry->entry_next;
			}
		}
		is_first = FALSE;
		order_list = order_list->next;
	}
}

void	ls_print(t_ls_order *order_list, t_input *input)
{
	ls_nullptr(input);
	if (input->list == TRUE)
		ls_print_list(order_list, input);
	else
		ls_print_plain(order_list, input);
}
