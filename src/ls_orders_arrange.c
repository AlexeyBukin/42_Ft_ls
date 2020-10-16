/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders_arrange.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 16:23:08 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/16 19:06:56 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_order			*ls_monofiles_to_plain(t_ls_order *mono_list)
{
	t_ls_order		*free_me;
	t_ls_order		*monofiles;
	t_entry			*monofiles_ent;

	if (mono_list == NULL)
		return (NULL);
	ls_nullptr(monofiles = ls_order_malloc(ft_strdup("monofiles")));
	monofiles_ent = NULL;
	free_me = mono_list;
	while(mono_list != NULL)
	{
		if (monofiles_ent == NULL)
		{
			monofiles_ent = mono_list->list;
			monofiles->list = monofiles_ent;
		}
		else
		{
			monofiles_ent->entry_next = mono_list->list;
			monofiles_ent = monofiles_ent->entry_next;
		}
		mono_list = mono_list->next;
	}
	free_order_list_struct_only(free_me);
	return (monofiles);
}

void				ls_order_list_arrange_list(t_ls_order **mfiles,
						t_ls_order **mfiles_tmp, t_ls_order **tmp)
{
	if (mfiles == NULL || mfiles_tmp == NULL || tmp == NULL)
		return;
	if (*mfiles_tmp == NULL) {
		*mfiles = *tmp;
		*mfiles_tmp = *tmp;
	} else {
		(*mfiles_tmp)->next = *tmp;
		(*mfiles_tmp) = (*mfiles_tmp)->next;
	}
	*tmp = (*tmp)->next;
	(*mfiles_tmp)->next = NULL;
}

static size_t entry_list_len(t_entry *entry_list)
{
	size_t		len;

	len = 0;
	while (entry_list != NULL)
	{
		entry_list = entry_list->entry_next;
		len ++;
	}
	return (len);
}

t_ls_order			*ls_order_list_arrange(t_ls_order *order_list)
{
	t_ls_order		*mono_files_list;
	t_ls_order		*mono_files_tmp;
	t_ls_order		*order_list_tmp;
	t_ls_order		*tmp;

	tmp = order_list;
	order_list = NULL;
	order_list_tmp = NULL;
	mono_files_list = NULL;
	mono_files_tmp = NULL;
	while (tmp != NULL)
	{
		if (tmp->is_dir == FALSE)
			ls_order_list_arrange_list(&mono_files_list, &mono_files_tmp, &tmp);
		else
			ls_order_list_arrange_list(&order_list, &order_list_tmp, &tmp);
	}
	mono_files_list = ls_monofiles_to_plain(mono_files_list);
	if (mono_files_list != NULL)
	{
		mono_files_list->list_size = entry_list_len(mono_files_list->list);
		mono_files_list->next = order_list;
	}
	else
		mono_files_list = order_list;
	return (mono_files_list);
}
