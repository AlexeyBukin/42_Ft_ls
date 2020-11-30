/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:52:27 by kcharla           #+#    #+#             */
/*   Updated: 2020/11/30 23:20:08 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	size_t			len;
	char			*str;

	str = (char*)s;
	len = ft_strlen(s);
	str[len] = '\n';
	write(1, s, len + 1);
	str[len] = '\0';
}
