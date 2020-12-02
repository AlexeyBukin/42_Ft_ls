/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_entry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:33:37 by hush              #+#    #+#             */
/*   Updated: 2020/12/01 23:19:42 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_entry			*ls_entry_create(t_dirent *dirent)
{
	t_entry		*entry;

	ls_nullptr(dirent);
	entry = (t_entry*)ft_memalloc(sizeof(t_entry));
	ls_nullptr(entry);
	entry->dirent = *dirent;
	entry->name = entry->dirent.d_name;
	entry->full_name = NULL;
	entry->group = NULL;
	entry->owner = NULL;
	entry->size_str = NULL;
	entry->link_num_str = NULL;
	entry->entry_next = NULL;
	entry->attr = LS_ATTR_NO;
	return (entry);
}

void			ls_entry_list_create_helper(t_entry **entry,
					t_entry **entry_set, t_dirent *dir_ent)
{
	ls_nullptr((*entry_set = ls_entry_create(dir_ent)));
	*entry = *entry_set;
}

int				ls_do_not_create(char *name, t_input *input)
{
	ls_nullptr2(name, input);
	if (input->show == SHOW_VISIBLE)
	{
		if (name[0] == '.')
			return (1);
	}
	if (input->show == SHOW_HIDDEN)
	{
		if (ft_strequ(name, ".") || ft_strequ(name, ".."))
			return (1);
	}
	return (0);
}

t_entry			*ls_entry_list_create(t_input *input, t_ls_order *order)
{
	t_entry		*entry_list;
	t_entry		*entry;
	t_dirent	*dir_ent;

	ls_nullptr2(order, input);
	entry_list = NULL;
	entry = NULL;
	if ((order->dir = opendir(order->name)) == NULL)
	{
		ls_order_error(order, E_LS_PERMISSION_DENIED);
		return (ls_entry_nameonly(order->name));
	}
	order->list_size = 0;
	while ((dir_ent = readdir(order->dir)) != NULL)
	{
		if (ls_do_not_create(dir_ent->d_name, input))
			continue ;
		if (entry_list == NULL)
			ls_entry_list_create_helper(&entry, &entry_list, dir_ent);
		else
			ls_entry_list_create_helper(&entry, &(entry->entry_next), dir_ent);
		order->list_size++;
	}
	closedir(order->dir);
	return (entry_list);
}

t_entry			*ls_entry_nameonly(char *name)
{
	t_entry		*entry;

	ls_nullptr(name);
	entry = (t_entry*)ft_memalloc(sizeof(t_entry));
	ls_nullptr(entry);
	entry->dirent.d_type = DT_REG;
	entry->name = name;
	entry->full_name = NULL;
	entry->group = NULL;
	entry->owner = NULL;
	entry->size_str = NULL;
	entry->link_num_str = NULL;
	entry->entry_next = NULL;
	entry->attr = LS_ATTR_NO;
	return (entry);
}
