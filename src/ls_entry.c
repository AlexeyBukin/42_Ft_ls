/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_entry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:33:37 by hush              #+#    #+#             */
/*   Updated: 2020/03/19 03:31:51 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry				*ls_entry_create(t_dirent *dirent)
{
	t_entry			*entry;

	ls_nullptr(dirent);
	entry = (t_entry*)malloc(sizeof(t_entry));
	ls_nullptr(entry);
	entry->dirent = *dirent;
	entry->name = entry->dirent.d_name;
	entry->full_name = NULL;
	entry->group = NULL;
	entry->owner = NULL;
	entry->size_str = NULL;
	entry->link_num_str = NULL;
	entry->entry_next = NULL;
	return (entry);
}

t_entry			*ls_entry_list_create(t_input *input, t_ls_order *order)
{
	t_entry		*entry_list;
	t_entry		*entry;
	t_dirent	*dir_ent;

	ls_nullptr(order);
	ls_nullptr(input);
	entry_list = NULL;
	entry = NULL;
	order->dir = opendir(order->name);
	ls_nullptr(order->dir);
	order->list_size = 0;
	while ((dir_ent = readdir(order->dir)) != NULL)
	{
		if (dir_ent->d_name[0] == '.' && input->all == FALSE)
			continue ;
		if (entry_list == NULL)
		{
			ls_nullptr((entry_list = ls_entry_create(dir_ent)));
			entry = entry_list;
		}
		else
		{
			ls_nullptr((entry->entry_next = ls_entry_create(dir_ent)));
			entry = entry->entry_next;
		}
		order->list_size++;
	}
	closedir(order->dir);
	return (entry_list);
}
