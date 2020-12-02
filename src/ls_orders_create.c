/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 00:21:00 by hinterfa          #+#    #+#             */
/*   Updated: 2020/12/02 22:39:02 by hinterfa         ###   ########.fr       */
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
	order->list = NULL;
	return (order);
}

t_ls_order			*ls_order_error(t_ls_order *order, int error)
{
	if (order != NULL)
	{
		if (error == E_LS_NO_SUCH_FILE)
		{
			// ft_printf("ft_ls: %s: No such file or directory\n", order->name);
			order->error = error;
			// ft_printf("%s\n", order->name);
			order->is_dir = TRUE;
			order->list = NULL;
			// ls_nullptr(order->list = ls_entry_nameonly(order->name));
		}
		else if (S_ISDIR(order->stat.st_mode))
		{
			// ft_printf("without entity\n");
			order->is_dir = TRUE;
			order->error = error;
		}
		else
		{
			order->is_dir = FALSE;
			ls_nullptr(order->list = ls_entry_nameonly(order->name));
		}
	}
	return (order);
}

void				ls_order_create_helper(t_ls_order **order,
						t_input *input, char *order_name)
{
	if (S_ISDIR((*order)->stat.st_mode))
	{
		(*order)->is_dir = TRUE;
		(*order)->list = ls_entry_list_create(input, *order);
	}
	else
	{
		(*order)->is_dir = FALSE;
		(*order)->list = ls_entry_nameonly(order_name);
	}
}

t_ls_order			*ls_order_create(t_input *input, char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(input);
	ls_nullptr((order = ls_order_malloc(order_name)));
	order->error = E_LS_NONE;
	if (lstat(order_name, &(order->stat)) != 0)
	{
		// ft_printf("got one!\n");
		if (errno == ENOENT)
			return (ls_order_error(order, E_LS_NO_SUCH_FILE));
		else if (errno == EACCES)
			return (ls_order_error(order, E_LS_PERMISSION_DENIED));
		else
			ls_unknown_error(errno);
	}
	//
	// if (!(order->stat.st_mode & S_IRUSR))
	// 	return (ls_order_error(order, order->error));
	//
	ls_order_create_helper(&order, input, order_name);
	return (order);
}
