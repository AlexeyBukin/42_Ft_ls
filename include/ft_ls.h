#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <dirent.h>
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

typedef struct		dirent	t_dirent;
typedef struct		stat	t_stat;

typedef struct		s_flags
{
	char			**dirs;

	t_bool			all;
	t_bool			rec;
	t_bool			rev;
	t_bool			list;
	t_bool			time;

	t_bool			p_slash;
}					t_flags;

typedef struct		s_entry
{
	t_dirent		*entry;
	t_stat			*stat;
	char 			*name_full;
	char			*name_relative;
	struct s_entry	*next;
	struct s_entry	*prev;
}					t_entry;


int 				ls_get_flags(int ac, char **av, t_flags *flags);

t_entry				*ls_ent_create(t_dirent *entry, t_stat *stat);

t_entry				**ls_get_rights(t_dirent **entry);

t_entry				**ls_ent_get(char **dirs, t_flags *flags);
t_entry				**ls_ent_get_rec(char **dirs, t_flags *flags);

t_entry				**ls_ent_sort(t_entry **entries, t_flags *flags);

int 				ls_print_short(t_entry **entries, t_flags *flags);
int 				ls_print_long(t_entry **entries, t_flags *flags);
#endif