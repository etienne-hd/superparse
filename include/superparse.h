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

typedef enum e_superargtype
{
	CHAR = '0',
	STRING = '1',
	INTEGER = '2',
	BOOLEAN = '3'	
} t_superargtype;

typedef struct s_superarg
{
	const char **identifier;
	const t_superargtype type;
	const char *describe;
	const int required;
} t_superarg;

t_superparse superparse_init(const char *name, const char *description);
int superparse_add_arg(t_superparse *superparse, const t_superarg arg);

#endif