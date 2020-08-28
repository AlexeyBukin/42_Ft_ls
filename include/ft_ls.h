/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekans <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:09:52 by gekans            #+#    #+#             */
/*   Updated: 2020/08/25 17:09:55 by gekans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/stat.h>
#include <sys/acl.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include "libft.h"

//typedef struct _dirdesc {
//	int	dd_fd;		/* file descriptor associated with directory */
//	long	dd_loc;		/* offset in current buffer */
//	long	dd_size;	/* amount of data returned by getdirentries */
//	char	*dd_buf;	/* data buffer */
//	int	dd_len;		/* size of data buffer */
//	long	dd_seek;	/* magic cookie returned by getdirentries */
//	long	dd_rewind;	/* magic cookie for rewinding */
//	int	dd_flags;	/* flags for readdir */
//	pthread_mutex_t	dd_lock; /* for thread locking */
//	struct _telldir *dd_td;	/* telldir position recording */
//} DIR;

//struct dirent { /* when _DARWIN_FEATURE_64_BIT_INODE is defined */
//	ino_t      d_fileno;     /* file number of entry */
//	__uint16_t d_seekoff;    /* seek offset (optional, used by servers) */
//	__uint16_t d_reclen;     /* length of this record */
//	__uint16_t d_namlen;     /* length of string in d_name */
//	__uint8_t  d_type;       /* file type, see below */
//	char    d_name[1024];    /* name must be no longer than this */
//};

//      *
//      * File types [d_type]
//      */
//#define DT_UNKNOWN       0
//#define DT_FIFO          1
//#define DT_CHR           2
//#define DT_DIR           4
//#define DT_BLK           6
//#define DT_REG           8
//#define DT_LNK          10
//#define DT_SOCK         12
//#define DT_WHT          14

//# define LS_USAGE "usage: ft_ls [-Ralrt] [file ...]"
# define LS_USAGE "usage: ls [-@ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1%] [file ...]"

typedef struct dirent	t_dirent;
typedef struct stat	t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef enum		e_sort_time
{
	SORT_TIME_NONE,
	SORT_TIME_MOD,
	SORT_TIME_ACCESS
}					t_sort_time;

typedef enum		e_show
{
	SHOW_VISIBLE,
	SHOW_ALL,
	SHOW_HIDDEN
}					t_show;

typedef enum		e_ls_attr
{
	LS_ATTR_NO,
	LS_ATTR_YES,
	LS_ATTR_ACL
}					t_ls_attr;

//TODO implement -F fancy

typedef struct		s_input
{
	char			**order_names;
	size_t			order_num;
	t_show			show;
	t_bool			rec;
	t_bool			rev;
	t_bool			list;
	t_sort_time		time_sort;
	t_bool			fancy;
	time_t			time_now;
}					t_input;

typedef struct		s_listable
{
	struct s_listable	*next;
}					t_listable;

typedef struct		s_entry
{
	struct s_entry	*entry_next;
	char			*name;
	char			*full_name;
	t_dirent		dirent;
	t_stat			stat;
	char 			*owner;
	char 			*group;
	char 			*link_num_str;
	char 			*size_str;
	t_ls_attr		attr;
}					t_entry;

typedef struct		s_ls_order
{
	struct s_ls_order	*next;
	char				*name;
	char				*full_name;
	t_stat				stat;
	t_bool				is_dir;
	int					error;
	DIR					*dir;
	size_t				list_size;
	t_entry				*list;
}					t_ls_order;

typedef enum		e_ls_values
{
	LS_OK = 0,
}					t_ls_values;

typedef enum		e_ls_error
{
	E_LS_NULL_POINTER = -64,
	E_LS_ILLEGAL_OPTION,
	E_LS_NO_SUCH_FILE,
	E_LS_PERMISSION_DENIED,
	E_LS_UNKNOWN_ERROR,
}					t_ls_error;

typedef enum		e_param_res
{
	PARAM_ERROR = -1,
	PARAM_UNSET,
	PARAM_FILE,
	PARAM_FLAG,
	PARAM_DOUBLE_DASH
}					t_param_res;

typedef struct		s_print
{
	char *time_str;
	char *links_str;
	char *bytes_str;
	char *ownername;
	char *groupname;
}					t_print;

typedef struct		s_sizes
{
	size_t dirsize;
	size_t max_len_owner;
	size_t max_len_group;
	size_t max_len_size;
	size_t max_len_links;
	size_t len;
}					t_sizes;

void				free_print_list(t_print *print);
void				print_order_list(t_ls_order *order_list);
void				ls_flags(int ac, char **av, t_input *input);
t_entry				**ls_get_rights(t_entry **entries);
t_entry				**ls_ent_get(t_input *input);
t_entry				**ls_ent_get_rec(char **dirs, t_input *input);
void				ls_print(t_ls_order *order_list, t_input *input);
int					ls_print_short(t_entry **entries, t_input *input);
int					ls_print_long(t_entry **entries, t_input *input);
t_entry				*ls_entry_list_create(t_input *input, t_ls_order *order);
t_entry				*ls_entry_nameonly(char *name);
t_ls_order			*ls_order_list_create(t_input *input);

void				order_list_fill_stat(t_ls_order *order_list, t_input *input);
//void				order_list_fill_stat(t_ls_order *order_list);

/*
** ls_sort.c
*/

t_ls_order			*ls_entry_list_sort(t_entry *entry_list, t_input *input);
t_ls_order			*ls_order_list_sort(t_ls_order *order_list, t_input *input);
void				free_order_list(t_ls_order *order_list);
void				free_entry_list(t_entry *e_list);
void				ls_unknown_error(int err_id);
void				ls_illegal_option(char c);
void				ls_nullptr(const void *ptr);
t_listable			*merge_lists(t_listable *list_1, t_listable *list_2,
									int (compare)(void*, void*));
int					entry_compare_alphabet(void *en_1_void, void *en_2_void);
int					order_compare_time(void *order_1_void, void *order_2_void);
int					order_compare_alphabet(void *order_1_void,
										void *order_2_void);
t_listable			*sort_listable(t_listable *list,
				int (compare)(void*, void*));
char				*ls_rwx(t_entry *entry, char *str_10);
void				ls_print_list(t_ls_order *order_list, t_input *input);
void				ls_print_plain(t_ls_order *order_list, t_input *input);
int					ls_enter_flag(char c, t_input *input);
void				ls_add_order_name(t_input *input, char *order_name);
t_bool				arg_is_dot(char *arg);
t_bool				arg_is_double_dash(char *arg);
void				ls_check_arg(char *arg, t_bool *flags_done, t_input *input);
t_ls_order			*ls_order_list_create_plain(t_input *input,
					t_ls_order *order_list);
t_ls_order			*ls_order_list_create_rec(t_input *input,
					t_ls_order *order_list);
t_ls_order			*ls_order_create_rec(t_input *input, char *order_name);
t_ls_order			*ls_order_create(t_input *input, char *order_name);
t_ls_order			*ls_order_malloc(char *order_name);

#endif
