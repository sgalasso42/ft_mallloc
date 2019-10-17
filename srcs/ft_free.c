#include "ft_malloc.h"

void		delete_page(void *ptr)
{
	t_page	*page;

	page = get_first_page();
	while (page)
	{
		if (page == ptr)
			break ;
		page = page->next;
	}

	munmap(page, page->size); // 0 ok,  -1 pas ok, a securiser, voir man
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
		delete_page(ptr);
	}
}
