#include "ft_ls.h"

void	ls_unknown_error(int err_id)
{
	ft_printf("ft_ls: Unknown error: %d\n", err_id);
	exit(0);
}

/*
** replacing 'e' with illegal option c
** writing to error stream
*/

void	ls_illegal_option(char c)
{
	char		*str;

	str = ft_strdup("/bin/ls: illegal option -- e\n"LS_USAGE"\n");
	str[27] = c;
	ft_putstr_fd(str, 2);
	ft_free(str);
	exit(1);
}

void	ls_nullptr(const void* ptr)
{
	if (ptr == NULL)
	{
		ft_printf("ft_ls: Null pointer exception\n");
		exit(0);
	}
}