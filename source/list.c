#include "list.h"
#include <stdlib.h>

t_list *
lst_new(void *value)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->value = value;
	lst->next = NULL;
	return (lst);
}

void
lst_add_back(t_list **lst, t_list *new)
{
	t_list	*current_lst;

	if (!lst || !new)
		return ;
	current_lst = *lst;
	if (!current_lst)
	{
		*lst = new;
		return ;
	}
	while (current_lst && current_lst->next)
		current_lst = current_lst->next;
	current_lst->next = new;
}