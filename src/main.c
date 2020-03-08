#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_ft_ls		data;
	char * path = getenv("PATH");
	ft_printf("PATH = \'%s\'\n", path);
	return (0);
}