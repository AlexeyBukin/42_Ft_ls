/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 20:02:10 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/02 02:00:19 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_unknown_error(int err_id)
{
	(void)err_id;
	exit(0);
}

/*
** replacing 'e' with illegal option c
** writing to error stream
*/

void	ls_illegal_option(char c)
{
	char		*str;

	str = ft_strdup("/bin/ls: illegal option -- e\n"LS_USAGE"\n");
	str[27] = c;
	ft_putstr_fd(str, 2);
	ft_free(str);
	exit(1);
}

void	ls_nullptr(const void *ptr)
{
	if (ptr == NULL)
	{
		ft_printf("ft_ls: Null pointer exception\n");
		exit(0);
	}
}

void	ls_nullptr2(const void *ptr, const void *ptr2)
{
	ls_nullptr(ptr);
	ls_nullptr(ptr2);
}
