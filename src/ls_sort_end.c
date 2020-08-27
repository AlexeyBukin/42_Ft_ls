/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 13:35:58 by gekans            #+#    #+#             */
/*   Updated: 2020/08/25 13:36:00 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned char		kakayato_huita(t_listable *list, t_listable *stack[32],
	char levels[32], int (compare)(void*, void*))
{
	unsigned char	pos;

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
			stack[pos - 2] = merge_lists(stack[pos - 2],
								stack[pos - 1], compare);
			levels[pos - 2]++;
			pos--;
		}
	}
	return (pos);
}

t_listable			*sort_listable(t_listable *list,
				int (compare)(void*, void*))
{
	t_listable		*stack[32];
	char			levels[32];
	unsigned char	pos;

	if (list == NULL || compare == NULL)
		return (NULL);
	ls_nullptr(list);
	ls_nullptr(compare);
	ft_bzero(stack, sizeof(t_listable*) * 32);
	ft_bzero(levels, sizeof(char) * 32);
	pos = kakayato_huita(list, stack, levels, compare);
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

int					order_compare_alphabet(void *order_1_void,
									void *order_2_void)
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

int					order_compare_time(void *order_1_void, void *order_2_void)
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
	if (order_1->stat.st_mtime != order_2->stat.st_mtime)
		return ((int)(order_1->stat.st_mtime - order_2->stat.st_mtime));
	if (order_1->stat.st_mtime != order_2->stat.st_mtime)
		return ((int)(order_1->stat.st_mtime - order_2->stat.st_mtime));
	return (order_compare_alphabet(order_1_void, order_2_void));
}
