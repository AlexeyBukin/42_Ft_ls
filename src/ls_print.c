/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls__print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:46:58 by hush              #+#    #+#             */
/*   Updated: 2020/07/25 14:03:04 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls_print_list2(t_entry *entry, t_sizes sizes)
{
	t_print		print;
	char		str_rwx[11];

	str_rwx[10] = '\0';
	while (entry != NULL)
	{
		ls_nullptr((ls_rwx(entry, str_rwx)));
		print.time_str = ft_strsub(ctime(&entry->stat.st_mtime), 4, 12);
		print.links_str = ft_strf_width(entry->link_num_str,
								sizes.max_len_links, ' ', FALSE);
		print.bytes_str = ft_strf_width(entry->size_str,
								sizes.max_len_size, ' ', FALSE);
		print.ownername = ft_strf_width(entry->owner,
					sizes.max_len_owner, ' ', TRUE);
		print.groupname = ft_strf_width(entry->group,
							sizes.max_len_group, ' ', TRUE);
		ft_printf("%s  %s %s  %s  %s %s %s\n", str_rwx, print.links_str,
			print.ownername, print.groupname,
			print.bytes_str, print.time_str, entry->name);
		free_print_list(&print);
		entry = entry->entry_next;
	}
}

void			ls_print_list4(t_entry *entry, t_sizes sizes)
{
	if (sizes.len > sizes.max_len_owner)
		sizes.max_len_owner = sizes.len;
	sizes.len = ft_strlen(entry->group);
	if (sizes.len > sizes.max_len_group)
		sizes.max_len_group = sizes.len;
	entry->link_num_str = ft_ulltoa(
		(unsigned long)entry->stat.st_nlink);
	sizes.len = ft_strlen(entry->link_num_str);
	if (sizes.len > sizes.max_len_links)
		sizes.max_len_links = sizes.len;
}

void			ls_print_list3(t_ls_order *order_list, t_entry *entry)
{
	t_sizes		sizes;

	sizes.dirsize = 0;
	sizes.max_len_owner = 0;
	sizes.max_len_group = 0;
	sizes.max_len_size = 0;
	sizes.max_len_links = 0;
	sizes.len = 0;
	while (entry != NULL)
	{
		sizes.len = ft_strlen(entry->owner);
		ls_print_list4(entry, sizes);
		entry->size_str = ft_ulltoa((unsigned long)entry->stat.st_size);
		sizes.len = ft_strlen(entry->size_str);
		if (sizes.len > sizes.max_len_size)
			sizes.max_len_size = sizes.len;
		sizes.dirsize += entry->stat.st_blocks;
		entry = entry->entry_next;
	}
	ft_printf("total %llu\n", sizes.dirsize);
	entry = order_list->list;
	ls_print_list2(entry, sizes);
}

void			ls_print_list(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	t_entry		*entry;

	(void)input;
	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (order_list->error == 0)
		{
			if (is_first == FALSE)
				ft_printf("\n");
			is_first = FALSE;
			if (input->order_num > 1 || input->rec == TRUE)
				ft_printf("%s:\n", order_list->name);
			entry = order_list->list;
			ls_print_list3(order_list, entry);
		}
		order_list = order_list->next;
	}
}

void			ls_print_plain(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	t_entry		*entry;

	(void)input;
	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (is_first == FALSE)
			ft_printf("\n");
		is_first = FALSE;
		if (order_list->error == 0)
		{
			if (input->order_num > 1 || input->rec == TRUE)
				ft_printf("%s:\n", order_list->name);
			entry = order_list->list;
			while (entry != NULL)
			{
				ft_printf("%s  ", entry->name);
				entry = entry->entry_next;
			}
			ft_printf("\n", order_list->name);
		}
		order_list = order_list->next;
	}
}
