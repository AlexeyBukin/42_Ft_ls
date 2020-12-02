/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 19:49:31 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/02 18:54:44 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		merge_lists_helper(t_listable **list_1, t_listable **list_2,
					int (compare)(void*, void*), t_listable **setted)
{
	if (compare(*list_1, *list_2) <= 0)
	{
		*setted = *list_1;
		*list_1 = (*list_1)->next;
	}
	else
	{
		*setted = *list_2;
		*list_2 = (*list_2)->next;
	}
}

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
	merge_lists_helper(&list_1, &list_2, compare, &merged);
	tmp = merged;
	while (list_1 != NULL && list_2 != NULL)
	{
		merge_lists_helper(&list_1, &list_2, compare, &(tmp->next));
		tmp = tmp->next;
	}
	if (list_1 != NULL)
		tmp->next = list_1;
	if (list_2 != NULL)
		tmp->next = list_2;
	return (merged);
}
