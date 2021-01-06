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
			printf("TINY : ");
		else if (page->fsize == SMALL)
			printf("SMALL : ");
		else
			printf("LARGE : ");
		printf("%p\n", (void*)page + sizeof(t_page));
		block = page->blocklist;
		while (block)
		{
			printf("%p - %p : %zu octets\n", (void *)block + sizeof(t_block), (void *)block + sizeof(t_block) + block->size, block->size);
			block = block->next;
		}
		page = page->next;
	}
}
