#ifndef SUPERPARSE_H
# define SUPERPARSE_H

# include "list.h"

typedef struct s_superparse
{
	const char *name;
	const char *description;
	t_list *args;
	int argc;
	char **argv;
} t_superparse;

t_superparse superparse_init(const char *name, const char *description);

#endif