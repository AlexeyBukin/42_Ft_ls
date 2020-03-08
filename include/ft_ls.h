#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <dirent.h>
#include "libft.h"

typedef struct		s_flags
{
	t_bool			all;
	t_bool			rec;
	t_bool			rev;
	t_bool			list;
	t_bool			time;

	t_bool			p_slash;
}					t_flags;

typedef struct		s_ft_ls
{
	int		code;
}					t_ft_ls;

#endif