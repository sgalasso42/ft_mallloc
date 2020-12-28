#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define TINY 90000 // N : should be TINYMAX * 100
# define SMALL 900000 // M : should be SMALLMAX * 100

# define TINYMAX 900 // n
# define SMALLMAX 9000  // m

// to remove useless includes
# include <sys/mman.h>
# include <unistd.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_block	t_block;
typedef struct s_page	t_page;

struct					s_block
{
	size_t		fsize; // (header + content) size
	size_t		size; // content size
	t_block		*next;
	t_page		*page;
};

struct					s_page
{
	size_t		fsize; // (header + content) size // also correspond to type
	size_t		size; // content size
	t_block		*blocklist;
	t_page		*next;
};

t_page					*g_pagelist;

// utils functions
int						get_typesize(size_t size);
void					ft_bzero(void *s, size_t n);
void					*ft_memset(void *s, int c, size_t n);
t_block					*add_block(t_block *prev, t_page *page, void *addr, size_t size);
t_page					*add_page(size_t size);

// library functions
void					show_alloc_mem(void);
void					show_pages_content(void);
void					*malloc(size_t size);
void					*ft_realloc(void *ptr, size_t size);
// calloc
// reallocf
// valloc
void					free(void *ptr);

#endif
