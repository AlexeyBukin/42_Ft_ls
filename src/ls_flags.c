/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:08:21 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/01 21:42:48 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			ls_add_order_name(t_input *input, char *order_name)
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

static int			ls_enter_flag(char c, t_input *input)
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
	else if (c == 'S')								//
		input->size_sort = TRUE;
	else if (c == 'd')
		input->cancel_rec = TRUE;
	else if (ft_strchr("1gf\\", c) == NULL)
		ls_illegal_option(c);
	return (LS_OK);
}

static t_bool		arg_is_double_dash(char *arg)
{
	if (arg[0] == '-')
		if (arg[1] == '-')
			if (arg[2] == '\0')
				return (TRUE);
	return (FALSE);
}

void				ls_check_arg(char *arg, t_bool *flags_done, t_input *input)
{
	size_t		j;

	ls_nullptr(arg);
	ls_nullptr(flags_done);
	ls_nullptr(input);
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

void				ls_flags(int ac, char **av, t_input *input)
{
	t_bool			flags_done;
	size_t			i;

	ls_nullptr(input);
	ls_nullptr(av);
	i = 0;
	flags_done = FALSE;
	input->order_names = (char**)malloc(sizeof(char*) * 2);
	ls_nullptr(input->order_names);
	input->order_names[0] = NULL;
	input->order_num = 0;
	while ((int)++i < ac)
	{
		ls_check_arg(av[i], &flags_done, input);
	}
	if (input->size_sort == TRUE)
		input->time_sort = SORT_TIME_NONE;
	if (input->cancel_rec == TRUE)
		input->rec = FALSE;
	if (input->order_num == 0)
	{
		ls_add_order_name(input, ".");
	}
	input->time_now = time(NULL);
}
