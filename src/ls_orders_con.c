/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders_con.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:43:32 by gekans            #+#    #+#             */
/*   Updated: 2020/08/25 15:43:35 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_order			*ls_order_list_create(t_input *input)
{
	t_ls_order		*order_list;

	order_list = NULL;
	if (input->rec == TRUE)
		return (ls_order_list_create_rec(input, order_list));
	return (ls_order_list_create_plain(input, order_list));
}

void				order_list_fill_stat2(t_entry *entry)
{
	char			*full_buf;
	char			*new_buf;
	ssize_t			size;

	if (stat(entry->full_name, &(entry->stat)) != 0)
		ls_unknown_error(errno);
	if (entry->dirent.d_type == DT_LNK)
	{
		ft_printf("found link\n");
		ft_printf("full name is %s\n", entry->full_name);
		full_buf = ft_memalloc(entry->stat.st_size);
		size = readlink(entry->full_name,
						full_buf, entry->stat.st_size + 1);
		size++;
		new_buf = ft_strdup(full_buf);
		ft_free(full_buf);
		ft_printf("look, (%s)!\n", new_buf);
	}
}

void				order_list_fill_stat(t_ls_order *order_list)
{
	t_passwd		*passwd;
	t_group			*group;
	t_entry			*entry;

	while (order_list != NULL)
	{
		entry = order_list->list;
		while (entry != NULL)
		{
			ls_nullptr((entry->full_name = ft_strjoin_3(order_list->name,
													"/", entry->name)));
			order_list_fill_stat2(entry);
			if ((passwd = getpwuid(entry->stat.st_uid)) != NULL)
				entry->owner = ft_strdup(passwd->pw_name);
			else
				ls_unknown_error(errno);
			if ((group = getgrgid(entry->stat.st_gid)) != NULL)
				entry->group = ft_strdup(group->gr_name);
			else
				ls_unknown_error(errno);
			entry = entry->entry_next;
		}
		order_list = order_list->next;
	}
}
