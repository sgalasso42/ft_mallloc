#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <unistd.h>

# include <stdio.h>

typedef struct	s_page	t_page;

struct					s_page
{
	size_t	size;
	int		available;
	t_page	*next;
};

t_page					*get_first_page(void);

//void					show_alloc_mem();
void					*ft_malloc(size_t size);
//void					*ft_realloc(void *ptr, size_t size);
void					ft_free(void *ptr);

#endif
