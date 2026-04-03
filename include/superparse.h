#ifndef SUPERPARSE_H
# define SUPERPARSE_H

typedef struct s_superparse
{
	const char *name;
	const char *description;
} t_superparse;

typedef enum e_superargtype
{
	NONE = '0',
	STRING = '1',
} t_superargtype;

typedef struct s_superoption
{
	const char *long_name; // --value
	const char short_name; // -value
	const t_superargtype type;
	const char *describe;
	void *ref;
	char *raw;
} t_superoption;

int	superparse_parse(const t_superparse superparse, t_superoption *options, int argc, char **argv);

#endif