/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:48:23 by hush              #+#    #+#             */
/*   Updated: 2020/11/30 23:21:42 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strf_width(const char *str, int width,
				char filler, t_bool align_left)
{
	char		*res;
	char		fill[2];
	int			len;

	if ((res = ft_strdup(str)) == NULL)
		return (NULL);
	len = (int)ft_strlen(res);
	if (len < width)
	{
		fill[0] = ' ';
		if (filler > 0)
			fill[0] = filler;
		fill[1] = '\0';
		if (align_left == TRUE)
			res = ft_strjoin_free(res, ft_str_spam(fill, width - len));
		else
			res = ft_strjoin_free(ft_str_spam(fill, width - len), res);
	}
	return (res);
}
