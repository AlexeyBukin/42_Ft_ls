/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_attributes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 00:17:29 by hinterfa          #+#    #+#             */
/*   Updated: 2020/12/02 00:17:34 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_rwx_filetype(t_entry *entry, char *filetype)
{
	if (entry == NULL || filetype == NULL)
		return (-1);
	if (S_ISFIFO(entry->stat.st_mode))
		*filetype = 'p';
	else if (S_ISCHR(entry->stat.st_mode))
		*filetype = 'c';
	else if (S_ISDIR(entry->stat.st_mode))
		*filetype = 'd';
	else if (S_ISBLK(entry->stat.st_mode))
		*filetype = 'b';
	else if (S_ISREG(entry->stat.st_mode))
		*filetype = '-';
	else if (S_ISLNK(entry->stat.st_mode))
		*filetype = 'l';
	else if (S_ISSOCK(entry->stat.st_mode))
		*filetype = 's';
	else if (S_ISWHT(entry->stat.st_mode))
		*filetype = 'w';
	else
		return (-1);
	return (0);
}

char	*ls_rwx(t_entry *entry, char *str_10)
{
	if (entry == NULL || str_10 == NULL)
		return (NULL);
	if (ls_rwx_filetype(entry, str_10))
		return (NULL);
	str_10[1] = (entry->stat.st_mode & S_IRUSR) ? 'r' : '-';
	str_10[2] = (entry->stat.st_mode & S_IWUSR) ? 'w' : '-';
	str_10[3] = (entry->stat.st_mode & S_IXUSR) ? 'x' : '-';
	str_10[4] = (entry->stat.st_mode & S_IRGRP) ? 'r' : '-';
	str_10[5] = (entry->stat.st_mode & S_IWGRP) ? 'w' : '-';
	str_10[6] = (entry->stat.st_mode & S_IXGRP) ? 'x' : '-';
	str_10[7] = (entry->stat.st_mode & S_IROTH) ? 'r' : '-';
	str_10[8] = (entry->stat.st_mode & S_IWOTH) ? 'w' : '-';
	str_10[9] = (entry->stat.st_mode & S_IXOTH) ? 'x' : '-';
	str_10[10] = ' ';
	if (entry->attr == LS_ATTR_YES || entry->attr == LS_ATTR_ACL)
		str_10[10] = (entry->attr == LS_ATTR_YES) ? '@' : '+';
	return (str_10);
}
