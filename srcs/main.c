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

#include <time.h>
#include "ft_malloc.h"

int	main(void)
{
	void	*test[1000];
	ft_bzero(test, 1000 * sizeof(void*));
	srand(time(NULL));
	int i;

	// MY MALLOC
	clock_t lastTime0 = clock();
	for (i = 0; i < 10; i++)
	{
		void *ptr = ft_malloc((rand() % 15000));
		test[i] = ptr;
	}
	clock_t diff0 = clock() - lastTime0;

	// SYSTEM MALLOC
	clock_t lastTime2 = clock();
	for (i = 0; i < 10; i++)
	{
		void *ptr = malloc((rand() % 15000));
		test[i] = ptr;
	}
	clock_t diff2 = clock() - lastTime2;

	// MY FREE
	clock_t lastTime1 = clock();
	for (i = 0; i < 10; i++)
		ft_free(test[i]);
	clock_t diff1 = clock() - lastTime1;

	// SYSTEM FREE
	clock_t lastTime3 = clock();
	for (i = 0; i < 10; i++)
		free(test[i]);
	clock_t diff3 = clock() - lastTime3;

	// LOGS
	show_pages_content();
	printf("\nmalloc perso: %lu ticks\n", diff0);
	printf("malloc system: %lu ticks\n", diff2);
	printf("free perso: %lu ticks\n", diff1);
	printf("free system: %lu ticks\n", diff3);
	printf("\nratio malloc: %lu\n", diff0 / diff2);
	printf("ratio free:   %lu\n", diff1 / diff3);
	return (0);
}
