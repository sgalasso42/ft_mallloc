/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:25:36 by sgalasso          #+#    #+#             */
/*   Updated: 2019/10/23 15:32:21 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		get_typesize(size_t size)
{
	if (size <= TINYMAX)
	{
		return (TINY);
	}
	else if (size > TINYMAX && size <= SMALLMAX)
	{
		return (SMALL);
	}
	return (0);
}
