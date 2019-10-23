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

void		show_pages_content(void)
{
	t_page		*page;
	t_block		*block;

	printf("\n#####################################\n\n");
	if ((page = g_pagelist))
	{
		while (page)
		{
			printf("------------------\npage %p | size = %zu\n", page, page->fsize);
			if ((block = page->blocklist))
			{
				while (block)
				{
					printf("    block %p | size = %zu\n", block, block->size);
					block = block->next;
				}
			}
			page = page->next;
		}
	}
	printf("\n");
}
