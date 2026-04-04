#include "superparse.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	char opt_a = 0;
	char *opt_b = NULL;
	int opt_c = 0;
	long long opt_d = 0;

	t_superoption options[] = {
		(t_superoption){
			.short_name='a', .long_name="aaa",
			.type=NONE, .ref=&opt_a
		},
		(t_superoption){
			.short_name='b', .long_name="bbb",
			.type=STRING, .ref=&opt_b, .value_name="string"
		},
		(t_superoption){
			.short_name='c', .long_name="ccc",
			.type=INT, .ref=&opt_c, .value_name="int"
		},
		(t_superoption){
			.short_name='d', .long_name="ddd",
			.type=INT, .ref=&opt_d, .value_name="int64"
		},
		{ 0 }
	};

	if (superparse_parse((t_superparse){ 0 }, options, argc, argv) == -1)
		return (2);

	printf("a: %d\n", opt_a);
	printf("b: %s\n", opt_b);
	printf("c: %d\n", opt_c);
	printf("d: %lld\n", opt_d);

	printf("positional:\n");
	for (int i = 0; i < argc && argv[i]; i++)
		printf("%s\n", argv[i]);
}