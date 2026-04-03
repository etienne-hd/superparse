#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

int ft_strlen(const char *s);
int ft_count_char(const char *s, int c);
int ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);

#endif