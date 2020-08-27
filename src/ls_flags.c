/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:08:21 by kcharla           #+#    #+#             */
/*   Updated: 2020/08/22 18:15:00 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ls_add_order_name(t_input *input, char *order_name)
{
	char		**new_arr;
	size_t		i;

	ls_nullptr(order_name);
	ls_nullptr(input);
	i = input->order_num;
	ls_nullptr((new_arr = (char**)malloc(sizeof(char*) * (i + 1))));
	i = 0;
	while (i < input->order_num)
	{
		new_arr[i] = input->order_names[i];
		i++;
	}
	new_arr[i] = order_name;
	free(input->order_names);
	input->order_names = new_arr;
	input->order_num++;
}

int			ls_enter_flag(char c, t_input *input)
{
	ls_nullptr(input);
	if (c == 'R')
		input->rec = TRUE;
	else if (c == 'a')
		input->show = SHOW_ALL;
	else if (c == 'A')
		input->show = SHOW_HIDDEN;
	else if (c == 'l')
		input->list = TRUE;
	else if (c == 'r')
		input->rev = TRUE;
	else if (c == 't')
		input->time_sort = SORT_TIME_MOD;
	else if (c == 'u')
		input->time_sort = SORT_TIME_ACCESS;
	else
		ls_illegal_option(c);
	return (LS_OK);
}

t_bool		arg_is_double_dash(char *arg)
{
	if (arg[0] == '-')
		if (arg[1] == '-')
			if (arg[2] == '\0')
				return (TRUE);
	return (FALSE);
}

t_bool		arg_is_dot(char *arg)
{
	if (arg[0] == '.')
		if (arg[1] == '\0')
			return (TRUE);
	return (FALSE);
}

void		ls_check_arg(char *arg, t_bool *flags_done, t_input *input)
{
	size_t		j;

	ls_nullptr(arg);
	ls_nullptr(flags_done);
	ls_nullptr(input);
	if (arg_is_dot(arg))
	{
		if (input->order_num == 0)
			input->current_dir = TRUE;
		else
			input->current_dir = FALSE;
	}
	else
		input->current_dir = FALSE;
	if (arg_is_double_dash(arg))
		*flags_done = TRUE;
	else if (arg[0] != '-' || *flags_done == TRUE)
		ls_add_order_name(input, arg);
	else
	{
		j = 1;
		while (arg[j] != '\0')
			ls_enter_flag(arg[j++], input);
	}
}
