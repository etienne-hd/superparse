#include "superparse.h"
#include "utils.h"
#include <unistd.h>

static int
get_padding(t_superoption *options)
{
	int padding;
	int current_padding;
	t_superoption *option;
	
	padding = 0;
	option = options;
	while (option->short_name || option->long_name)
	{
		current_padding = 6; // __-x__
		if (option->long_name)
			current_padding += 2 + ft_strlen(option->long_name); // --<'long_name length'>
		if (option->type != NONE && option->value_name)
			current_padding += 3 + ft_strlen(option->value_name); // _<'value length'>
		current_padding += 2; 
		if (current_padding > padding)
			padding = current_padding;
		option++;
	}
	if (padding > 32)
		return (32);
	return (padding);
}

static void
print_describe(const char *message, int current_padding, int default_padding)
{
	int begin;
	int end;

	end = 0;
	begin = 0;
	while (message[end])
	{
		end++;
		if ((message[end] == 0 || ft_isspace(message[end])) && end - begin > 0)
		{
			// print value
			if (current_padding + end - begin >= 80)
			{
				write_buf(1, "\n", -1);
				current_padding = 0;
				current_padding += write_buf(1, "                                                ", default_padding);
			}
			else if (begin != 0)
				current_padding += write_buf(1, " ", -1);
			current_padding += write_buf(1, &message[begin], end - begin);
			while (ft_isspace(message[end]))
				end++;
			begin = end;
		}
	}
}

void
show_help(t_superparse superparse, t_superoption *options)
{
	int padding;
	int current_padding;
	t_superoption *option;

	if (superparse.usage)
	{
		write_buf(1, "Usage: ", -1);
		write_buf(1, superparse.usage, -1);
		write_buf(1, "\n", -1);
	}

	padding = get_padding(options);
	option = options;
	while (option->short_name || option->long_name)
	{
		current_padding = 0;
		if (option->short_name)
			current_padding += write_buf(1, "  -", -1) + write_buf(1, &option->short_name, 1);
		else
			current_padding += write_buf(1, "      ", -1);
		if (option->short_name && option->long_name)
			current_padding += write_buf(1, ", ", -1);
		if (option->long_name)
			current_padding += write_buf(1, "--", -1) + write_buf(1, option->long_name, -1);
		if (option->type != NONE && option->value_name)
		{
			current_padding += write_buf(1, " <", -1);
			current_padding += write_buf(1, option->value_name, -1);
			current_padding += write_buf(1, ">", -1);
		}
		current_padding += write_buf(1, "  ", -1);
		if (current_padding < padding)
			current_padding += write_buf(1, "                          ", padding - current_padding);
		if (option->describe)
			print_describe(option->describe, current_padding, padding + 2);
		write_buf(1, "\n", -1);
		option++;
	}
	if (superparse.summary)
	{
		write_buf(1, "\n", -1);
		write_buf(1, superparse.summary, -1);
		write_buf(1, "\n", -1);
	}
	write_buf(1, NULL, 0);
}