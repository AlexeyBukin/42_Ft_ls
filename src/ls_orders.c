/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:00:57 by hush              #+#    #+#             */
/*   Updated: 2020/12/01 22:25:42 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_ls_order	*ls_order_create_rec_safe(t_input *input, char *name)
{
	t_ls_order			*order;

	ls_nullptr(order = ls_order_create_rec(input, name));
	// if (order->error == E_LS_PLAIN_FILE)
	// {
	// 	free_order_list(order);
	// 	ls_nullptr(order = ls_order_create(input, name));
	// }
	return (order);
}

static t_ls_order	*ls_order_list_create_rec(t_input *input,
					t_ls_order *order_list)
{
	t_ls_order			*order_tmp;
	t_ls_order			*order;
	size_t				i;

	ls_nullptr(input);
	order_tmp = NULL;
	i = 0;
	while (i < input->order_num)
	{
		// ft_printf("User order: %s\n", input->order_names[i]);
		order = ls_order_create_rec_safe(input,
		ft_strdup(input->order_names[i]));
		// ft_printf("User order end: %s\n", input->order_names[i]);
		// ft_printf("User order: %s\n", order->name);
		if (order_list != NULL)
		{
			if (order_tmp == NULL)
				order_tmp = order_list;
			while (order_tmp->next != NULL)
				order_tmp = order_tmp->next;
			order_tmp->next = order;
		}
		else
			order_list = order;
		i++;
	}
	return (order_list);
}

void				ls_order_list_create_plain_helper(t_ls_order **order,
					t_ls_order **order_list, t_ls_order **order_tmp)
{
	if (order == NULL || order_list == NULL || order_tmp == NULL)
		return ;
	if ((*order)->is_dir == FALSE)
	{
		if ((*order_list)->is_dir == FALSE)
		{
			if ((*order)->list != NULL)
				(*order)->list->entry_next = (*order_list)->list;
			else
				(*order)->list = (*order_list)->list;
			(*order_list)->list = (*order)->list;
			(*order)->list = NULL;
			free_order_list_struct_only(*order);	//
		}
		else
		{
			(*order)->next = *order_list;
			*order_list = *order;
		}
	}
	else
	{
		(*order_tmp)->next = *order;
		(*order_tmp) = *order;
	}
}

static t_ls_order	*ls_order_list_create_plain(t_input *input,
					t_ls_order *order_list)
{
	t_ls_order			*order_tmp;
	t_ls_order			*order;
	size_t				i;

	ls_nullptr(input);
	order_tmp = NULL;
	i = 0;
	while (i < input->order_num)
	{
		order = ls_order_create(input, ft_strdup(input->order_names[i]));
		ls_nullptr(order);
		// ft_printf("next order: %s, %p\n", order->name, order->name);
		if (order_list != NULL)
		{
			ls_order_list_create_plain_helper(&order, &order_list, &order_tmp);
		}
		else
		{
			order_tmp = order;
			order_list = order;
		}
		i++;
	}

	// t_ls_order *tmp = order_list;
	// while (tmp != NULL)
	// {
	// 	ft_printf("arrange order: %s, %p\n", tmp->name, tmp->name);
	// 	tmp = tmp->next;
	// }
	
	return (order_list);
}

t_ls_order			*ls_order_list_create(t_input *input)
{
	t_ls_order			*order_list;

	order_list = NULL;
	if (input->rec == TRUE)
		return (ls_order_list_create_rec(input, order_list));
	return (ls_order_list_create_plain(input, order_list));
}
