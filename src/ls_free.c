/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:44:24 by hush              #+#    #+#             */
/*   Updated: 2020/03/19 03:32:04 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_print_list(t_print *print)
{
	free(print->time_str);
	free(print->links_str);
	free(print->bytes_str);
	free(print->ownername);
	free(print->groupname);
}

void	free_entry_list(t_entry *e_list)
{
	t_entry *temp;

	temp = e_list;
	while (e_list != NULL)
	{
		free(e_list->full_name);
		free(e_list->owner);
		free(e_list->group);
		free(e_list->link_num_str);
		free(e_list->size_str);
		temp = e_list->entry_next;
		free(e_list);
		e_list = temp;
	}
	free(e_list);
}

void	free_order_list(t_ls_order *order_list)
{
	t_ls_order *tmp_ord;

	tmp_ord = order_list;
	while (order_list != NULL)
	{
		free_entry_list(tmp_ord->list);
		tmp_ord = order_list->next;
		free(order_list);
		order_list = tmp_ord;
	}
}
