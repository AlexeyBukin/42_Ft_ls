/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_nofiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:07:55 by hinterfa          #+#    #+#             */
/*   Updated: 2020/12/06 18:49:23 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_print_nofiles(t_ls_order *order_nofiles, t_input *input)
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

void		sort_nofiles(t_ls_order **nofiles_list)
{
	t_input			input;

	ft_bzero(&input, sizeof(t_input));
	*nofiles_list = ls_monofiles_to_plain(*nofiles_list);
	*nofiles_list = ls_order_list_sort(*nofiles_list, &input);
	ls_print_nofiles(*nofiles_list, &input);
}

t_ls_order	*nofile_handler(t_ls_order *order_list)
{
	t_ls_order		*tmp;
	t_ls_order		*nofiles_list;
	t_ls_order		*nofiles_tmp;
	t_ls_order		*res_list;
	t_ls_order		*res_tmp;

	tmp = order_list;
	nofiles_list = NULL;
	nofiles_tmp = NULL;
	res_list = NULL;
	res_tmp = NULL;
	while (tmp != NULL)
	{
		if (tmp->error == E_LS_NO_SUCH_FILE)
			ls_order_list_arrange_list(&nofiles_list, &nofiles_tmp, &tmp);
		else
			ls_order_list_arrange_list(&res_list, &res_tmp, &tmp);
	}
	if (nofiles_list != NULL)
		sort_nofiles(&nofiles_list);
	return (res_list);
}
