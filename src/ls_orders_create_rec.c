/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders_create_rec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:38:26 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/17 17:38:43 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_order			*ls_order_malloc(char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(order_name);
	ls_nullptr((order = (t_ls_order*)ft_memalloc(sizeof(t_ls_order))));
	order->name = order_name;
	order->is_dir = FALSE;
	return (order);
}

t_ls_order			*ls_order_error(t_ls_order *order, int error)
{
	if (order != NULL)
		order->error = error;
	return (order);
}

t_ls_order			*ls_order_create(t_input *input, char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(input);
	ls_nullptr((order = ls_order_malloc(order_name)));
	order->error = E_LS_NONE;
	if (lstat(order_name, &(order->stat)) != 0)
	{
		if (errno == ENOENT)
			ft_printf("ft_ls: %s: No such file or directory\n", order_name);
		else if (errno == EACCES)
			return (ls_order_error(order, E_LS_PERMISSION_DENIED));
		else
			ls_unknown_error(errno);
	}
	if (!(order->stat.st_mode & S_IRUSR))
		return (ls_order_error(order, E_LS_PERMISSION_DENIED));
	if (S_ISDIR(order->stat.st_mode))
	{
		order->is_dir = TRUE;
		order->list = ls_entry_list_create(input, order);
	}
	else
		order->list = ls_entry_nameonly(order_name);
	return (order);
}

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
	ls_order_create_rec_helper(order->list, &order, order_name, input);
	return (order_rec);
}
