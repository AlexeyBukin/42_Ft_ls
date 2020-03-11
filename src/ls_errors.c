#include "ft_ls.h"

void	ls_illegal_option(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(c);
	ft_putstr("\n");
	ft_putendl(LS_USAGE);
	exit(0);
}

void	ls_nullptr(void* ptr)
{
	if (ptr == NULL)
	{
		ft_putendl("Null pointer exception...");
		exit(0);
	}
}