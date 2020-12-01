/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders_create_rec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:38:26 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/02 00:20:20 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ls_order_create_rec_helper(t_entry *entry,
						t_ls_order **order, char *order_name, t_input *input)
{
	while (entry != NULL)
	{
		if (ft_strcmp(entry->name, ".") != 0 &&
				ft_strcmp(entry->name, "..") != 0)
		{
			(*order)->next = ls_order_create_rec(input,
								ft_strjoin_3(order_name, "/", entry->name));
			if ((*order)->next->error == E_LS_PLAIN_FILE)
			{
				free_order_list((*order)->next);
				(*order)->next = NULL;
			}
			while ((*order)->next != NULL)
				*order = (*order)->next;
		}
		entry = entry->entry_next;
	}
}

t_ls_order			*ls_order_create_rec(t_input *input, char *order_name)
{
	t_ls_order		*order;
	t_ls_order		*order_rec;

	ls_nullptr((order_rec = ls_order_create(input, order_name)));
	if (order_rec->is_dir == FALSE && order_rec->error == E_LS_NONE)
	{
		order_rec->error = E_LS_PLAIN_FILE;
		return (order_rec);
	}
	order = order_rec;
	if (order_rec->is_dir == TRUE)
	{
		ls_order_create_rec_helper(order->list, &order, order_name, input);
	}
	return (order_rec);
}
