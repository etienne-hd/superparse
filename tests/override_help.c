#include "superparse.h"
#include <stdio.h>

void override_help(t_superparse superparse, t_superoption *option)
{
	(void)superparse;
	(void)option;
	printf("Hello, World!\n");
	return ;
}

int	main(int argc, char **argv)
{
	t_superoption options[] = {
		{ 0 }
	};

	if (superparse_parse((t_superparse){ .override_help=override_help }, options, argc, argv) == -1)
		return (2);
}