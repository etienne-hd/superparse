#ifndef SUPERPARSE_H
# define SUPERPARSE_H

typedef struct s_superparse
{
	const char *name;
	const char *description;
} t_superparse;

typedef enum e_supertype
{
	NONE,
	STRING,
	INT,
	INT64,
	CALLBACK,
} t_supertype;

typedef struct s_superoption
{
	const char *long_name; // --value
	const char short_name; // -value
	const t_supertype type;
	const char *describe;
	int (*callback)(struct s_superoption *);
	char *invoked;
	void *ref;
	char *value;
} t_superoption;

int	superparse_parse(const t_superparse superparse, t_superoption *options, int argc, char **argv);

#endif