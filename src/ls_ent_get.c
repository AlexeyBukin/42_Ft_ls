/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_ent_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:19:28 by kcharla           #+#    #+#             */
/*   Updated: 2020/03/11 01:22:02 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


t_entry				*ls_ent_create(t_dirent *entry, t_stat *input)
{
	
}

t_entry				**ls_ent_get(char **dirs, t_input *input)
{
	t_entry			**entries;

	if (input == NULL || dirs == NULL)
		return (NULL);
	ls_get_names_size()
	return (NULL);
}


//int					ls_is_unreachable(char *ent_name)
//{
//	struct stat info;
//
//	if (ent_name == NULL)
//		return (E_LS_NULL_POINTER);
//	if (stat(ent_name, &info) != 0)
//	{
//		if (errno == ENOENT)
//		{
//			return (E_LS_NO_SUCH_FILE);
//		}
//		else if (errno == EACCES)
//		{
//			return (E_LS_PERMISSION_DENIED);
//		}
//		return (E_LS_UNKNOWN_ERROR);
//	}
//	return (LS_OK);
//}