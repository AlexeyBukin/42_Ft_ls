/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 13:34:40 by gekans            #+#    #+#             */
/*   Updated: 2020/08/26 13:34:43 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_listable	*merge_lists(t_listable *list_1, t_listable *list_2,
						   int (compare)(void*, void*))
{
	t_listable		*merged;
	t_listable		*tmp;

	ls_nullptr(compare);
	if (list_1 == NULL)
		return (list_2);
	if (list_2 == NULL)
		return (list_1);
	if (compare(list_1, list_2) < 0)
	{
		merged = list_1;
		list_1 = list_1->next;
	}
	else
	{
		merged = list_2;
		list_2 = list_2->next;
	}
	tmp = merged;
	while (list_1 != NULL && list_2 != NULL)
	{
		if (compare(list_1, list_2) < 0)
		{
			tmp->next = list_1;
			list_1 = list_1->next;
		}
		else
		{
			tmp->next = list_2;
			list_2 = list_2->next;
		}
		tmp = tmp->next;
	}
	if (list_1 != NULL)
		tmp->next = list_1;
	if (list_2 != NULL)
		tmp->next = list_2;
	return (merged);
}

t_listable	*sort_listable(t_listable *list, int (compare)(void*, void*))
{
	t_listable		*stack[32];
	char			levels[32];
	unsigned char	pos;

	if (list == NULL || compare == NULL)
		return (NULL);
	ls_nullptr(list);
	ls_nullptr(compare);
	pos = 0;
	while (list != NULL)
	{
		stack[pos] = list;
		levels[pos] = 1;
		list = list->next;
		stack[pos]->next = NULL;
		pos++;
		while ((pos > 1) && (levels[pos - 1] == levels[pos - 2]))
		{
			stack[pos - 2] = merge_lists(stack[pos - 2], stack[pos - 1], compare);
			levels[pos - 2]++;
			pos--;
		}
	}
	while (pos > 1)
	{
		stack[pos - 2] = merge_lists(stack[pos - 2], stack[pos - 1], compare);
		levels[pos - 2]++;
		pos--;
	}
	if (pos > 0)
		return (stack[0]);
	return (NULL);
}

int			order_compare_alphabet(void* order_1_void, void* order_2_void)
{
	t_ls_order		*order_1;
	t_ls_order		*order_2;

	order_1 = (t_ls_order*)order_1_void;
	order_2 = (t_ls_order*)order_2_void;
	if (order_1 == NULL || order_2 == NULL)
	{
		if (order_1 != NULL)
			return (-1);
		else if (order_2 != NULL)
			return (1);
		return (0);
	}
	return (ft_strcmp(order_1->name, order_2->name));
}

int			order_compare_time(void *order_1_void, void *order_2_void)
{
	t_ls_order		*order_1;
	t_ls_order		*order_2;

	order_1 = (t_ls_order*)order_1_void;
	order_2 = (t_ls_order*)order_2_void;
	if (order_1 == NULL || order_2 == NULL)
	{
		if (order_1 != NULL)
			return (-1);
		else if (order_2 != NULL)
			return (1);
		return (0);
	}
	return ((int)(order_1->stat.st_mtime - order_2->stat.st_mtime) * (-1));
}

int			entry_compare_alphabet(void* en_1_void, void* en_2_void)
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
	return (ft_strcmp(en_1->name, en_2->name));
}

int			entry_compare_time(void* en_1_void, void* en_2_void)
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
	return ((int)(en_2->stat.st_mtime - en_1->stat.st_mtime));
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
