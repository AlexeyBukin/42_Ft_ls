/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls__print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:46:58 by hush              #+#    #+#             */
/*   Updated: 2020/03/15 21:20:09 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_order_list(t_ls_order *order_list)
{
	t_ls_order *tmp_ord = order_list;
	while (tmp_ord != NULL)
	{
		ft_printf("main dir : %s, p=%p, next=%p\n", tmp_ord->name, tmp_ord, tmp_ord->next);
		t_entry *temp = tmp_ord->list;
		while (temp != NULL)
		{
			ft_printf("     ent : \'%20s\', p=%p, next=%p\n", temp->name, temp, temp->entry_next);
			temp = temp->entry_next;
		}
		tmp_ord = tmp_ord->next;
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


void	ls_print_list(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	t_entry		*entry;

	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (is_first == FALSE)
			ft_printf("\n");
		else
			is_first = FALSE;

		if (order_list->error == 0)
		{
			if (input->current_dir == FALSE)
				ft_printf("%s: curdir=%d\n", order_list->name, input->current_dir);
			entry = order_list->list;
			while (entry != NULL)
			{
				ft_printf("%s\n", entry->name);
				entry = entry->entry_next;
			}
			ft_printf("\n", order_list->name);
		}
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
		else
			is_first = FALSE;

		if (order_list->error == 0)
		{
			if (input->current_dir == FALSE)
				ft_printf("%s: curdir=%d\n", order_list->name, input->current_dir);
			entry = order_list->list;
			while (entry != NULL)
			{
				ft_printf("%s\n", entry->name);
				entry = entry->entry_next;
			}
			ft_printf("\n", order_list->name);
		}
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