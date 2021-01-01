#include "ft_malloc.h"

void		relink_pagelist(t_page *page, t_page *previous)
{
	if (previous)
	{
		previous->next = page->next;
	}
	else
	{
		g_pagelist = page->next;;
	}
}

void		delete_page(t_page *page)
{
	t_page	*current;
	t_page	*previous;

	previous = 0;
	current = g_pagelist;
	while (current)
	{
		if (current == page)
		{
			relink_pagelist(page, previous);
			if ((munmap((void *)page, page->fsize)) == -1)
			{
				perror("munmap error "); // check if I can use perror, else to remove
				exit(EXIT_FAILURE); // quitter proprement
			}
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void		relink_blocklist(t_page *page, t_block *block, t_block *previous)
{
	if (previous)
	{
		previous->next = block->next;
	}
	else
	{
		page->blocklist = block->next;
	}
	if (!page->blocklist)
	{
		delete_page(page);
	}
}

void		free(void *ptr)
{
	t_page		*page;
	t_block		*block;
	t_block		*previous;

	previous = 0;
	page = g_pagelist;
	while (page)
	{
		block = page->blocklist;
		while (block)
		{
			if ((void *)block == ptr)
			{
				relink_blocklist(page, block, previous);
				return ;
			}
			previous = block;
			block = block->next;
		}
		page = page->next;
	}
}
