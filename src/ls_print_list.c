/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 00:19:04 by hinterfa          #+#    #+#             */
/*   Updated: 2020/12/06 16:48:38 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list_helper(t_ls_order *order_list)
{
	char *basename;

	basename = ft_strrchr(order_list->name, '/');
	if (basename == NULL)
		basename = order_list->name;
	else
		basename++;
	ft_printf("ft_ls: %s: Permission denied\n", basename);
}

void	ls_print_list(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	char		str_rwx[12];

	is_first = TRUE;
	str_rwx[11] = '\0';
	ls_nullptr(order_list);
	while (order_list != NULL)
	{
		if (order_list->error == E_LS_NONE)
			ls_print_order(order_list, input, is_first, str_rwx);
		else
		{
			if (order_list->error == E_LS_PERMISSION_DENIED)
			{
				if (is_first == FALSE)
					ft_printf("\n");
				if ((input->order_num > 1 || (input->rec == TRUE &&
				is_first == FALSE)) && order_list->is_dir == TRUE)
					ft_printf("%s:\n", order_list->name);
				print_list_helper(order_list);
			}
		}
		is_first = FALSE;
		order_list = order_list->next;
	}
}
