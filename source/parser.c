#include "superparse.h"
#include "utils.h"
#include "handler.h"
#include <unistd.h>

static int
parse_option_type(t_superoption *option)
{
	int (*handlers[])(t_superoption *) = {
		[NONE] = handle_none,
		[STRING] = handle_string,
		[INT] = handle_int,
		[INT64] = handle_int64,
	};

	int (*handler)(t_superoption *);
	if (option->type == CALLBACK)
		handler = option->callback;
	else
		handler = handlers[option->type];
	if (handler(option) == -1)
		return (-1);
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
		if (
			(is_long_name && option->long_name && ft_strcmp(&argv[*i][2], option->long_name) == 0)
			|| (!is_long_name && option->short_name && ft_count_char(&argv[*i][1], option->short_name))
		)
		{
			option->invoked = processing_arg;
			if (!is_long_name && option->type != NONE && ft_strlen(argv[*i]) > ft_count_char(&argv[*i][1], option->short_name) + 1)
			{
				write_buf(2, "superparse: \"", -1);
				write_buf(2, option->invoked, -1);
				write_buf(2, "\" cannot be used in a grouped option.\n", -1);
				write_buf(2, 0, 0);
				return (-1);
			}
			else if (option->type != NONE)
			{
				option->value = argv[*i + 1];
				if (!option->value)
				{
					write_buf(2, "superparse: \"", -1);
					write_buf(2, option->invoked, -1);
					write_buf(2, "\" option requires an argument.\n", -1);
					write_buf(2, 0, 0);
					return (-1);
				}
				(*i)++;
			}
			else
				option->value = (void *)-1;
			if (parse_option_type(option) == -1)
				return (-1);
			option_checker += is_long_name ? 1 : ft_count_char(&processing_arg[1], option->short_name);
			if (option->type != NONE)
				break;
		}
		option++;
	}
	if (!option_checker && !(!is_long_name && ft_strlen(processing_arg) == option_checker + 1))
	{
		write_buf(2, "superparse: Unknown option \"", -1);
		write_buf(2, processing_arg, -1);
		write_buf(2, "\"\n", -1);
		write_buf(2, 0, 0);
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
	int	lock_positional;

	index = 1;
	positional_index = 1;
	lock_positional = 0;
	while (index < argc)
	{
		if (!lock_positional && argv[index][0] == '-')
		{
			if (ft_strcmp(argv[index], "--") == 0)
				lock_positional = 1;
			else if (parse_name_arg(options, argc, argv, &index) != 0)
				return (-1);
		}
		else
			argv[positional_index++] = argv[index];
		index++;
	}
	while (positional_index < argc)
		argv[positional_index++] = NULL;
	return (0);
}