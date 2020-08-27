/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 13:34:40 by gekans            #+#    #+#             */
/*   Updated: 2020/08/26 13:34:43 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			entry_compare_time(void *en_1_void, void *en_2_void)
{
	t_entry			*en_1;
	t_entry			*en_2;

	en_1 = (t_entry*)en_1_void;
	en_2 = (t_entry*)en_2_void;
	if (en_1 == NULL || en_2 == NULL)
	{
		if (en_1 != NULL)
			return (-1);
		else if (en_2 != NULL)
			return (1);
		return (0);
	}
	if (en_2->stat.st_mtime != en_1->stat.st_mtime)
		return ((int)(en_2->stat.st_mtime - en_1->stat.st_mtime));
	if (en_2->stat.st_mtime != en_1->stat.st_mtime)
		return ((int)(en_2->stat.st_mtime - en_1->stat.st_mtime));
	return (entry_compare_alphabet(en_1_void, en_2_void));
}

t_ls_order	*ls_order_list_sort_alpha(t_ls_order *order_list)
{
	t_ls_order		*tmp;

	ls_nullptr(order_list);
	tmp = order_list;
	while (tmp != NULL)
	{
		if (tmp->error == 0 && tmp->is_dir == TRUE && tmp->list_size > 0)
		{
			tmp->list = (t_entry*)sort_listable(
					(t_listable*)tmp->list, entry_compare_alphabet);
		}
		tmp = tmp->next;
	}
	order_list = (t_ls_order*)sort_listable(
			(t_listable*)order_list, order_compare_alphabet);
	return (order_list);
}

t_ls_order	*ls_order_list_sort_time(t_ls_order *order_list)
{
	t_ls_order		*tmp;

	ls_nullptr(order_list);
	tmp = order_list;
	while (tmp != NULL)
	{
		if (tmp->error == 0 && tmp->is_dir == TRUE && tmp->list != NULL)
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

t_ls_order	*ls_order_list_sort(t_ls_order *order_list, t_input *input)
{
	t_ls_order	*sorted;

	ls_nullptr(input);
	sorted = ls_order_list_sort_alpha(order_list);
	if (input->time_sort == TRUE)
	{
		sorted = ls_order_list_sort_time(sorted);
	}
	return (sorted);
}
