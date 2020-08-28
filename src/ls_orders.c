/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hush <hush@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 01:00:57 by hush              #+#    #+#             */
/*   Updated: 2020/08/28 04:41:14 by u18600003        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define READLINK_BUF_SIZE 1023
void	entry_fill_link(t_entry *entry, t_input *input)
{
	char		buf[READLINK_BUF_SIZE + 1];
	ssize_t		name_size;

	ls_nullptr(entry);
	ls_nullptr(input);
	if (lstat(entry->full_name, &(entry->stat)) != 0)
		ls_unknown_error(errno);
	if (input->list)
	{
		if ((name_size = readlink(entry->full_name, buf, READLINK_BUF_SIZE)) < 0)
			ls_unknown_error(1);
		buf[name_size] = '\0';
		ls_nullptr(entry->name = ft_strjoin_3(entry->name, " -> ", buf));
	}

}

void	order_list_fill_stat(t_ls_order *order_list, t_input *input)
{
	t_passwd	*passwd;
	t_group		*group;
	t_entry		*entry;

	while (order_list != NULL)
	{
		entry = order_list->list;
		while (entry != NULL)
		{
			ls_nullptr((entry->full_name = ft_strjoin_3(order_list->name, "/", entry->name)));
			if (entry->dirent.d_type == DT_LNK)
				entry_fill_link(entry, input);
			else if (stat(entry->full_name, &(entry->stat)) != 0)
				ls_unknown_error(errno);

			if ((passwd = getpwuid(entry->stat.st_uid)) != NULL)
				entry->owner = ft_strdup(passwd->pw_name);
			else
				ls_unknown_error(errno);

			if ((group = getgrgid(entry->stat.st_gid)) != NULL)
				entry->group = ft_strdup(group->gr_name);
			else
				ls_unknown_error(errno);
			//getting xattr aka '@' and acl aka '+'
			ssize_t xattr = listxattr(entry->full_name, NULL, 0, XATTR_NOFOLLOW);
			acl_entry_t dummy;

			acl_t acl = NULL;
			acl = acl_get_link_np(entry->full_name, ACL_TYPE_EXTENDED);
			if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
				acl_free(acl);
				acl = NULL;
			}
			if (xattr < 0)
				xattr = 0;
			if (xattr > 0)
				entry->attr = LS_ATTR_YES;
			else if (acl != NULL)
				entry->attr = LS_ATTR_ACL;


			entry = entry->entry_next;
		}
		order_list = order_list->next;
	}
}

static
t_ls_order		*ls_order_malloc(char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(order_name);
	ls_nullptr((order = (t_ls_order*)ft_memalloc(sizeof(t_ls_order))));
	order->name = order_name;
	//memalloc() does bzero()...
//	order->next = NULL;
//	order->list = NULL;
//	order->list_size = 0;
//	order->error = 0;
//	order->is_dir = FALSE;
	return (order);
}

static
t_ls_order		*ls_order_create(t_input *input, char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(input);
	ls_nullptr((order = ls_order_malloc(order_name)));
	if (lstat(order_name, &(order->stat)) != 0)
	{
		if (errno == ENOENT)
			order->error = E_LS_NO_SUCH_FILE;
		else if (errno == EACCES)
			order->error = E_LS_PERMISSION_DENIED;
		else
			ls_unknown_error(errno);
	}
	else if (!(order->stat.st_mode & S_IRUSR))
		order->error = E_LS_PERMISSION_DENIED;
	else if (S_ISDIR(order->stat.st_mode))
	{
		order->is_dir = TRUE;
		order->list = ls_entry_list_create(input, order);
	}
	if (order->error == E_LS_NO_SUCH_FILE)
		ft_printf("ft_ls: %s: No such file or directory\n", order_name);
	return (order);
}

static
t_ls_order		*ls_order_create_rec(t_input *input, char *order_name)
{
	t_entry			*entry;
	t_ls_order		*order;
	t_ls_order		*order_rec;

	ls_nullptr((order_rec = ls_order_create(input, order_name)));
	if (order_rec->is_dir == FALSE)
		return (NULL);
	order = order_rec;
	entry = order->list;
	while (entry != NULL)
	{
		if (ft_strcmp(entry->name, ".") != 0 && ft_strcmp(entry->name, "..") != 0)
		{
			order->next = ls_order_create_rec(input,
				ft_strjoin_3(order_name, "/", entry->name));
			while (order->next != NULL)
				order = order->next;
		}
		entry = entry->entry_next;
	}
	return (order_rec);
}

static
t_ls_order			*ls_order_list_create_rec(t_input *input,
					t_ls_order *order_list)
{
	t_ls_order			*order_tmp;
	t_ls_order			*order;
	size_t 				i;

	ls_nullptr(input);
	order_tmp = NULL;
	i = 0;
	while (i < input->order_num)
	{
		ls_nullptr((order = ls_order_create_rec(input, input->order_names[i])));
		if (order_list != NULL)
		{
			if (order_tmp == NULL)
				order_tmp = order_list;
			while (order_tmp->next != NULL)
				order_tmp = order_tmp->next;
			order_tmp->next = order;
		}
		else
			order_list = order;
		i++;
	}
	return (order_list);
}

static
t_ls_order			*ls_order_list_create_plain(t_input *input,
					t_ls_order *order_list)
{
	t_ls_order			*order_tmp;
	t_ls_order			*order;
	size_t 				i;

	ls_nullptr(input);
	order_tmp = NULL;
	i = 0;
	while (i < input->order_num)
	{
		ls_nullptr((order = ls_order_create(input, input->order_names[i])));
		if (order_list != NULL)
		{
			if (order_tmp == NULL)
				order_tmp = order_list;
			order_tmp->next = order;
		}
		else
			order_list = order;
		i++;
	}
	return (order_list);
}

t_ls_order			*ls_order_list_create(t_input *input)
{
	t_ls_order			*order_list;

	order_list = NULL;
	if (input->rec == TRUE)
		return (ls_order_list_create_rec(input, order_list));
	return (ls_order_list_create_plain(input, order_list));
}
