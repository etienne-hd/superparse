#include "superparse.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

static int
parse_arg_type(t_superoption *options)
{
	size_t i;

	i = 0;
	while (options[i].short_name || options[i].long_name)
	{
		t_superoption option = options[i];
		if (option.raw != NULL)
		{
			if (option.type == NONE)
				*(char *)option.ref = 1;
			else if (option.type == STRING)
				*(char **)option.ref = option.raw;
		}
		i++;
	}
	return (0);
}

static int
parse_name_arg(t_superoption *options, int argc, char **argv, int *i)
{
	int option_checker = 0;
	int is_long_name = argv[*i][1] == '-';
	char *processing_arg = argv[*i];

	t_superoption *option = options;
	while ((option->short_name || option->long_name) && *i < argc)
	{
		// Long Name
		if (
			(is_long_name && option->long_name && ft_strcmp(&argv[*i][2], option->long_name) == 0)
			|| (!is_long_name && option->short_name && ft_count_char(&argv[*i][1], option->short_name))
		)
		{
			if (!is_long_name && option->type != NONE && ft_strlen(argv[*i]) > ft_count_char(&argv[*i][1], option->short_name) + 1)
			{
				printf("[SuperParse]: %s can't collapse non NONE argument!\n", processing_arg);
				return (-1);
			}
			else if (option->type != NONE)
			{
				option->raw = argv[*i + 1];
				(*i)++;
			}
			else
				option->raw = (void *)-1;
			option_checker += is_long_name ? 1 : ft_count_char(&processing_arg[1], option->short_name);
			if (option->type != NONE)
				break;
		}
		option++;
	}
	if (!option_checker && !(!is_long_name && ft_strlen(processing_arg) == option_checker + 1))
	{
		printf("[SuperParse]: Unknown option %s\n", processing_arg);
		return (-1);
	}
	return (0);
}

int
superparse_parse(const t_superparse superparse, t_superoption *options, int argc, char **argv)
{
	(void)superparse;
	int index;
	int positional_index;

	index = 1;
	positional_index = 1;
	while (index < argc)
	{
		if (argv[index][0] == '-')
		{
			if (parse_name_arg(options, argc, argv, &index) != 0)
				return (-1);
		}
		else
			argv[positional_index++] = argv[index];
		index++;
	}
	while (positional_index < argc)
		argv[positional_index++] = NULL;
	if (parse_arg_type(options) == -1)
		return (-1);
	return (0);
}