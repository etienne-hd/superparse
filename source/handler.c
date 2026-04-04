#include "superparse.h"
#include "utils.h"

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
		write_buf(2, "superparse: Cannot parse integer value \"", -1);
		write_buf(2, option->value, -1);
		write_buf(2, "\" for ", -1);
		write_buf(2, option->invoked, -1);
		write_buf(2, "\n", -1);
		write_buf(2, 0, 0);
		return (-1);
	}
	s = option->value;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if ((option->value[0] != '-' && number > number * 10 + *s - '0') || (option->value[0] == '-' && -number < -(number * 10 + *s - '0')))
		{
			write_buf(2, "superparse: Integer value \"", -1);
			write_buf(2, option->value, -1);
			write_buf(2, "\" for ", -1);
			write_buf(2, option->invoked, -1);
			write_buf(2, " out of range\n", -1);
			write_buf(2, 0, 0);
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
		write_buf(2, "superparse: Cannot parse integer 64 value \"", -1);
		write_buf(2, option->value, -1);
		write_buf(2, "\" for ", -1);
		write_buf(2, option->invoked, -1);
		write_buf(2, "\n", -1);
		write_buf(2, 0, 0);
		return (-1);
	}
	s = option->value;
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if ((option->value[0] != '-' && number > number * 10 + *s - '0') || (option->value[0] == '-' && -number < -(number * 10 + *s - '0')))
		{
			write_buf(2, "superparse: Integer 64 value \"", -1);
			write_buf(2, option->value, -1);
			write_buf(2, "\" for ", -1);
			write_buf(2, option->invoked, -1);
			write_buf(2, " out of range\n", -1);
			write_buf(2, 0, 0);
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