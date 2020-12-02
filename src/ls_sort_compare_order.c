/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_compare_order.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 19:49:26 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/02 21:09:28 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ft_cmp_low(const char *s1, const char *s2)
{
	char *s3;
	char *s4;
	int	res;

	s3 = ft_strdup(s1);
	s4 = ft_strdup(s2);
	ft_str_low(s3);
	ft_str_low(s4);
	res = ft_strcmp(s3, s4);
	free(s3);
	free(s4);
	return (res);
}

int			order_compare_alphabet(void *order_1_void, void *order_2_void)
{
	t_ls_order		*order_1;
	t_ls_order		*order_2;

	order_1 = (t_ls_order*)order_1_void;
	order_2 = (t_ls_order*)order_2_void;
	if (order_1 == NULL || order_2 == NULL)
	{
		if (order_1 != NULL)
			return (-1);
		else if (order_2 != NULL)
			return (1);
		return (0);
	}
	// return (ft_cmp_low(order_1->name, order_2->name));
	return (ft_strcmp(order_1->name, order_2->name));
}


int			order_compare_time(void *order_1_void, void *order_2_void)
{
	t_ls_order		*order_1;
	t_ls_order		*order_2;	

	order_1 = (t_ls_order*)order_1_void;
	order_2 = (t_ls_order*)order_2_void;
	if (order_1 == NULL || order_2 == NULL)
	{
		if (order_1 != NULL)
			return (-1);
		else if (order_2 != NULL)
			return (1);
		return (0);
	}
	return ((int)((order_1->stat.st_mtime - order_2->stat.st_mtime)) * (-1));
}

int			order_compare_time_access(void *order_1_void, void *order_2_void)
{
	t_ls_order		*order_1;
	t_ls_order		*order_2;

	order_1 = (t_ls_order*)order_1_void;
	order_2 = (t_ls_order*)order_2_void;
	if (order_1 == NULL || order_2 == NULL)
	{
		if (order_1 != NULL)
			return (-1);
		else if (order_2 != NULL)
			return (1);
		return (0);
	}
	return ((int)(order_1->stat.st_atime - order_2->stat.st_atime) * (-1));
}

int			order_compare_size(void *order_1_void, void *order_2_void)
{
	t_ls_order		*order_1;
	t_ls_order		*order_2;

	order_1 = (t_ls_order*)order_1_void;
	order_2 = (t_ls_order*)order_2_void;
	if (order_1 == NULL || order_2 == NULL)
	{
		if (order_1 != NULL)
			return (-1);
		else if (order_2 != NULL)
			return (1);
		return (0);
	}
	return ((int)(order_1->stat.st_size - order_2->stat.st_size) * (-1));
}
