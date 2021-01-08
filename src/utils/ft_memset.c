#include "ft_malloc.h"

void ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void *ft_memset(void *s, int c, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}