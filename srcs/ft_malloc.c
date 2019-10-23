/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:04:26 by sgalasso          #+#    #+#             */
/*   Updated: 2019/10/23 18:30:05 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block		*add_block(t_page *page, void *addr, size_t size/*, int typesize*/)
{
	t_block		*curr_block; // current block
	t_block		*new_block;

	new_block = addr;
	new_block->size = size;
	new_block->fsize = size + sizeof(t_block);

	if ((curr_block = page->blocklist))
	{
		while (curr_block->next)
		{
			if (curr_block < new_block)
			{
				if ((curr_block->next && (void *)new_block < (void *)curr_block->next)
				|| (!curr_block->next && (void *)new_block < (void *)page->next))
					break ;
			}
			curr_block = curr_block->next;
		}
		new_block->next = curr_block->next;
		curr_block->next = new_block;
	}
	else
	{
		page->blocklist = new_block;
		new_block->next = 0;
	}
	return (new_block);
}

t_block		*size_check(t_page *page, size_t fsize, size_t size)
{
	t_block		*block = 0;
	t_block		*curr_block = 0;

	curr_block = page->blocklist;
	if (!curr_block)
	{
		block = add_block(page, page + sizeof(t_page), size);
		return (block);
	}
	while (curr_block)
	{
		if ((!curr_block->next && (size_t)(page + page->fsize) - (size_t)curr_block >= fsize)
		|| (curr_block->next && (size_t)curr_block->next - (size_t)(curr_block + curr_block->fsize) >= fsize))
		{
			block = add_block(page, curr_block + curr_block->fsize, size);
			return (block);
		}
		curr_block = curr_block->next;
	}
	return (block);
}

t_block		*space_available(size_t size, int typesize)
{
	t_page		*page;
	t_block		*block;
	size_t		fsize;

	fsize = size + sizeof(t_block);
	page = g_pagelist;
	while (page)
	{
		if ((typesize == TINY && page->fsize == TINY)
			|| (typesize == SMALL && page->fsize == SMALL))
		{
			if ((block = size_check(page, fsize, size)))
				return (block);
		}
		page = page->next;
	}
	return (0);
}

t_page		*new_page(size_t size, int typesize)
{
	t_page	*last_page;
	t_page	*new_page;
	int		length;

	if (typesize != SMALL && typesize != TINY)
		length = size + sizeof(t_page);
	else
		length = typesize;

	printf("mmap length : %d\n", length);

	if ((new_page = mmap(0, length, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
	{
		perror("mmap error "); // to remove or check if ok to use
		exit(EXIT_FAILURE); // temporaire, trouver autre solution
	}

	new_page->size = size;
	if (typesize == SMALL || typesize == TINY)
		new_page->fsize = typesize;
	else
		new_page->fsize = size + sizeof(t_page);
	new_page->blocklist = 0;
	new_page->next = 0;

	if (!g_pagelist)
	{
		g_pagelist = new_page;
	}
	else
	{
		last_page = g_pagelist;
		while (last_page->next)
			last_page = last_page->next;
		last_page->next = new_page;
	}
	return (new_page);
}

t_block		*space_allocation(size_t size, int typesize)
{
	t_page		*page;
	t_block		*block;

	page = new_page(size, typesize);
	block = add_block(page, page + sizeof(page), size/*, type*/);
	return (block);
}

void		*ft_malloc(size_t size)
{
	t_block		*block;
	int			typesize;

	typesize = get_typesize(size);
	if (!(block = space_available(size, typesize)))
	{
		block = space_allocation(size, typesize);
	}
	return ((void *)block);
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_block		*block;
	int			typesize;

	(void)ptr;

	typesize = get_typesize(size);
	if (!(0/* adding_possible(ptr, size) */))
	{
		block = space_allocation(size, typesize);
	}
	return ((void *)block);
}
