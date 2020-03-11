/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_ent_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharla <kcharla@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 01:19:28 by kcharla           #+#    #+#             */
/*   Updated: 2020/03/11 07:48:07 by kcharla          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


t_entry				*ls_ent_main(char *name)
{
	t_entry			*entry;

	ls_nullptr(name);
	entry = (t_entry*)malloc(sizeof(t_entry));
	ls_nullptr(entry);
	entry->name = name;
	entry->error = LS_OK;
	entry->next = NULL;
	entry->prev = NULL;
	if (stat(name, &(entry->stat)) != 0)
	{
		if (errno == ENOENT)
		{
//			ft_putstr("ft_ls: no files!");
			entry->error = E_LS_NO_SUCH_FILE;
		}

		else if (errno == EACCES)
			entry->error = E_LS_PERMISSION_DENIED;
		else
			entry->error = E_LS_UNKNOWN_ERROR;
	}
	if (entry->error == E_LS_NO_SUCH_FILE)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(entry->name);
		ft_putstr(": No such file or directory\n");
	}
	return (entry);
}

t_entry				*ls_ent_create(t_dirent *dirent)
{
	t_entry			*entry;

	ls_nullptr(dirent);
	entry = (t_entry*)malloc(sizeof(t_entry));
	ls_nullptr(entry);
	entry->dirent = dirent;
	entry->name = dirent->d_name;
	entry->error = LS_OK;
	entry->next = NULL;
	entry->prev = NULL;
	return (entry);
}

t_entry				**ls_ent_get(t_input *input)
{
	int				i;
	t_entry			**entries;
	t_dirent		*tmp_ent;
	t_entry			*ptr;

	ls_nullptr(input);
	ls_nullptr(input->ent_names);
	entries = (t_entry**)malloc(sizeof(t_entry*) * (input->ent_num + 1));
	ls_nullptr(entries);
	entries[input->ent_num] = NULL;
	i = 0;
	while (i < (int)input->ent_num)
	{
		entries[i] = ls_ent_main(input->ent_names[i]);
		ls_nullptr(entries[i]);
//		if (entries[i]->error == E_LS_NO_SUCH_FILE)
//		{
//			ft_putstr("do_nothing...\n");
//			free(entries[i]);
//			i--;
//		}
//		else
//		if (entries[i]->stat.st_mode)
		if (entries[i]->error == LS_OK)
			if (S_ISDIR(entries[i]->stat.st_mode))
			{
				if (entries[i]->stat.st_mode & S_IRUSR)
				{
					ft_putstr("is dir@\n");
					entries[i]->dir = opendir(input->ent_names[i]);
					ft_putstr("is dir_2\n");
					ls_nullptr(entries[i]->dir);
					ft_putstr("is dir_3\n");
					ptr = entries[i];
					while ((tmp_ent = readdir(entries[i]->dir)) != NULL)
					{
						if (tmp_ent->d_name[0] == '.' && input->all == FALSE)
						{
							continue ;
						}
						ptr->next = ls_ent_create(tmp_ent);
						ptr->next->prev = ptr;
						ptr = ptr->next;
					}
					closedir(entries[i]->dir);
				}
				else
				{
					entries[i]->error = E_LS_PERMISSION_DENIED;
				}
			}
		i++;
	}
	//ft_putstr("entries\n");
	return (entries);
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