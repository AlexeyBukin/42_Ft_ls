/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:00:57 by hush              #+#    #+#             */
/*   Updated: 2020/03/15 16:21:20 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static
t_ls_order		*ls_order_malloc(char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(order_name);
	ls_nullptr((order = (t_ls_order*)malloc(sizeof(t_ls_order))));
	order->name = order_name;
	order->next = NULL;
	order->prev = NULL;
	order->list = NULL;
	order->list_size = 0;
	order->error = 0;
	order->is_dir = FALSE;
	return (order);
}

static
t_ls_order		*ls_order_create(t_input *input, char *order_name)
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

t_ls_order			*ls_order_list_create(t_input *input)
{
	t_ls_order			*order_list;
	t_ls_order			*order;
	size_t 				i;

	ls_nullptr(input);
	order_list = NULL;
	order = NULL;
	i = 0;
	if (input->order_num > 0)
	{
		order_list = ls_order_create(input, input->order_names[i]);
		ls_nullptr(order_list);
		order = order_list;
		i++;
		while (i < input->order_num)
		{
			order->next = ls_order_create(input, input->order_names[i]);
			ls_nullptr(order->next);
			order->next->prev = order;
			order = order->next;
			i++;
		}
	}
	return (order_list);
}
