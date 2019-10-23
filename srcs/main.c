/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:04:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/10/23 15:13:53 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		main(void)
{
	char	*str;
	char	*str1;

	if (!(str = ft_malloc(sizeof(char) * 5)))
	{
		printf("Malloc returned null 0");
		return (0);
	}
	str = strcpy(str, "12345");

	if (!(str1 = ft_malloc(sizeof(char) * 5)))
	{
		printf("Malloc returned null 1");
		return (0);
	}
	str1 = strcpy(str1, "abcde");

	show_pages_content();

	ft_free(str);

	show_pages_content();

	ft_free(str1);

	show_pages_content();

	return (0);
}
