#include "superparse.h"
#include <stdio.h>

int
handle_none(t_superoption *option)
{
	*(char *)option->ref = 1;
	return (0);
}

int
handle_string(t_superoption *option)
{
	*(char **)option->ref = option->value;
	return (0);
}

int
handle_int(t_superoption *option)
{
	char *s = option->value;
	int number = 0;

	while ((*s >= '0' && *s <= '9') || ((*s == '-' || *s == '+') && s == option->value))
		s++;
	if (*s != 0)
	{
		printf("[SuperParse]: Cannot parse integer value \"%s\" for %s\n", option->value, option->invoked);
		return (-1);
	}
	s = option->value;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if ((option->value[0] != '-' && number > number * 10 + *s - '0') || (option->value[0] == '-' && -number < -(number * 10 + *s - '0')))
		{
			printf("[SuperParse]: Integer value \"%s\" for %s out of range\n", option->value, option->invoked);
			return (-1);
		}
		number = number * 10 + *s - '0';
		s++;
	}
	if (option->value[0] == '-')
		number = -number;
	*(int *)option->ref = number;
	return (0);
}

int
handle_int64(t_superoption *option)
{
	char *s = option->value;
	long long number = 0;

	while ((*s >= '0' && *s <= '9') || ((*s == '-' || *s == '+') && s == option->value))
		s++;
	if (*s != 0)
	{
		printf("[SuperParse]: Cannot parse 64 bits integer value \"%s\" for %s\n", option->value, option->invoked);
		return (-1);
	}
	s = option->value;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if ((option->value[0] != '-' && number > number * 10 + *s - '0') || (option->value[0] == '-' && -number < -(number * 10 + *s - '0')))
		{
			printf("[SuperParse]: 64 bits integer value \"%s\" for %s out of range\n", option->value, option->invoked);
			return (-1);
		}
		number = number * 10 + *s - '0';
		s++;
	}
	if (option->value[0] == '-')
		number = -number;
	*(long long *)option->ref = number;
	return (0);
}