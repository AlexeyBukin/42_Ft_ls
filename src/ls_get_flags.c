/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:08:21 by kcharla           #+#    #+#             */
/*   Updated: 2020/03/11 03:42:03 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** TODO smart array resizing
*/

int					ls_add_ent_name(t_input *input, char *ent_name)
{
	char		**new_arr;
	size_t		i;

	ls_nullptr(ent_name);
	ls_nullptr(input);
	ls_nullptr(input->ent_names);
	i = 0;
	while (input->ent_names[i] != NULL)
		i++;
	ls_nullptr(new_arr = (char**)malloc(sizeof(char*) * (i + 2)));
	i = 0;
	while (input->ent_names[i] != NULL)
	{
		new_arr[i] = input->ent_names[i];
		i++;
	}
	new_arr[i++] = ent_name;
	new_arr[i] = NULL;
	free(input->ent_names);
	input->ent_names = new_arr;
	return (LS_OK);
}

int					ls_enter_flag(char c, t_input *input)
{
	ls_nullptr(input);
	if (c == 'R')
		input->rec = TRUE;
	else if (c == 'a')
		input->all = TRUE;
	else if (c == 'l')
		input->list = TRUE;
	else if (c == 'r')
		input->rev = TRUE;
	else if (c == 't')
		input->time = TRUE;
	else
		ls_illegal_option(c);
	return (LS_OK);
}

int					ls_check_arg(char *arg, t_bool *flags_done, t_input *input)
{
	size_t			j;

	ls_nullptr(arg);
	ls_nullptr(flags_done);
	ls_nullptr(input);
	if (arg[0] != '-' || *flags_done == TRUE)
	{
		ls_add_ent_name(input, arg);
		*flags_done = TRUE;
	}
	else
	{
		if (arg[1] == '-')
			if (arg[2] == '\0')
			{
				*flags_done = TRUE;
				return (LS_OK);
			}
		j = 1;
		while (arg[j] != '\0')
			ls_enter_flag(arg[j++], input);
	}
	return (LS_OK);
}

int					ls_get_flags(int ac, char **av, t_input *input)
{
	t_bool			flags_done;
	size_t			i;

	ls_nullptr(input);
	ls_nullptr(av);
	i = 0;
	flags_done = FALSE;
	input->ent_names = (char**)malloc(sizeof(char*) * 2);
	ls_nullptr(input->ent_names);
	input->ent_names[0] = NULL;
	while ((int)++i < ac)
		ls_check_arg(av[i], &flags_done, input);
	return (LS_OK);
}
