#include "superparse.h"
#include <stdio.h>
#include <stdlib.h>

int handle_ip_address(t_superoption *option)
{
	int shift = 0;
	char *raw_address = option->value;
	unsigned int ip_address = 0;
	int i = 0;
	int part = 0;
	
	while (raw_address[i])
	{
		part++;
		int value = atoi(&raw_address[i]);
		if (value > 255 || value < 0)
		{
			printf("callback: Invalid IP Address\n");
			return (-1);
		}
		ip_address += (value << shift);
		shift += 8;
		while (raw_address[i] && raw_address[i] != '.')
			i++;
		if (raw_address[i] == '.')
			i++;
	}
	if (part != 4 || raw_address[i - 1] == '.')
	{
		printf("callback: Invalid IP Address\n");
		return (-1);
	}
	*(unsigned int *)option->ref = ip_address;
	return (0);
}

int	main(int argc, char **argv)
{
	unsigned int ip_address = 0;

	t_superoption options[] = {
		(t_superoption){
			.short_name='i', .long_name="ip_address",
			.type=CALLBACK, .callback=handle_ip_address,
			.ref=&ip_address
		},
		{ 0 }
	};

	if (superparse_parse((t_superparse){ 0 }, options, argc, argv) == -1)
		return (2);

	printf("ip address: %u\n", ip_address);

	printf("positional:\n");
	for (int i = 0; i < argc && argv[i]; i++)
		printf("%s\n", argv[i]);
}