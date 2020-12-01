/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 00:15:48 by hinterfa          #+#    #+#             */
/*   Updated: 2020/12/02 00:16:04 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_order	*ls_order_list_sort_time(t_ls_order *order_list)
{
	t_ls_order		*tmp;

	ls_nullptr(order_list);
	tmp = order_list;
	while (tmp != NULL)
	{
		if (tmp->error == E_LS_NONE && tmp->list_size > 0)
		{
			tmp->list = (t_entry*)sort_listable(
					(t_listable*)tmp->list, entry_compare_time);
		}
		tmp = tmp->next;
	}
	order_list = (t_ls_order*)sort_listable(
			(t_listable*)order_list, order_compare_time);
	return (order_list);
}

t_ls_order	*ls_order_list_sort_time_access(t_ls_order *order_list)
{
	t_ls_order		*tmp;

	ls_nullptr(order_list);
	tmp = order_list;
	while (tmp != NULL)
	{
		if (tmp->error == E_LS_NONE && tmp->list_size > 0)
		{
			tmp->list = (t_entry*)sort_listable(
					(t_listable*)tmp->list, entry_compare_time_access);
		}
		tmp = tmp->next;
	}
	order_list = (t_ls_order*)sort_listable(
			(t_listable*)order_list, order_compare_time_access);
	return (order_list);
}

t_ls_order	*ls_order_list_sort_size(t_ls_order *order_list)
{
	t_ls_order		*tmp;

	ls_nullptr(order_list);
	tmp = order_list;
	while (tmp != NULL)
	{
		if (tmp->error == E_LS_NONE && tmp->list_size > 0)
		{
			tmp->list = (t_entry*)sort_listable(
					(t_listable*)tmp->list, entry_compare_size);
		}
		tmp = tmp->next;
	}
	order_list = (t_ls_order*)sort_listable(
			(t_listable*)order_list, order_compare_size);
	return (order_list);
}
