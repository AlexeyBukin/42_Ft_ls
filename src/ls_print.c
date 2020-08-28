/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls__print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:46:58 by hush              #+#    #+#             */
/*   Updated: 2020/08/28 07:04:35 by u18600003        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls_print_list2(t_entry *entry, t_sizes sizes)
{
	t_print		print;
	char		str_rwx[11];

	str_rwx[10] = '\0';
	while (entry != NULL)
	{
		ls_nullptr((ls_rwx(entry, str_rwx)));
		print.time_str = ft_strsub(ctime(&entry->stat.st_mtime), 4, 12);
		print.links_str = ft_strf_width(entry->link_num_str,
								sizes.max_len_links, ' ', FALSE);
		print.bytes_str = ft_strf_width(entry->size_str,
								sizes.max_len_size, ' ', FALSE);
		print.ownername = ft_strf_width(entry->owner,
					sizes.max_len_owner, ' ', TRUE);
		print.groupname = ft_strf_width(entry->group,
							sizes.max_len_group, ' ', TRUE);
		ft_printf("%s  %s %s  %s  %s %s %s\n", str_rwx, print.links_str,
			print.ownername, print.groupname,
			print.bytes_str, print.time_str, entry->name);
		free_print_list(&print);
		entry = entry->entry_next;
	}
}

void			ls_print_list3(t_ls_order *order_list, t_entry *entry)
{
	if (entry == NULL || str_10 == NULL)
		return (NULL);

	if (S_ISFIFO(entry->stat.st_mode))
		str_10[0] = 'p';
	else if (S_ISCHR(entry->stat.st_mode))
		str_10[0] = 'c';
	else if (S_ISDIR(entry->stat.st_mode))
		str_10[0] = 'd';
	else if (S_ISBLK(entry->stat.st_mode))
		str_10[0] = 'b';
	else if (S_ISREG(entry->stat.st_mode))
		str_10[0] = '-';
	else if (S_ISLNK(entry->stat.st_mode))
		str_10[0] = 'l';
	else if (S_ISSOCK(entry->stat.st_mode))
		str_10[0] = 's';
	else if (S_ISWHT(entry->stat.st_mode))
		str_10[0] = 'w';

	str_10[1] = (entry->stat.st_mode & S_IRUSR) ? 'r' : '-';
	str_10[2] = (entry->stat.st_mode & S_IWUSR) ? 'w' : '-';
	str_10[3] = (entry->stat.st_mode & S_IXUSR) ? 'x' : '-';
	str_10[4] = (entry->stat.st_mode & S_IRGRP) ? 'r' : '-';
	str_10[5] = (entry->stat.st_mode & S_IWGRP) ? 'w' : '-';
	str_10[6] = (entry->stat.st_mode & S_IXGRP) ? 'x' : '-';
	str_10[7] = (entry->stat.st_mode & S_IROTH) ? 'r' : '-';
	str_10[8] = (entry->stat.st_mode & S_IWOTH) ? 'w' : '-';
	str_10[9] = (entry->stat.st_mode & S_IXOTH) ? 'x' : '-';
	if (entry->attr == LS_ATTR_YES || entry->attr == LS_ATTR_ACL)
		str_10[10] = (entry->attr == LS_ATTR_YES) ? '@' : '+';
	else
		str_10[10] = ' ';
	return (str_10);
}

#define SIX_MONTH_IN_SECONDS 15552000

void	ls_print_list(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	t_entry		*entry;
	char		str_rwx[12];

	str_rwx[11];
	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (order_list->error == 0)
		{
			if (is_first == FALSE)
				ft_printf("\n");
			if ((input->order_num > 1 || (input->rec == TRUE && is_first == FALSE)) && order_list->is_dir == TRUE)
				ft_printf("%s:\n", order_list->name);
			is_first = FALSE;
			//biggest user str size
			entry = order_list->list;
			size_t dirsize = 0;
			size_t max_len_owner = 0;
			size_t max_len_group = 0;
			size_t max_len_size = 0;
			size_t max_len_links = 0;
			size_t len = 0;
			while (entry != NULL)
			{
				len = ft_strlen(entry->owner);
				if (len > max_len_owner)
					max_len_owner = len;
				len = ft_strlen(entry->group);
				if (len > max_len_group)
					max_len_group = len;
				entry->link_num_str = ft_ulltoa((unsigned long)entry->stat.st_nlink);
				len = ft_strlen(entry->link_num_str);
				if (len > max_len_links)
					max_len_links = len;
				entry->size_str = ft_ulltoa((unsigned long)entry->stat.st_size);
				len = ft_strlen(entry->size_str);
				if (len > max_len_size)
					max_len_size = len;
				dirsize += entry->stat.st_blocks;
				entry = entry->entry_next;
			}
			if (order_list->list != NULL && order_list->is_dir == TRUE)
				ft_printf("total %llu\n", dirsize);
			entry = order_list->list;
			while (entry != NULL)
			{
				ls_nullptr((ls_rwx(entry, str_rwx)));
				char * time_str;
				if (input->time_now - entry->stat.st_mtime < SIX_MONTH_IN_SECONDS)
					time_str = ft_strsub(ctime(&entry->stat.st_mtime), 4, 12);
				else
					time_str = ft_strjoin_free(ft_strsub(ctime(&entry->stat.st_mtime), 4, 7),
								ft_strsub(ctime(&entry->stat.st_mtime), 19, 5));
//				char * time_str = ft_strsub(ctime(&entry->stat.st_mtime), 4, 12);
				char * links_str = ft_strf_width(entry->link_num_str, max_len_links, ' ', FALSE);
				char * bytes_str = ft_strf_width(entry->size_str, max_len_size, ' ', FALSE);
				char * ownername = ft_strf_width(entry->owner, max_len_owner, ' ', TRUE);
				char * groupname = ft_strf_width(entry->group, max_len_group, ' ', TRUE);
				ft_printf("%s %s %s  %s  %s %s %s\n", str_rwx, links_str, ownername, groupname, bytes_str, time_str, entry->name);
				free(time_str);
				free(links_str);
				free(bytes_str);
				free(ownername);
				free(groupname);
				entry = entry->entry_next;
			}
		}
		order_list = order_list->next;
	}
}

void			ls_print_plain(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	t_entry		*entry;

	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (is_first == FALSE)
			ft_printf("\n");
		if (order_list->error == 0)
		{
			if ((input->order_num > 1 || (input->rec == TRUE && is_first == FALSE)) && order_list->is_dir == TRUE)
				ft_printf("%s:\n", order_list->name);
			entry = order_list->list;
			while (entry != NULL)
			{
				ft_printf("%s\n", entry->name);
				entry = entry->entry_next;
			}
		}
		is_first = FALSE;
		order_list = order_list->next;
	}
}
