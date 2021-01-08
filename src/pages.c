#include "ft_malloc.h"

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

t_page *add_page(size_t size)
{
	t_page	*new_page;
	t_page	*ptr;

	if ((new_page = mmap(0, get_typesize(size), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
	new_page->fsize = get_typesize(size);
	new_page->blocklist = 0;
	new_page->next = 0;
	ptr = g_pagelist;
	if (!ptr)
		g_pagelist = new_page;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new_page;
	}
	return (new_page);
}