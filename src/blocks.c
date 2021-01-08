#include "ft_malloc.h"

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