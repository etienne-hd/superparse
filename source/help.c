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

static int
write_buf(const char *msg, unsigned int n)
{
	static char buffer[1024];
	static unsigned long buffer_cursor;
	unsigned int i;

	i = 0;
	if (msg == NULL)
	{
		if (buffer_cursor)
		{
			i = write(1, buffer, buffer_cursor);
			buffer_cursor = 0;
		}
		return (i);
	}
	while (i < n && msg[i])
	{
		if (buffer_cursor >= sizeof(buffer))
			write_buf(NULL, 0);
		buffer[buffer_cursor++] = msg[i];
		i++;
	}
	return (i);
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
				write_buf("\n", 1);
				current_padding = 0;
				current_padding += write_buf("                                                ", default_padding);
			}
			else if (begin != 0)
				current_padding += write_buf(" ", 1);
			current_padding += write_buf(&message[begin], end - begin);
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
		write_buf("Usage: ", 7);
		write_buf(superparse.usage, ft_strlen(superparse.usage));
		write_buf("\n", 1);
	}

	padding = get_padding(options);
	option = options;
	while (option->short_name || option->long_name)
	{
		current_padding = 0;
		if (option->short_name)
			current_padding += write_buf("  -", 3) + write_buf(&option->short_name, 1);
		else
			current_padding += write_buf("      ", 6);
		if (option->short_name && option->long_name)
			current_padding += write_buf(", ", 2);
		if (option->long_name)
			current_padding += write_buf("--", 2) + write_buf(option->long_name, ft_strlen(option->long_name));
		if (option->type != NONE && option->value_name)
		{
			current_padding += write_buf(" <", 2);
			current_padding += write_buf(option->value_name, ft_strlen(option->value_name));
			current_padding += write_buf(">", 1);
		}
		current_padding += write_buf("  ", 2);
		if (current_padding < padding)
			current_padding += write_buf("                          ", padding - current_padding);
		if (option->describe)
			print_describe(option->describe, current_padding, padding + 2);
		write_buf("\n", 1);
		option++;
	}
	if (superparse.summary)
	{
		write_buf("\n", 1);
		write_buf(superparse.summary, ft_strlen(superparse.summary));
		write_buf("\n", 1);
	}
	write_buf(NULL, 0);
}