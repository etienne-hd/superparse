#include "utils.h"

int
ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int
ft_count_char(const char *s, int c)
{
	int count;

	count = 0;
	while (*s)
	{
		if (c == *s)
			count++;
		s++;
	}
	return count;
}

int
ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int
ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (*s1 == *s2 && *s1 && i < n)
	{
		s1++;
		s2++;
	}
	if (n == 0)
		return (0);
	return (*s1 == *s2);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n != 0)
	{
		((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1]; 
		n--;
	}
	return (dest);
}

int ft_isspace(char c)
{
	return ((c >= 8 && c <= 13) || c == ' ');
}