#include "superparse.h"

int
handle_none(t_superoption option)
{
	*(char *)option.ref = 1;
	return (0);
}

int
handle_string(t_superoption option)
{
	*(char **)option.ref = option.raw;
	return (0);
}

int
handle_double(t_superoption option)
{
	(void)option;
	// TODO
	return (0);
}

int
handle_int(t_superoption option)
{
	(void)option;
	// TODO
	return (0);
}

int
handle_int64(t_superoption option)
{
	(void)option;
	// TODO
	return (0);
}