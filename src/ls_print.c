/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls__print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:46:58 by hush              #+#    #+#             */
/*   Updated: 2020/03/15 18:46:58 by hush             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_order_list(t_ls_order *order_list)
{
	t_ls_order *tmp_ord = order_list;
	while (tmp_ord != NULL)
	{
		ft_printf("main dir : %s, p=%p, prev=%p, next=%p\n", tmp_ord->name, tmp_ord, tmp_ord->prev, tmp_ord->next);
		t_entry *temp = tmp_ord->list;
		while (temp != NULL)
		{
			ft_printf("     ent : \'%20s\', p=%p, prev=%p, next=%p\n", temp->name, temp, temp->prev, temp->entry_next);
			temp = temp->entry_next;
		}
		tmp_ord = tmp_ord->next;
	}
}

void	print_flags(t_input *input)
{
	ft_printf("R = %c\n", input->rec + '0');
	ft_printf("a = %c\n", input->all + '0');
	ft_printf("l = %c\n", input->list + '0');
	ft_printf("r = %c\n", input->rev + '0');
	ft_printf("t = %c\n", input->time + '0');
}
