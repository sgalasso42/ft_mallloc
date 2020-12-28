#include "ft_malloc.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}

int		get_typesize(size_t size)
{
	if (size <= TINYMAX)
	{
		return (TINY);
	}
	else if (size > TINYMAX && size <= SMALLMAX)
	{
		return (SMALL);
	}
	return (size + sizeof(t_page));
}

t_block	*add_block(t_block *prev, t_page *page, void *addr, size_t size)
{
	t_block		*new_block;

	new_block = addr;
	new_block->size = size;
	new_block->fsize = size + sizeof(t_block);
	if (prev)
	{
		new_block->next = prev->next;
		prev->next = new_block;
	}
	else
	{
		page->blocklist = new_block;
		new_block->next = 0;
	}
	new_block->page = page;
	return (new_block);
}

t_page	*add_page(size_t size)
{
	t_page	*new_page;

	if ((new_page = mmap(0, get_typesize(size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
	{
		perror("mmap error "); // to remove or check if ok to use
		exit(EXIT_FAILURE); // temporaire, trouver autre solution
	}
	new_page->size = size;
	new_page->fsize = get_typesize(size);
	new_page->blocklist = 0;
	new_page->next = g_pagelist;
	g_pagelist = new_page;
	return (new_page);
}