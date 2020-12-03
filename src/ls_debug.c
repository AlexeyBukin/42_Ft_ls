/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:25:53 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/03 16:56:20 by hinterfa         ###   ########.fr       */
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
		ft_printf("main dir : %s, is_dir: %d, p=%p, next=%p, error=%d\n",
			tmp_ord->name, tmp_ord->is_dir, tmp_ord, tmp_ord->next, tmp_ord->error);
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
