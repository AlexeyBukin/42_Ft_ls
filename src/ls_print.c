/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls__print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 18:46:58 by hush              #+#    #+#             */
/*   Updated: 2020/08/28 03:32:43 by u18600003        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//void	print_order_list(t_ls_order *order_list)
//{
//	t_ls_order *tmp_ord = order_list;
//	while (tmp_ord != NULL)
//	{
//		ft_printf("main dir : %s, p=%p, next=%p\n", tmp_ord->name, tmp_ord, tmp_ord->next);
//		t_entry *temp = tmp_ord->list;
//		while (temp != NULL)
//		{
//			ft_printf("     ent : \'%20s\', p=%p, next=%p\n", temp->name, temp, temp->entry_next);
//			temp = temp->entry_next;
//		}
//		tmp_ord = tmp_ord->next;
//	}
//}

//void	print_flags(t_input *input)
//{
//	ft_printf("R = %c\n", input->rec + '0');
//	ft_printf("a = %c\n", input->show + '0');
//	ft_printf("l = %c\n", input->list + '0');
//	ft_printf("r = %c\n", input->rev + '0');
//	ft_printf("t = %c\n", input->time_sort + '0');
//}

char	*ls_rwx(t_entry *entry, char *str_10)
{
	if (entry == NULL || str_10 == NULL)
		return (NULL);

	if (entry->dirent.d_type == DT_UNKNOWN)
		str_10[0] = 'u';
	else if (entry->dirent.d_type == DT_FIFO)
		str_10[0] = 'p';
	else if (entry->dirent.d_type == DT_CHR)
		str_10[0] = 'c';
	else if (entry->dirent.d_type == DT_DIR)
		str_10[0] = 'd';
	else if (entry->dirent.d_type == DT_BLK)
		str_10[0] = 'b';
	else if (entry->dirent.d_type == DT_REG)
		str_10[0] = '-';
	else if (entry->dirent.d_type == DT_LNK)
		str_10[0] = 'l';
	else if (entry->dirent.d_type == DT_SOCK)
		str_10[0] = 's';
	else if (entry->dirent.d_type == DT_WHT)
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

void	ls_print_list(t_ls_order *order_list, t_input *input)
{
	t_bool		is_first;
	t_entry		*entry;
	char		str_rwx[12];

	(void)input;
	str_rwx[11] = '\0';
	ls_nullptr(order_list);
	is_first = TRUE;
	while (order_list != NULL)
	{
		if (order_list->error == 0)
		{
			if (is_first == FALSE)
				ft_printf("\n");
			if (input->order_num > 1 || (input->rec == TRUE && is_first == FALSE))
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
			if (order_list->list != NULL)
				ft_printf("total %llu\n", dirsize);
			entry = order_list->list;
			while (entry != NULL)
			{
				ls_nullptr((ls_rwx(entry, str_rwx)));
				char * time_str = ft_strsub(ctime(&entry->stat.st_mtime), 4, 12);
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
			if (input->order_num > 1 || (input->rec == TRUE && is_first == FALSE))
				ft_printf("%s:\n", order_list->name);
			entry = order_list->list;
			while (entry != NULL)
			{
//				ft_printf("%s  ", entry->name);
				ft_printf("%s\n", entry->name);
				entry = entry->entry_next;
			}
//			if (order_list->list != NULL)
//				ft_printf("\n");
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