#include "ft_malloc.h"

t_page		*get_first_page(void)
{
	static t_page	*first_page = 0;

	return (first_page);
}

t_page		*space_available(size_t size)
{
	t_page	*page = 0;

	(void)size;

	page = get_first_page();
	if (0/*TINY*/)
	{
	}
	else if (0/*SMALL*/)
	{
	}
	else
	{
		while (page)
		{
			if (page->available)
				return (page);
			page = page->next;
		}
	}
	return (0);
}

t_page		*new_page(size_t size)
{
	t_page	*last_page;
	t_page	*new_page;
	size_t	length;

	length = size + sizeof(t_page);

	last_page = get_first_page();
	while (last_page)
		last_page = last_page->next;

	if ((new_page = mmap(0, length, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
	{
		printf("mmap error\n");
		exit(EXIT_FAILURE); // temporaire, trouver autre solution
	}

	new_page->size = size;
	new_page->available = 0;
	new_page->next = 0;
	if (last_page)
	{
		last_page->next = new_page;
	}
	else
	{
		last_page = new_page;
	}

	return (new_page);
}

void		*ft_malloc(size_t size)
{
	t_page	*page;

	if (!(page = space_available(size)))
	{
		page = new_page(size);
	}
	return (page);
}
