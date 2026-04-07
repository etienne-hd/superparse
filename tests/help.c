#include "superparse.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char *opt_type = NULL;
	char *opt_value = NULL;
	int opt_ok = 0;

	t_superoption options[] = {
		(t_superoption){
			.short_name='t', .long_name="type",
			.type=STRING, .ref=&opt_type,
			.value_name="type", .describe="Type of blablabla"
		},
		(t_superoption){
			.short_name='v', .long_name="value",
			.type=STRING, .ref=&opt_value,
			.value_name="value", .describe="Value of the type"
		},
		(t_superoption){
			.short_name='o', .long_name="ok",
			.type=NONE, .ref=&opt_ok,
			.describe="You want to set OK to true???"
		},
		{ 0 }
	};

	if (superparse_parse((t_superparse){ .usage="./help <...> [...]", .summary="This program..." }, options, argc, argv) == -1)
		return (2);
}