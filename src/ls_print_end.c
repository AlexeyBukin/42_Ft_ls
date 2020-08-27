/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 13:49:31 by gekans            #+#    #+#             */
/*   Updated: 2020/08/25 14:08:18 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ls_print(t_ls_order *order_list, t_input *input)
{
	ls_nullptr(input);
	if (input->list == TRUE)
		ls_print_list(order_list, input);
	else
		ls_print_plain(order_list, input);
}

void			print_order_list(t_ls_order *order_list)
{
	t_ls_order	*tmp_ord;
	t_entry		*temp;

	tmp_ord = order_list;
	while (tmp_ord != NULL)
	{
		ft_printf("main dir : %s, p=%p, next=%p\n",
					tmp_ord->name, tmp_ord, tmp_ord->next);
		temp = tmp_ord->list;
		while (temp != NULL)
		{
			ft_printf("     ent : \'%20s\', p=%p, next=%p\n",
					temp->name, temp, temp->entry_next);
			temp = temp->entry_next;
		}
		tmp_ord = tmp_ord->next;
	}
}

void			print_flags(t_input *input)
{
	ft_printf("R = %c\n", input->rec + '0');
	ft_printf("a = %c\n", input->show + '0');
	ft_printf("l = %c\n", input->list + '0');
	ft_printf("r = %c\n", input->rev + '0');
	ft_printf("t = %c\n", input->time_sort + '0');
}

char			*ls_rwx2(t_entry *entry, char *str_10)
{
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
	return (str_10);
}

char			*ls_rwx(t_entry *entry, char *str_10)
{
	if (entry == NULL || str_10 == NULL)
		return (NULL);
	ls_rwx2(entry, str_10);
	str_10[1] = (entry->stat.st_mode & S_IRUSR) ? 'r' : '-';
	str_10[2] = (entry->stat.st_mode & S_IWUSR) ? 'w' : '-';
	str_10[3] = (entry->stat.st_mode & S_IXUSR) ? 'x' : '-';
	str_10[4] = (entry->stat.st_mode & S_IRGRP) ? 'r' : '-';
	str_10[5] = (entry->stat.st_mode & S_IWGRP) ? 'w' : '-';
	str_10[6] = (entry->stat.st_mode & S_IXGRP) ? 'x' : '-';
	str_10[7] = (entry->stat.st_mode & S_IROTH) ? 'r' : '-';
	str_10[8] = (entry->stat.st_mode & S_IWOTH) ? 'w' : '-';
	str_10[9] = (entry->stat.st_mode & S_IXOTH) ? 'x' : '-';
	return (str_10);
}
