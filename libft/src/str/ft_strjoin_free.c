/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 20:20:34 by kcharla           #+#    #+#             */
/*   Updated: 2020/09/20 15:49:42 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	res = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		return (NULL);
	res = ft_strcpy(res, s1);
	res = ft_strcat(res, s2);
	free(s1);
	free(s2);
	return (res);
}

char	*ft_strjoin_free_2(char *s1, char *s2)
{
	return (ft_strjoin_free(s1, s2));
}

char	*ft_strjoin_free_3(char *s1, char *s2, char *s3)
{
	return (ft_strjoin_free(ft_strjoin_free(s1, s2), s3));
}

char	*ft_strjoin_free_4(char *s1, char *s2, char *s3, char *s4)
{
	return (ft_strjoin_free(ft_strjoin_free(s1, s2), ft_strjoin_free(s3, s4)));
}
