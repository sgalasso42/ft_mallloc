/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 15:04:31 by sgalasso          #+#    #+#             */
/*   Updated: 2019/10/23 18:25:57 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		main(void)
{
	char	*str;
	char	*str0;
	char	*str1;
	char	*str2;
	(void)str;
	(void)str0;
	(void)str1;
	(void)str2;

	if (!(str = ft_malloc(sizeof(char) * 3)))
	{
		printf("Malloc returned null 0");
		return (0);
	}
	printf("malloc %p\n", str);

	if (!(str0 = ft_malloc(sizeof(char) * 5)))
	{
		printf("Malloc returned null 0");
		return (0);
	}
	printf("malloc %p\n", str0);

	if (!(str1 = ft_malloc(sizeof(char) * 25)))
	{
		printf("Malloc returned null 1");
		return (0);
	}
	printf("malloc %p\n", str1);

	if (!(str2 = ft_malloc(sizeof(char) * 160)))
	{
		printf("Malloc returned null 2");
		return (0);
	}
	printf("malloc %p\n", str2);

	show_pages_content();

	printf("free %p\n", str);
	ft_free(str);

	show_pages_content();

	printf("free %p\n", str0);
	ft_free(str0);

	show_pages_content();

	printf("free %p\n", str1);
	ft_free(str1);

	show_pages_content();

	printf("free %p\n", str2);
	ft_free(str2);

	show_pages_content();

	return (0);
}
