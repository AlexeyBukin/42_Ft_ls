/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders_fill_stat.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:36:40 by kcharla           #+#    #+#             */
/*   Updated: 2020/10/17 17:36:40 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				entry_fill_link(t_entry *entry, t_input *input)
{
	char		buf[RDLINK_BUF_SIZE + 1];
	ssize_t		name_size;

	ls_nullptr(entry);
	ls_nullptr(input);
	if (lstat(entry->full_name, &(entry->stat)) != 0)
		ls_unknown_error(errno);
	if (input->list)
	{
		if ((name_size = readlink(entry->full_name, buf, RDLINK_BUF_SIZE)) < 0)
			ls_unknown_error(1);
		buf[name_size] = '\0';
		ls_nullptr(entry->name = ft_strjoin_3(entry->name, " -> ", buf));
	}
}

void				entry_set_attr(t_entry *entry)
{
	ssize_t			xattr;
	acl_entry_t		dummy;
	acl_t			acl;

	xattr = listxattr(entry->full_name, NULL, 0, XATTR_NOFOLLOW);
	acl = NULL;
	acl = acl_get_link_np(entry->full_name, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		entry->attr = LS_ATTR_YES;
	else if (acl != NULL)
		entry->attr = LS_ATTR_ACL;
	acl_free(acl);
}

void				entry_set_pwuid_group(t_entry *entry)
{
	t_passwd	*passwd;
	t_group		*group;

	if ((passwd = getpwuid(entry->stat.st_uid)) != NULL)
		entry->owner = ft_strdup(passwd->pw_name);
	else
		ls_unknown_error(errno);
	if ((group = getgrgid(entry->stat.st_gid)) != NULL)
		entry->group = ft_strdup(group->gr_name);
	else
		ls_unknown_error(errno);
}

void				order_list_fill_stat(t_ls_order *order_list, t_input *input)
{
	t_entry		*entry;

	while (order_list != NULL)
	{
		entry = order_list->list;
		while (entry != NULL)
		{
			if (order_list->is_dir == FALSE || entry->name[0] == '/')
				ls_nullptr((entry->full_name = ft_strdup(entry->name)));
			else
				ls_nullptr((entry->full_name =
						ft_strjoin_3(order_list->name, "/", entry->name)));
			if (entry->dirent.d_type == DT_LNK)
				entry_fill_link(entry, input);
			else if (stat(entry->full_name, &(entry->stat)) != 0)
				ls_unknown_error(errno);
			entry_set_pwuid_group(entry);
			entry_set_attr(entry);
			entry = entry->entry_next;
		}
		order_list = order_list->next;
	}
}
