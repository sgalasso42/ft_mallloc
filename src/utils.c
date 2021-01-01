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

int get_typesize(size_t size)
{
	if (size + sizeof(t_block) <= TINYMAX)
	{
		return (TINY);
	}
	else if (size + sizeof(t_block) > TINYMAX && size + sizeof(t_block) <= SMALLMAX)
	{
		return (SMALL);
	}
	return (sizeof(t_page) + sizeof(t_block) + size);
}

t_block *add_block(t_block *prev, t_page *page, void *addr, size_t size)
{
	t_block *new_block;

	// printf("> creating block: [%p] of size: %zu\n", addr, size);
	new_block = addr;
	new_block->size = size;
	if (!prev)
	{
		page->blocklist = new_block;
		new_block->next = 0;
	}
	else
	{
		new_block->next = prev->next;
		prev->next = new_block;
	}
	new_block->page = page;
	return (new_block);
}

t_page *add_page(size_t size)
{
	t_page *new_page;

	if ((new_page = mmap(0, get_typesize(size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
	{
		perror("mmap error "); // to remove or check if ok to use
		exit(EXIT_FAILURE);	   // temporaire, trouver autre solution
	}
	// printf("> creating page: [%p] of fsize: %d\n", new_page, get_typesize(size));
	new_page->fsize = get_typesize(size);
	new_page->blocklist = 0;
	new_page->next = g_pagelist;
	g_pagelist = new_page;
	return (new_page);
}