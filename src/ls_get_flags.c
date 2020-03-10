/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:08:21 by kcharla           #+#    #+#             */
/*   Updated: 2020/03/11 01:14:07 by kcharla          ###   ########.fr       */
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

	if (input == NULL || ent_name == NULL)
		return (E_LS_NULL_POINTER);
	if (input->ent_names == NULL)
		return (E_LS_NULL_POINTER);
	i = 0;
	while (input->ent_names[i] != NULL)
		i++;
	if ((new_arr = (char**)malloc(sizeof(char*) * (i + 2))) == NULL)
		return (E_LS_NULL_POINTER);
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
	if (input == NULL)
		return (E_LS_NULL_POINTER);
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
		return (E_LS_ILLEGAL_OPTION);
	return (LS_OK);
}

int					ls_check_arg(char *arg, t_bool *flags_done, t_input *input)
{
	size_t			j;
	int				res;

	if (arg == NULL || flags_done == NULL || input == NULL)
		return (E_LS_NULL_POINTER);
	if (arg[0] != '-' || *flags_done == TRUE)
	{
		if ((res = ls_add_ent_name(input, arg)) != LS_OK)
			return (res);
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
			if ((res = ls_enter_flag(arg[j++], input)) != LS_OK)
				return (res);
	}
	return (LS_OK);
}

int					ls_get_flags(int ac, char **av, t_input *input)
{
	t_bool			flags_done;
	int				res;
	size_t			i;
	size_t			j;

	if (input == NULL || av == NULL)
		return (E_LS_NULL_POINTER);
	i = 0;
	flags_done = FALSE;
	while ((int)++i < ac)
		if ((res = ls_check_arg(av[i], &flags_done, input)) != LS_OK)
			return (res);
	return (LS_OK);
}
