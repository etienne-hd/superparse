#include "superparse.h"

t_superparse
superparse_init(const char *name, const char *description)
{
	t_superparse superparse;

	superparse.name = name;
	superparse.description = description;
	superparse.args = 0;
	superparse.argv = 0;
	superparse.argc = 0;

	return (superparse);
}