#include "superparse.h"
#include <stdio.h>

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
	char *s = option.raw;
	int number = 0;

	while ((*s >= '0' && *s <= '9') || (*s == '-' && s == option.raw))
		s++;
	if (*s != 0)
	{
		printf("[SuperParse]: Cannot parse integer value \"%s\" for TODO\n", option.raw);
		return (-1);
	}
	s = option.raw;
	if (*s == '-')
		s++;
	while (*s)
	{
		if ((option.raw[0] != '-' && number > number * 10 + *s - '0') || (option.raw[0] == '-' && -number < -(number * 10 + *s - '0')))
		{
			printf("[SuperParse]: Integer value \"%s\" for TODO out of range\n", option.raw);
			return (-1);
		}
		number = number * 10 + *s - '0';
		s++;
	}
	if (option.raw[0] == '-')
		number = -number;
	*(int *)option.ref = number;
	return (0);
}

int
handle_int64(t_superoption option)
{
	(void)option;
	// TODO
	return (0);
}