#include "list.h"
#include "superparse.h"

int
superparse_add_arg(t_superparse *superparse, const t_superarg arg)
{
	t_list *list_arg;

	list_arg = lst_new((void *)&arg);
	if (!list_arg)
		return (-1);
	lst_add_back(&superparse->args, list_arg);
	return (0);
}