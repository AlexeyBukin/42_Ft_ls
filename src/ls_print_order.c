/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_order.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 18:47:56 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/01 05:34:26 by hinterfa         ###   ########.fr       */
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

void	ls_print_order_entry_helper(t_entry *entry, t_ls_max *max_len,
									size_t *dirsize)
{
	size_t		len;

	if (entry == NULL || max_len == NULL || dirsize == NULL)
		return ;
	len = ft_strlen(entry->owner);
	if (len > max_len->owner)
		max_len->owner = len;
	len = ft_strlen(entry->group);
	if (len > max_len->group)
		max_len->group = len;
	entry->link_num_str = ft_ulltoa((unsigned long)entry->stat.st_nlink);
	len = ft_strlen(entry->link_num_str);
	if (len > max_len->links)
		max_len->links = len;
	entry->size_str = ft_ulltoa((unsigned long)entry->stat.st_size);
	len = ft_strlen(entry->size_str);
	if (len > max_len->size)
		max_len->size = len;
	*dirsize += entry->stat.st_blocks;
}

void	ls_print_order_helper(t_entry *entry, t_ls_max *max_len,
								t_input *input, char *str_rwx)
{
	time_t		time_to_show;
	char		*time_str;
	char		*links_str;
	char		*bytes_str;
	char		*ownername;
	char		*groupname;

	if (entry == NULL || max_len == NULL || input == NULL || str_rwx == NULL)
		return ;
	ls_nullptr((ls_rwx(entry, str_rwx)));
	time_to_show = entry->stat.st_mtime;
	if (input->time_sort == SORT_TIME_ACCESS)
		time_to_show = entry->stat.st_atime;

	if (input->time_now - time_to_show < SIX_MONTH_IN_SECONDS)
		time_str = ft_strsub(ctime(&time_to_show), 4, 12);
	else
		time_str = ft_strjoin_free(ft_strsub(ctime(&time_to_show),
				4, 7), ft_strsub(ctime(&time_to_show), 19, 5));
	links_str = ft_strf_width(entry->link_num_str, max_len->links, ' ', FALSE);
	bytes_str = ft_strf_width(entry->size_str, max_len->size, ' ', FALSE);
	ownername = ft_strf_width(entry->owner, max_len->owner, ' ', TRUE);
	groupname = ft_strf_width(entry->group, max_len->group, ' ', TRUE);
	ft_printf("%s %s %s  %s  %s %s %s\n", str_rwx, links_str, ownername,
					groupname, bytes_str, time_str, entry->name);
	free(time_str);
	free(links_str);
	free(bytes_str);
	free(ownername);
	free(groupname);
}

void	ls_print_order_header(t_ls_order *order, t_input *input,
								t_bool is_first)
{
	if (order == NULL || input == NULL)
		return ;
	if (is_first == FALSE)
		ft_printf("\n");
	if ((input->order_num > 1 || (input->rec == TRUE && is_first == FALSE))
													&& order->is_dir == TRUE)
		ft_printf("%s:\n", order->name);
	// *is_first = FALSE;
}
