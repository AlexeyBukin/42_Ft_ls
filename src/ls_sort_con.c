/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_con.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 13:12:17 by gekans            #+#    #+#             */
/*   Updated: 2020/08/25 13:12:22 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_listable	*merge_lists2(t_listable *list_1, t_listable *list_2,
				t_listable *merged, int (compare)(void*, void*))
{
	t_listable	*tmp;

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
	return (tmp);
}

t_listable	*merge_lists(t_listable *list_1, t_listable *list_2,
									int (compare)(void*, void*))
{
	t_listable	*merged;

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
	merge_lists2(list_1, list_2, merged, compare);
	return (merged);
}

int			entry_compare_alphabet(void *en_1_void, void *en_2_void)
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
