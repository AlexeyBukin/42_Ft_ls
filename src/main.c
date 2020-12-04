/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:22:39 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/04 19:56:32 by hinterfa         ###   ########.fr       */
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

void	ls_print_plain2(t_ls_order *order_nofiles, t_input	*input)
{
	t_bool		is_first;
	t_entry		*entry;

	is_first = TRUE;
	ls_nullptr(order_nofiles);
	is_first = input->rec;

	entry = order_nofiles->list;
	while (entry != NULL)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", entry->name);
		entry = entry->entry_next;
	}
}

t_ls_order	*test(t_ls_order *order_list)
{
	//rename
	t_ls_order		*tmp;
	t_ls_order		*nofiles_list;
	t_ls_order		*nofiles_tmp;
	t_ls_order		*res_list;
	t_ls_order		*res_tmp;
	t_input			input;

	tmp = order_list;
	nofiles_list = NULL;
	nofiles_tmp = NULL;
	res_list = NULL;
	res_tmp = NULL;
	ft_bzero(&input, sizeof(t_input));
	
	while (tmp != NULL)
	{
		if (tmp->error == E_LS_NO_SUCH_FILE)
		{
			ls_order_list_arrange_list(&nofiles_list, &nofiles_tmp, &tmp);
		}
		else
		{
			ls_order_list_arrange_list(&res_list, &res_tmp, &tmp);
		}
	}
	
	nofiles_list = ls_monofiles_to_plain(nofiles_list);
	nofiles_list = ls_order_list_sort(nofiles_list, &input);
	ls_print_plain2(nofiles_list, &input);
	// rename
	return(res_list);
}

int				main(int ac, char **av)
{
	t_input		input;
	t_ls_order	*order_list[2];

	ft_bzero(&input, sizeof(t_input));
	ls_flags(ac, av, &input);
	ls_nullptr((order_list[0] = ls_order_list_create(&input)));

	ls_nullptr(order_list[0] = test(order_list[0]));

	
	ls_nullptr((order_list[0] = ls_order_list_arrange(order_list[0])));
	
	// ft_printf("\n\n\n");
	// print_order_list(order_list[0]);
	// ft_printf("\n\n\n");

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
	free_order_list(order_list[0], input.list);
	free(input.order_names);
	return (0);
}
