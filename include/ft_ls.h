#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
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

# define LS_USAGE "usage: ft_ls [-Ralrt] [file ...]"

typedef struct		dirent	t_dirent;
typedef struct		stat	t_stat;

typedef struct		s_input
{
	char			**order_names;
	size_t			order_num;

	t_bool			all;
	t_bool			rec;
	t_bool			rev;
	t_bool			list;
	t_bool			time;

	t_bool			p_slash;
}					t_input;

typedef struct		s_entry
{
	t_dirent		dirent;
	t_stat			stat;
	char 			*name;
	struct s_entry	*entry_next;
	struct s_entry	*prev;
}					t_entry;

typedef struct		s_ls_order
{
	char 				*name;
	t_stat				stat;
	t_bool				is_dir;
	int					error;
	struct s_ls_order	*next;
	struct s_ls_order	*prev;
	DIR					*dir;
	size_t 				list_size;
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

void	print_order_list(t_ls_order *order_list);

void 				ls_flags(int ac, char **av, t_input *input);

t_entry				**ls_get_rights(t_entry **entries);

t_entry				**ls_ent_get(t_input *input);
t_entry				**ls_ent_get_rec(char **dirs, t_input *input);

t_entry				**ls_order_list_sort(t_ls_order *order_list, t_input *input);
t_entry				**ls_entry_list_sort(t_entry *entry_list, t_input *input);

int 				ls_print_short(t_entry **entries, t_input *input);
int 				ls_print_long(t_entry **entries, t_input *input);

t_entry				*ls_entry_list_create(t_input *input, t_ls_order *order);
t_ls_order			*ls_order_list_create(t_input *input);

/*
** ls_errors.c, error management
*/



void				ls_unknown_error(int err_id);
void				ls_illegal_option(char c);
void				ls_nullptr(void* ptr);

/*
** TODO comment
*/

#endif