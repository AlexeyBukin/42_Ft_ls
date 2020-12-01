/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 13:34:40 by gekans            #+#    #+#             */
/*   Updated: 2020/12/01 05:27:21 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		sort_listable_helper(t_listable **stack, char *levels,
				unsigned char pos, int (compare)(void*, void*))
{
	stack[pos - 2] = merge_lists(stack[pos - 2], stack[pos - 1], compare);
	levels[pos - 2]++;
}

t_listable	*sort_listable(t_listable *list, int (compare)(void*, void*))
{
	t_listable		*stack[LS_SORT_DEPTH];
	char			levels[LS_SORT_DEPTH];
	unsigned char	pos;

	if (list == NULL || compare == NULL)
		return (NULL);
	pos = 0;
	while (list != NULL)
	{
		stack[pos] = list;
		levels[pos] = 1;
		list = list->next;
		stack[pos]->next = NULL;
		pos++;
		while ((pos > 1) && (levels[pos - 1] == levels[pos - 2]))
			sort_listable_helper(stack, levels, pos--, compare);
	}
	while (pos > 1)
		sort_listable_helper(stack, levels, pos--, compare);
	if (pos > 0)
		return (stack[0]);
	return (NULL);
}

t_ls_order	*ls_order_list_sort_alpha(t_ls_order *order_list)
{
	t_ls_order		*tmp;

	ls_nullptr(order_list);
	tmp = order_list;
	while (tmp != NULL)
	{
		if (tmp->error == E_LS_NONE && tmp->list_size > 0)
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

t_ls_order	*ls_order_list_sort(t_ls_order *order_list, t_input *input)
{
	t_ls_order	*sorted;

	ls_nullptr(input);
	sorted = ls_order_list_sort_alpha(order_list);
	if (input->time_sort == SORT_TIME_MOD)
	{
		sorted = ls_order_list_sort_time(sorted);
	}
	else if (input->time_sort == SORT_TIME_ACCESS)
	{
		sorted = ls_order_list_sort_time_access(sorted);
	}
	return (sorted);
}
