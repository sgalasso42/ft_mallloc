#include "ft_malloc.h"

void    *realloc(void *ptr, size_t size) {
    t_page		*page;
	t_block		*block;
    char        *new_ptr;

    new_ptr = NULL;
	page = g_pagelist;
	while (page)
	{
		block = page->blocklist;
		while (block)
		{
			if ((void *)block == ptr - sizeof(t_block))
			{
                // printf("Found the block\n");
				if (block->next && (size_t)((void *)(block->next) - ((void *)block + block->size + sizeof(t_block))) >= sizeof(t_block) + size)
                {
                    // printf("Can increase between blocks\n");
                    block->size = size;
                    return ((void *)block + sizeof(t_block));
                }
                else if (!block->next && (size_t)(((void *)(block->page) + block->page->fsize) - ((void *)block + block->size + sizeof(t_block))) >= sizeof(t_block) + size)
                {
                    // printf("Can increase at the end of blocks\n");
                    // printf("size: %zu\n", size);
                    // printf("fsize: %zu\n", sizeof(t_block) + size);
                    // printf("page start: %p\n", (void *)(block->page));
                    // printf("page end: %p\n", (void *)(block->page) + block->page->fsize);
                    // printf("block start: %p\n", block);
                    // printf("block end: %p\n", ((void *)block + block->size + sizeof(t_block)));
                    // printf("available at end: %zu\n", (size_t)(((void *)(block->page) + block->page->fsize) - ((void *)block + block->size + sizeof(t_block))));
                    block->size = size;
                    return ((void *)block + sizeof(t_block));
                }
                else
                {
                    // printf("Need to increase, new size: %zu\n", size);
                    if (!(new_ptr = malloc(size)))
                        return (NULL);
                    size_t i = 0;
                    while (i < block->size)
                    {
                        new_ptr[i] = ((char *)block + sizeof(t_block))[i];
                        i++;
                    }
                    free(block);
                    return ((void *)new_ptr);
                }
			}
			block = block->next;
		}
		page = page->next;
	}
	return (NULL);
}