/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:44:24 by hush              #+#    #+#             */
/*   Updated: 2020/03/15 18:44:24 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
