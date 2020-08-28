/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flags_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 14:29:27 by gekans            #+#    #+#             */
/*   Updated: 2020/08/25 14:29:30 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls_flags(int ac, char **av, t_input *input)
{
	t_bool		flags_done;
	size_t		i;

	ls_nullptr(input);
	ls_nullptr(av);
	i = 0;
	flags_done = FALSE;
	input->order_names = (char**)malloc(sizeof(char*) * 2);
	ls_nullptr(input->order_names);
	input->order_names[0] = NULL;
	input->order_num = 0;
	input->current_dir = FALSE;
	while ((int)++i < ac)
	{
		ls_check_arg(av[i], &flags_done, input);
	}
	if (input->order_num == 0)
	{
		ls_add_order_name(input, ".");
		input->current_dir = TRUE;
	}
}
