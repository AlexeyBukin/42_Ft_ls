/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_orders_create_rec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hinterfa <hinterfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 17:38:26 by kcharla           #+#    #+#             */
/*   Updated: 2020/12/01 04:52:45 by hinterfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_order			*ls_order_malloc(char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(order_name);
	ls_nullptr((order = (t_ls_order*)ft_memalloc(sizeof(t_ls_order))));
	order->name = order_name;
	order->is_dir = FALSE;
	order->list = NULL;
	return (order);
}

t_ls_order			*ls_order_error(t_ls_order *order, int error)
{
	if (order != NULL)
	{
		if (S_ISDIR(order->stat.st_mode))
		{
				// ft_printf("ERROR is dir: %s\n", order->name);
				order->is_dir = TRUE;
				order->error = error;
		}
		else
		{
			// ft_printf("ERROR is not dir: %s\n", order->name);
			order->is_dir = FALSE;
			ls_nullptr(order->list = ls_entry_nameonly(order->name));
		}
		
				// ft_printf("ERROR is not dir: %s\n", order->name);
		// ls_nullptr(order->list = ls_entry_nameonly(order->name));
	}
		

	return (order);
}

t_ls_order			*ls_order_create(t_input *input, char *order_name)
{
	t_ls_order		*order;

	ls_nullptr(input);
	ls_nullptr((order = ls_order_malloc(order_name)));
	// ft_printf("ft_ls order: '%s'\n", order_name);
	order->error = E_LS_NONE;
	if (lstat(order_name, &(order->stat)) != 0)
	{
		if (errno == ENOENT)
			ft_printf("ft_ls: %s: No such file or directory\n", order_name);
		else if (errno == EACCES)
		{
			return (ls_order_error(order, E_LS_PERMISSION_DENIED));
		}
		else
		{
			// ft_printf("ERRNO IS: %d, %s, %s\n", errno, order->name, strerror(errno));
			ls_unknown_error(errno);
		}
		// ft_printf("ERRNO TOUCHED \'%s\'\n", order->name);
	}
	if (!(order->stat.st_mode & S_IRUSR))
	{
		// ft_printf("ENTRY EACCESS TOUCHED \'%s\'\n", order->name);
		return (ls_order_error(order, E_LS_PERMISSION_DENIED));
	}
	if (S_ISDIR(order->stat.st_mode))
	{
		// ft_printf("ISDIR TOUCHED \'%s\'\n", order->name);
		order->is_dir = TRUE;
		order->list = ls_entry_list_create(input, order);
	}
	else
	{
		// ft_printf("ENTRY NAMEONLY TOUCHED \'%s\'\n", order->name);
		order->is_dir = FALSE;
		order->list = ls_entry_nameonly(order_name);
	}
		
	return (order);
}

void				ls_order_create_rec_helper(t_entry *entry,
						t_ls_order **order, char *order_name, t_input *input)
{
	// ft_printf("\nft_ls order from dir: %s\n", order_name);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->name, ".") != 0 &&
				ft_strcmp(entry->name, "..") != 0)
		{
			(*order)->next = ls_order_create_rec(input,
								ft_strjoin_3(order_name, "/", entry->name));

			// ft_printf("next name: %s\n", (*order)->next->name);
			
			if ((*order)->next->error == E_LS_PLAIN_FILE)
			{
				// ft_printf("next name plain: %s\n", (*order)->next->name);
				free_order_list((*order)->next);
				(*order)->next = NULL;
			}
			while ((*order)->next != NULL)
				*order = (*order)->next;
		}
		entry = entry->entry_next;
	}
	// ft_printf("ft_ls order end from dir: %s\n\n", order_name);
}

t_ls_order			*ls_order_create_rec(t_input *input, char *order_name)
{
	t_ls_order		*order;
	t_ls_order		*order_rec;

	// ft_printf("ft_ls order create: '%s'\n", order_name);
	ls_nullptr((order_rec = ls_order_create(input, order_name)));
	if (order_rec->is_dir == FALSE && order_rec->error == E_LS_NONE)
	{
		order_rec->error = E_LS_PLAIN_FILE;
		return (order_rec);
	}
	order = order_rec;
	if (order_rec->is_dir == TRUE)
	{
		ls_order_create_rec_helper(order->list, &order, order_name, input);
	}
	return (order_rec);
}
