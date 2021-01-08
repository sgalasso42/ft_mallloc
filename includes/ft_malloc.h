#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define TINY 16384 // 4096 * 4 > (TINYMAX + sizeof(t_block)) * 100 + sizeof(t_block) = 15224
# define SMALL 106496 // 4096 * 26 > (SMALLMAX + sizeof(t_block)) * 100 + sizeof(t_block) = 104824

# define TINYMAX 128
# define SMALLMAX 1024

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
	size_t		size; // content size
	t_block		*next;
	t_page		*page;
};

struct					s_page
{
	size_t		fsize; // full size (also correspond to type)
	t_block		*blocklist;
	t_page		*next;
};

t_page					*g_pagelist;

// utils functions
int						get_typesize(size_t size);
void					ft_bzero(void *s, size_t n);
void					*ft_memset(void *s, int c, size_t n);
size_t					ft_strlen(const char *s);
void					ft_putstr(char const *s);
char					*ft_itoa(int n);
t_block					*add_block(t_block *prev, t_page *page, void *addr, size_t size);
t_page					*add_page(size_t size);

// library functions
void					show_alloc_mem(void);
void					show_pages_content(void);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
// calloc
// reallocf
// valloc
void					free(void *ptr);

#endif
