#include "ft_malloc.h"

t_block		*find_block_space(t_page *page, size_t size)
{
	t_block	*current = 0;

	// printf("size: %zu\n", size);
	// printf("t_block: %zu\n", sizeof(t_block));
	// printf("t_page: %zu\n", sizeof(t_page));
	// printf("fsize: %zu\n", size + sizeof(t_block));
	if (!(current = page->blocklist))
	{
		// printf("Space found (FIRST)\n");
		return (add_block(current, page, (void *)page + sizeof(t_page), size));
	}
	while (current->next)
	{
		if ((size_t)((void *)(current->next) - ((void *)current + current->size + sizeof(t_block))) >= size + sizeof(t_block))
		{
			// printf("Space found (BETWEEN) after block [%p] + fsize: %zu\n", current, current->size + sizeof(t_block));
			return (add_block(current, page, (void *)current + current->size + sizeof(t_block), size));
		}
		current = current->next;
	}
	if ((size_t)(((void *)page + page->fsize) - ((void *)current + current->size + sizeof(t_block))) >= size + sizeof(t_block))
	{
		// printf("Space found (LAST) after block [%p] + fsize: %zu\n", current, current->size + sizeof(t_block));
		return (add_block(current, page, (void *)current + current->size + sizeof(t_block), size));
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
			if ((block = find_block_space(page, size)))
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

	ft_putstr("malloc called\n");
	if (!(block = find_available_space(size)))
	{
		// printf("Space not found\n");
		if (!(page = add_page(size)))
			return (NULL);
		block = add_block(page->blocklist, page, (void *)page + sizeof(t_page), size);
	}
	return ((void *)block + sizeof(t_block));
}
