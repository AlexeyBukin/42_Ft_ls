/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 18:49:38 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/30 23:22:24 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_abs(int a)
{
	if (a < 0)
		return (a * (-1));
	return (a);
}

long long int	ft_absl(long long int a)
{
	if (a < 0)
		return (a * (-1));
	return (a);
}

double			ft_absd(double a)
{
	if (a < 0)
		return (a * (-1));
	return (a);
}
