/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_pages_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:17:09 by sgalasso          #+#    #+#             */
/*   Updated: 2019/10/23 16:56:24 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	show_pages_content(void)
{
	t_page		*page;
	t_block		*block;
	int			nb_tiny;
	int			nb_small;
	int			nb_large;

	nb_tiny = 0;
	nb_small = 0;
	nb_large = 0;
	printf("\n#####################################\n\n");
	page = g_pagelist;
	if (page)
	{
		while (page)
		{
			printf("----------------\npage %p | fsize = %zu\n", page, page->fsize);
			block = page->blocklist;
			if (block)
			{
				while (block)
				{
					printf("    block %p | size = %zu\n", block, block->size);
					block = block->next;
				}
			}
			if (page->fsize == TINY)
				nb_tiny++;
			else if (page->fsize == SMALL)
				nb_small++;
			else
				nb_large++;
			page = page->next;
		}
	}
	printf("\n- - - - - - - - - - - - - - - - - - -\n\n");
	printf("nb pages: %d\n", nb_tiny + nb_small + nb_large);
	printf("TINY : %d\n", nb_tiny);
	printf("SMALL: %d\n", nb_small);
	printf("LARGE: %d\n", nb_large);
	printf("\n#####################################\n");
}
