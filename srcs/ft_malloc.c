#include "ft_malloc.h"

t_block		*add_block(t_page *page, void *addr, size_t size)
{
	t_block		*curr_block; // current block
	t_block		*new_block;

	new_block = addr;
	new_block->size = size;
	new_block->fsize = size + sizeof(t_block);

	if ((curr_block = page->blocklist))
	{
		while (curr_block->next)
		{
			if (curr_block < new_block)
			{
				if ((curr_block->next && (void *)new_block < (void *)curr_block->next)
				|| (!curr_block->next && (void *)new_block < (void *)page->next))
					break ;
			}
			curr_block = curr_block->next;
		}
		new_block->next = curr_block->next;
		curr_block->next = new_block;
	}
	else
	{
		page->blocklist = new_block;
		new_block->next = 0;
	}
	return (new_block);
}

/*t_block		*small_check(t_page *page, size_t fsize, size_t size)
{
	t_block		*block = 0;

	if (!page->blocklist && fsize <= page->size)
	{
		block = add_block(page, page + sizeof(t_page), size);
		return (block);
	}
	while (block)
	{
		if ((!block->next && (size_t)(page + page->fsize) - (size_t)block >= fsize)
		|| (block->next && (size_t)block->next - (size_t)(block + block->fsize) >= fsize))
		{
			block = add_block(page, block + block->fsize, size);
			return (block);
		}
		block = block->next;
	}
	return (block);
}*/

t_block		*large_check(t_page *page, size_t fsize, size_t size)
{
	t_block		*block = 0;

	if (!page->blocklist && fsize <= page->size)
	{
		block = add_block(page, page + sizeof(t_page), size);
		return (block);
	}
	while (block)
	{
		if ((!block->next && (size_t)(page + page->fsize) - (size_t)block >= fsize)
		|| (block->next && (size_t)block->next - (size_t)(block + block->fsize) >= fsize))
		{
			block = add_block(page, block + block->fsize, size);
			return (block);
		}
		block = block->next;
	}
	return (block);
}

t_block		*space_available(size_t size)
{
	t_page		*page;
	t_block		*block;
	size_t		fsize;

	fsize = size + sizeof(t_block);
	page = g_pagelist;
	while (page)
	{
		if (size < TINYMAX)
		{	
			//block = tiny_check(page, fsize, size);
		}
		else if (size < SMALLMAX)
		{
			//block = small_check(page, fsize, size);
		}
		else
		{
			block = large_check(page, fsize, size);
		}
		page = page->next;
	}
	return (0);
}

t_page		*new_page(size_t size)
{
	t_page	*last_page;
	t_page	*new_page;

	if ((new_page = mmap(0, size + sizeof(t_page), PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
	{
		printf("mmap error\n");
		exit(EXIT_FAILURE); // temporaire, trouver autre solution
	}

	new_page->size = size;
	new_page->fsize = size + sizeof(t_page);
	new_page->blocklist = 0;
	new_page->next = 0;

	if (!g_pagelist)
	{
		g_pagelist = new_page;;
	}
	else
	{
		last_page = g_pagelist;
		while (last_page->next)
			last_page = last_page->next;
		last_page->next = new_page;
	}
	return (new_page);
}

t_block		*space_allocation(size_t size)
{
	t_page		*page;
	t_block		*block;

	page = new_page(size); // todo : LARGE / SMALL / TINY system
	block = add_block(page, page + sizeof(page), size);

	return (block);
}

void		*ft_malloc(size_t size)
{
	t_block		*block;

	if (!(block = space_available(size)))
	{
		block = space_allocation(size);
	}
	return ((void *)block);
}
