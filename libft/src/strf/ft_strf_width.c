/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 00:48:23 by hush              #+#    #+#             */
/*   Updated: 2020/10/15 16:12:54 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//char	*ft_insert_s3(int len, char *res, int *flags)
//{
//	if (flags[ZERO] == 1 && flags[PRECISION] == 0 && flags[MINUS] == 0)
//	{
//		len = (int)ft_strlen(res);
//		if (len < flags[WIDTH])
//			res = ft_strjoin_free(ft_str_spam("0", flags[WIDTH] - len), res);
//	}
//	if (flags[WIDTH] > 0 && (len = (int)ft_strlen(res)) < flags[WIDTH])
//	{
//		if (flags[MINUS] == 1)
//			res = ft_strjoin_free(res, ft_str_spam(" ", flags[WIDTH] - len));
//		else
//			res = ft_strjoin_free(ft_str_spam(" ", flags[WIDTH] - len), res);
//	}
//	return (res);
//}


/*
** minus adjustment, length, fill with spaces or zeros
** precision width zero minus
*/

char	*ft_strf_width(const char *str, int width, char filler, t_bool align_left)
{
	char		*res;
	char 		fill[2];
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

