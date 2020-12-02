/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:44:24 by hush              #+#    #+#             */
/*   Updated: 2020/12/02 01:34:47 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	free_entry_list(t_entry *e_list, t_bool flag_list)
{
	t_entry		*temp;

	while (e_list != NULL)
	{
		free(e_list->full_name);
		free(e_list->owner);
		free(e_list->group);
		free(e_list->link_num_str);
		free(e_list->size_str);
		if (e_list->dirent.d_type == DT_LNK && flag_list == TRUE)
			free(e_list->name);
		temp = e_list->entry_next;
		free(e_list);
		e_list = temp;
	}
	free(e_list);
}

void	free_order_list(t_ls_order *order_list, t_bool flag_list)
{
	t_ls_order		*tmp_ord;

	while (order_list != NULL)
	{
		free_entry_list(order_list->list, flag_list);
		tmp_ord = order_list->next;
		free(order_list->name);
		free(order_list);
		order_list = tmp_ord;
	}
}

void	free_order_list_struct_only(t_ls_order *order_list)
{
	t_ls_order		*tmp_ord;

	while (order_list != NULL)
	{
		tmp_ord = order_list->next;
		free(order_list->name);
		free(order_list);
		order_list = tmp_ord;
	}
}
