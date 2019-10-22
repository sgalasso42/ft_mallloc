#include "ft_malloc.h"

void		relink_pagelist(t_page *page, t_page *last_page)
{
	if (last_page)
	{
		last_page->next = page->next;
	}
	else
	{
		g_pagelist = page->next;;
	}
}

void		delete_page(t_page *page)
{
	t_page	*curr_page;
	t_page	*last_page;

	last_page = 0;
	curr_page = g_pagelist;
	while (curr_page)
	{
		if (curr_page == page)
		{
			relink_pagelist(page, last_page);
			if ((munmap((void *)page, page->fsize)) == -1)
			{
				printf("munmap error\n");
				exit(EXIT_FAILURE); // quitter proprement
			}
			return ;
		}
		last_page = curr_page;
		curr_page = curr_page->next;
	}
	printf("delete_page error : page not found");
}

void		relink_blocklist(t_page *page, t_block *block, t_block *last_block)
{
	if (last_block)
	{
		last_block->next = block->next;
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

void		release_block(void *ptr)
{
	t_page		*page;
	t_block		*block;
	t_block		*last_block;

	last_block = 0;
	if (!(page = g_pagelist))
	{
		printf("release block error : no pages found");
		return ;
	}
	while (page)
	{
		block = page->blocklist;
		while (block)
		{
			if ((void *)block == ptr)
			{
				relink_blocklist(page, block, last_block);
				return ;
			}
			last_block = block;
			block = block->next;
		}
		page = page->next;
	}
	printf("release block error : block not found");
}

void		ft_free(void *ptr)
{
	if (0/*TINY*/)
	{
	}
	else if (0/*SMALL*/)
	{
	}
	else
	{
		release_block(ptr);
	}
}
