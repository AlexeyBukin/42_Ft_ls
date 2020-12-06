/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_compare_entry.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 00:08:45 by hinterfa          #+#    #+#             */
/*   Updated: 2020/12/06 16:43:29 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			entry_compare_alphabet(void *en_1_void, void *en_2_void)
{
	t_entry			*en_1;
	t_entry			*en_2;

	en_1 = (t_entry*)en_1_void;
	en_2 = (t_entry*)en_2_void;
	if (en_1 == NULL || en_2 == NULL)
	{
		if (en_1 != NULL)
			return (-1);
		else if (en_2 != NULL)
			return (1);
		return (0);
	}
	return (ft_strcmp(en_1->name, en_2->name));
}

int			entry_compare_time(void *en_1_void, void *en_2_void)
{
	t_entry			*en_1;
	t_entry			*en_2;

	en_1 = (t_entry*)en_1_void;
	en_2 = (t_entry*)en_2_void;
	if (en_1 == NULL || en_2 == NULL)
	{
		if (en_1 != NULL)
			return (-1);
		else if (en_2 != NULL)
			return (1);
		return (0);
	}
	return ((int)(en_2->stat.st_mtime - en_1->stat.st_mtime));
}

int			entry_compare_time_access(void *en_1_void, void *en_2_void)
{
	t_entry			*en_1;
	t_entry			*en_2;

	en_1 = (t_entry*)en_1_void;
	en_2 = (t_entry*)en_2_void;
	if (en_1 == NULL || en_2 == NULL)
	{
		if (en_1 != NULL)
			return (-1);
		else if (en_2 != NULL)
			return (1);
		return (0);
	}
	return ((int)(en_2->stat.st_atime - en_1->stat.st_atime));
}

int			entry_compare_size(void *en_1_void, void *en_2_void)
{
	t_entry			*en_1;
	t_entry			*en_2;

	en_1 = (t_entry*)en_1_void;
	en_2 = (t_entry*)en_2_void;
	if (en_1 == NULL || en_2 == NULL)
	{
		if (en_1 != NULL)
			return (-1);
		else if (en_2 != NULL)
			return (1);
		return (0);
	}
	return ((int)(en_2->stat.st_size - en_1->stat.st_size));
}
