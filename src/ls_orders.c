/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:00:57 by hush              #+#    #+#             */
/*   Updated: 2020/08/23 03:28:16 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_order	*ls_order_malloc(char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(order_name);
	ls_nullptr((order = (t_ls_order*)malloc(sizeof(t_ls_order))));
	order->name = order_name;
	order->next = NULL;
	order->list = NULL;
	order->list_size = 0;
	order->error = 0;
	order->is_dir = FALSE;
	return (order);
}

t_ls_order	*ls_order_create(t_input *input, char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(input);
	ls_nullptr((order = ls_order_malloc(order_name)));
	if (stat(order_name, &(order->stat)) != 0)
	{
		if (errno == ENOENT)
			order->error = E_LS_NO_SUCH_FILE;
		else if (errno == EACCES)
			order->error = E_LS_PERMISSION_DENIED;
		else
			ls_unknown_error(errno);
	}
	else if (!(order->stat.st_mode & S_IRUSR))
		order->error = E_LS_PERMISSION_DENIED;
	else if (S_ISDIR(order->stat.st_mode))
	{
		order->is_dir = TRUE;
		order->list = ls_entry_list_create(input, order);
	}
	if (order->error == E_LS_NO_SUCH_FILE)
		ft_printf("ft_ls: %s: No such file or directory\n", order_name);
	return (order);
}

t_ls_order	*ls_order_create_rec(t_input *input, char *order_name)
{
	t_entry			*entry;
	t_ls_order		*order;
	t_ls_order		*order_rec;

	ls_nullptr((order_rec = ls_order_create(input, order_name)));
	if (order_rec->is_dir == FALSE)
		return (NULL);
	order = order_rec;
	entry = order->list;
	while (entry != NULL)
	{
		if (ft_strcmp(entry->name, ".") != 0
					&& ft_strcmp(entry->name, "..") != 0)
		{
			order->next = ls_order_create_rec(input,
				ft_strjoin_3(order_name, "/", entry->name));
			while (order->next != NULL)
				order = order->next;
		}
		entry = entry->entry_next;
	}
	return (order_rec);
}

t_ls_order	*ls_order_list_create_rec(t_input *input,
					t_ls_order *order_list)
{
	t_ls_order			*order_tmp;
	t_ls_order			*order;
	size_t				i;

	ls_nullptr(input);
	order_tmp = NULL;
	i = 0;
	while (i < input->order_num)
	{
		ls_nullptr((order = ls_order_create_rec(input, input->order_names[i])));
		if (order_list != NULL)
		{
			if (order_tmp == NULL)
				order_tmp = order_list;
			while (order_tmp->next != NULL)
				order_tmp = order_tmp->next;
			order_tmp->next = order;
		}
		else
			order_list = order;
		i++;
	}
	return (order_list);
}

t_ls_order	*ls_order_list_create_plain(t_input *input,
					t_ls_order *order_list)
{
	t_ls_order		*order_tmp;
	t_ls_order		*order;
	size_t			i;

	ls_nullptr(input);
	order_tmp = NULL;
	i = 0;
	while (i < input->order_num)
	{
		ls_nullptr((order = ls_order_create(input, input->order_names[i])));
		if (order_list != NULL)
		{
			if (order_tmp == NULL)
				order_tmp = order_list;
			order_tmp->next = order;
		}
		else
			order_list = order;
		i++;
	}
	return (order_list);
}
