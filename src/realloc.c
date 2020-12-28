#include "ft_malloc.h"

void    *realloc(void *ptr, size_t size) {
    t_block *block;

    block = (t_block *)ptr;
    if ((size_t)(block->next) - (size_t)(block + block->fsize) >= sizeof(t_block) + size
    || (size_t)(block->page + block->page->fsize) - (size_t)block >= sizeof(t_block) + size)
    {
        block->size = size;
        block->fsize = sizeof(t_block) + size;
    }
    else
    {
        if (!(ptr = malloc(size)))
        {
		    return 0;
        }
    }
    return (block);
}