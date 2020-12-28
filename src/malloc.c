#include "ft_malloc.h"

t_block		*find_block_space(t_page *page, size_t fsize, size_t size)
{
	t_block	*current = 0;

	if (!(current = page->blocklist))
	{
		return (add_block(current, page, page + sizeof(t_page), size));
	}
	while (current->next)
	{
		if (((size_t)current->next - (size_t)(current + current->fsize) >= fsize))
		{
			return (add_block(current, page, current + current->fsize, size));
		}
		current = current->next;
	}
	if ((size_t)(page + page->fsize) - (size_t)current >= fsize)
	{
		return (add_block(current, page, current + current->fsize, size));
	}
	return (0);
}

t_block		*find_available_space(size_t size)
{
	t_page		*page;
	t_block		*block;

	page = g_pagelist;
	while (page)
	{
		if ((size_t)get_typesize(size) == page->fsize)
		{
			if ((block = find_block_space(page, size + sizeof(t_block), size)))
			{
				return (block);
			}
		}
		page = page->next;
	}
	return (0);
}

void		*malloc(size_t size)
{
	t_block		*block;
	t_page		*page;

	if (!(block = find_available_space(size)))
	{
		page = add_page(size);
		block = add_block(page->blocklist, page, page + sizeof(page), size);
	}
	return ((void *)block);
}
