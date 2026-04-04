#include "utils.h"
#include <unistd.h>

int
write_buf(int fd, const char *msg, unsigned int n)
{
	static char buffer[1024];
	static unsigned long buffer_cursor;
	unsigned int i;

	i = 0;
	if (msg == 0)
	{
		if (buffer_cursor)
		{
			i = write(fd, buffer, buffer_cursor);
			buffer_cursor = 0;
		}
		return (i);
	}
	while (((unsigned int)-1 == n || i < n) && msg[i])
	{
		if (buffer_cursor >= sizeof(buffer))
			write_buf(fd, NULL, 0);
		buffer[buffer_cursor++] = msg[i];
		i++;
	}
	return (i);
}