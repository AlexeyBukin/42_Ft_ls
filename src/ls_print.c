/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls__print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:46:58 by hush              #+#    #+#             */
/*   Updated: 2020/09/20 19:55:20 by kcharla          ###   ########.fr       */
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

typedef struct		s_ls_max
{
	size_t			owner;
	size_t			group;
	size_t			size;
	size_t			links;
}					t_ls_max;

//TODO norme
void	ls_print_order(t_ls_order *order, t_input *input, t_bool *is_first, char *str_rwx)
{
	t_entry		*entry;

	if (order == NULL || input == NULL || str_rwx == NULL || is_first == NULL)
		return ;
	if (*is_first == FALSE)
		ft_printf("\n");
	if ((input->order_num > 1 || (input->rec == TRUE && *is_first == FALSE)) && order->is_dir == TRUE)
		ft_printf("%s:\n", order->name);
	*is_first = FALSE;
	//biggest user str size
	entry = order->list;
	size_t dirsize = 0;
	t_ls_max	max_len;
	ft_bzero(&max_len, sizeof(t_ls_max));
//	size_t max_len_owner = 0;
//	size_t max_len_group = 0;
//	size_t max_len_size = 0;
//	size_t max_len_links = 0;
	size_t		len;
	while (entry != NULL)
	{
		len = ft_strlen(entry->owner);
		if (len > max_len.owner)
			max_len.owner = len;
		len = ft_strlen(entry->group);
		if (len > max_len.group)
			max_len.group = len;
		entry->link_num_str = ft_ulltoa((unsigned long)entry->stat.st_nlink);
		len = ft_strlen(entry->link_num_str);
		if (len > max_len.links)
			max_len.links = len;
		entry->size_str = ft_ulltoa((unsigned long)entry->stat.st_size);
		len = ft_strlen(entry->size_str);
		if (len > max_len.size)
			max_len.size = len;
		dirsize += entry->stat.st_blocks;
		entry = entry->entry_next;
	}
	if (order->list != NULL && order->is_dir == TRUE)
		ft_printf("total %llu\n", dirsize);
	entry = order->list;
	while (entry != NULL)
	{
		ls_nullptr((ls_rwx(entry, str_rwx)));
		char * time_str;
		if (input->time_now - entry->stat.st_mtime < SIX_MONTH_IN_SECONDS)
			time_str = ft_strsub(ctime(&entry->stat.st_mtime), 4, 12);
		else
			time_str = ft_strjoin_free(ft_strsub(ctime(&entry->stat.st_mtime), 4, 7),
									   ft_strsub(ctime(&entry->stat.st_mtime), 19, 5));
		char * links_str = ft_strf_width(entry->link_num_str, max_len.links, ' ', FALSE);
		char * bytes_str = ft_strf_width(entry->size_str, max_len.size, ' ', FALSE);
		char * ownername = ft_strf_width(entry->owner, max_len.owner, ' ', TRUE);
		char * groupname = ft_strf_width(entry->group, max_len.group, ' ', TRUE);
		ft_printf("%s %s %s  %s  %s %s %s\n", str_rwx, links_str, ownername, groupname, bytes_str, time_str, entry->name);
		free(time_str);
		free(links_str);
		free(bytes_str);
		free(ownername);
		free(groupname);
		entry = entry->entry_next;
	}
}

void	ls_print_list(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	char		str_rwx[12];

	str_rwx[11] = '\0';
	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (order_list->error == 0)
			ls_print_order(order_list, input, &is_first, str_rwx);
		order_list = order_list->next;
	}
}

void	ls_print_plain(t_ls_order *order_list, t_input *input)
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


void	ls_print(t_ls_order *order_list, t_input *input)
{
	ls_nullptr(input);
	if (input->list == TRUE)
		ls_print_list(order_list, input);
	else
		ls_print_plain(order_list, input);
}
