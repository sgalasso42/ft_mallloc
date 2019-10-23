/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:17:24 by sgalasso          #+#    #+#             */
/*   Updated: 2019/10/23 17:08:36 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define TINY 1000		// N : should be TINYMAX * 100
# define SMALL 10000	// M : should be SMALLMAX * 100

# define TINYMAX 10		// n
# define SMALLMAX 100	// m

# include "libft.h"
# include <sys/mman.h>
# include <unistd.h>

# include <stdio.h>		// to remove

typedef struct	s_block			t_block;
typedef struct	s_page			t_page;

struct					s_block
{
	size_t		fsize;	// full size
	size_t		size;	// content size
	t_block		*next;
	t_page		*page;	// page linked
};

struct					s_page
{
	size_t		fsize;	// full size // also correspond to type
	size_t		size;	// content size
	t_block		*blocklist;
	t_page		*next;
};

t_page					*g_pagelist;

// UTILS FUNCTIONS
int					get_typesize(size_t size);

// LIB FUNCTIONS
void					show_alloc_mem();
void					*ft_malloc(size_t size);
void					*ft_realloc(void *ptr, size_t size);
void					ft_free(void *ptr);

// BONUS
void					show_pages_content(void);

#endif
