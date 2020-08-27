/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 19:47:27 by gekans            #+#    #+#             */
/*   Updated: 2020/08/24 19:47:33 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				stat_needed(t_input *input)
{
	ls_nullptr(input);
	if (input->list == TRUE || input->time_sort == TRUE)
		return (TRUE);
	return (FALSE);
}

t_entry			*entry_list_reverse(t_entry *temp)
{
	t_entry		*reversed;
	t_entry		*to_do;

	ls_nullptr(temp);
	if (temp->entry_next == NULL)
		return (temp);
	to_do = temp->entry_next;
	reversed = temp;
	reversed->entry_next = NULL;
	while (to_do != NULL)
	{
		temp = to_do;
		to_do = to_do->entry_next;
		temp->entry_next = reversed;
		reversed = temp;
	}
	return (reversed);
}

t_ls_order		*order_list_revert(t_ls_order *temp)
{
	t_ls_order		*reversed;
	t_ls_order		*to_do;

	ls_nullptr(temp);
	ls_nullptr(temp->list = entry_list_reverse(temp->list));
	if (temp->next == NULL)
		return (temp);
	to_do = temp->next;
	reversed = temp;
	reversed->next = NULL;
	while (to_do != NULL)
	{
		temp = to_do;
		ls_nullptr(to_do->list = entry_list_reverse(to_do->list));
		to_do = to_do->next;
		temp->next = reversed;
		reversed = temp;
	}
	return (reversed);
}

int				main(int ac, char **av)
{
	t_input		input;
	t_ls_order	*order_list;

	ft_bzero(&input, sizeof(t_input));
	ls_flags(ac, av, &input);
	ls_nullptr((order_list = ls_order_list_create(&input)));
	if (stat_needed(&input))
		order_list_fill_stat(order_list);
	ls_nullptr((order_list = ls_order_list_sort(order_list, &input)));
	if (input.rev == TRUE)
	{
		ls_nullptr(order_list = order_list_revert(order_list));
	}
	ls_print(order_list, &input);
	free_order_list(order_list);
	free(input.order_names);
	return (0);
}
