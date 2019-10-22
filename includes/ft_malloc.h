#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <unistd.h>

# include <stdio.h>

typedef struct	s_block	t_block;
typedef struct	s_page	t_page;

struct					s_block
{
	size_t		fsize;	// full size
	size_t		size;	// content size
	t_block		*next;
};

struct					s_page
{
	size_t		fsize;	// full size
	size_t		size;	// content size
	t_block		*blocklist;
	t_page		*next;
};

t_page					*g_pagelist;

void					show_alloc_mem();
void					*ft_malloc(size_t size);
//void					*ft_realloc(void *ptr, size_t size);
void					ft_free(void *ptr);

// BONUS
void					show_pages_content(void);

#endif
