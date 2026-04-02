#ifndef LIST_H
# define LIST_H

typedef struct s_list
{
	void *value;
	struct s_list *next;
} t_list;

t_list *lst_new(void *value);
void lst_add_back(t_list **lst, t_list *new);

#endif