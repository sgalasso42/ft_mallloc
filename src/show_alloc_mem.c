#include "ft_malloc.h"

// TINY : 0xA0000
// 0xA0020 - 0xA004A : 42 octets
// 0xA006A - 0xA00BE : 84 octets
// SMALL : 0xAD000
// 0xAD020 - 0xADEAD : 3725 octets
// LARGE : 0xB0000
// 0xB0020 - 0xBBEEF : 48847 octets
// Total : 52698 octets

void		show_alloc_mem(void)
{
	t_page		*page;
	t_block		*block;

	// printf("t_page: %zu\n", sizeof(t_page));
	// printf("t_block: %zu\n", sizeof(t_block));
	page = g_pagelist;
	while (page)
	{
		if (page->fsize == TINY)
			ft_putstr("TINY : ");
		else if (page->fsize == SMALL)
			ft_putstr("SMALL : ");
		else
			ft_putstr("LARGE : ");
		ft_putstr((void*)page + sizeof(t_page));
		ft_putstr("\n");
		block = page->blocklist;
		while (block)
		{
			ft_putstr((void *)block + sizeof(t_block));
			ft_putstr(" - ");
			ft_putstr((void *)block + sizeof(t_block) + block->size);
			ft_putstr(ft_itoa(block->size));
			ft_putstr(" : ");
			ft_putstr("octets\n");
			block = block->next;
		}
		page = page->next;
	}
}
