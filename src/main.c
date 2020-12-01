/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:22:39 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/01 18:59:09 by hinterfa         ###   ########.fr       */
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
	t_ls_order	*order_list[2];

	ft_bzero(&input, sizeof(t_input));
	ls_flags(ac, av, &input);

	// char *tmp_str = NULL;
	// size_t i = 0;
	// while (i < input.order_num)
	// {
	// 	tmp_str = input.order_names[i];
	// 	ft_printf("order: %s\n", tmp_str);
	// 	i++;
	// }
	// ft_printf("1\n");
	ls_nullptr((order_list[0] = ls_order_list_create(&input)));
	
	// t_ls_order *tmp = order_list[0];
	// while (tmp != NULL)
	// {
	// 	ft_printf("arrange before order: %s, %p\n", tmp->name, tmp->name);
	// 	tmp = tmp->next;
	// }
	
	// ft_printf("1\n");
	// ls_print(order_list[0], &input);
	// ft_printf("\n\n");
	ls_nullptr((order_list[0] = ls_order_list_arrange(order_list[0])));
	// ls_print(order_list[0], &input);


	// t_entry *tmp = order_list[0]->list;
	// while (tmp != NULL)
	// {
	// 	ft_printf("arrange entry in monofiles: %s, %p\n", tmp->name, tmp->name);
	// 	tmp = tmp->entry_next;
	// }
	
	if (stat_needed(&input))
		order_list_fill_stat(order_list[0], &input);
	order_list[1] = order_list[0]->next;
	order_list[0]->next = NULL;
	ls_nullptr((order_list[0] = ls_order_list_sort(order_list[0], &input)));
	if (order_list[1] != NULL)
		ls_nullptr((order_list[1] = ls_order_list_sort(order_list[1], &input)));
	if (input.rev == TRUE)
	{
		ls_nullptr(order_list[0] = order_list_revert(order_list[0]));
		if (order_list[1] != NULL)
			ls_nullptr(order_list[1] = order_list_revert(order_list[1]));
	}
	order_list[0]->next = order_list[1];
	ls_print(order_list[0], &input);
	free_order_list(order_list[0]);
	free(input.order_names);
	return (0);
}
