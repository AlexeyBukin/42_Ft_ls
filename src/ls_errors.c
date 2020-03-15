#include "ft_ls.h"

void	ls_unknown_error(int err_id)
{
	ft_printf("ft_ls: Unknown error: %d\n", err_id);
	exit(0);
}

void	ls_illegal_option(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n%s", c, LS_USAGE);
	exit(0);
}

void	ls_nullptr(void* ptr)
{
	if (ptr == NULL)
	{
		ft_printf("ft_ls: Null pointer exception\n");
		exit(0);
	}
}