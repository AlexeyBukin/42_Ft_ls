#include "ft_ls.h"

int 				ls_add_ent_name(t_input *input, char *ent_name)
{
	if (input == NULL || ent_name == NULL)
		return (E_LS_NULL_POINTER);
	if (input->ent_names == NULL)
		return (E_LS_NULL_POINTER);
//	if (unreachable(ent_name))
//		return (E_LS_NO_SUCH_FILE);

//	if (input->ent_names)
	(void) ent_name;
	return (0);
}

//int 				ls_get_flags(int ac, char **av, t_input *input)
//{
//	int				flags_done;
//	size_t 			i;
//	size_t 			j;
//
//	if (input == NULL || av == NULL)
//		return (E_LS_NULL_POINTER);
//
//	i = 1;
//	flags_done = FALSE;
//	while (i < ac && av[i] != NULL)
//	{
//		if (av[i][0] != '-' || flags_done == TRUE)
//		{
//			flags_done = ls_add_ent_name(input, av[i]);
//			if (flags_done < 0)
//				return (flags_done);
//			flags_done = TRUE;
//		}
//		else
//		{
//			if (av[i][1] == '-')
//				if (av[i][2] == '\0')
//				{
//					flags_done = TRUE;
//					i++;
//					continue;
//				}
//			j = 1;
//			while (av[i][j] != '\0')
//			{
//				if (av[i][j] == 'R')
//					input->rec = TRUE;
//				else if (av[i][j] == 'a')
//					input->all = TRUE;
//				else if (av[i][j] == 'l')
//					input->list = TRUE;
//				else if (av[i][j] == 'r')
//					input->rev = TRUE;
//				else if (av[i][j] == 't')
//					input->time = TRUE;
//				else
//					return (E_LS_ILLEGAL_OPTION);
//				j++;
//			}
//		}
//		i++;
//	}
//	if (av[i] == NULL)
//	{
//		return (E_LS_NULL_POINTER);
//	}
//
//
//	return (0);
//}