/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 19:48:41 by gekans            #+#    #+#             */
/*   Updated: 2020/08/24 19:48:44 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_unknown_error(int err_id)
{
	ft_printf("ft_ls: Unknown error: %d\n", err_id);
	exit(0);
}

void	ls_illegal_option(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n%s\n", c, LS_USAGE);
	exit(0);
}

void	ls_nullptr(const void *ptr)
{
	if (ptr == NULL)
	{
		ft_printf("ft_ls: Null pointer exception\n");
		exit(0);
	}
}
