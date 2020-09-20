/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:25:53 by kcharla           #+#    #+#             */
/*   Updated: 2020/09/20 16:40:14 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_order_list(t_ls_order *order_list)
{
	t_ls_order		*tmp_ord;
	t_entry			*temp;

	tmp_ord = order_list;
	while (tmp_ord != NULL)
	{
		ft_printf("main dir : %s, p=%p, next=%p\n",
			tmp_ord->name, tmp_ord, tmp_ord->next);
		temp = tmp_ord->list;
		while (temp != NULL)
		{
			ft_printf("     ent : \'%20s\', p=%p, next=%p\n",
				temp->name, temp, temp->entry_next);
			temp = temp->entry_next;
		}
		tmp_ord = tmp_ord->next;
	}
}
