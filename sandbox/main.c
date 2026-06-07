/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:48:44 by skarayil          #+#    #+#             */
/*   Updated: 2026/06/07 14:51:24 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sandbox.h"

void	good_func(void)
{
	usleep(100000);
}

void	segfault_func(void)
{
	int	*ptr;

	ptr = NULL;
	*ptr = 42;
}

void	timeout_func(void)
{
	while (1)
		;
}

int	main(void)
{
	int res;

	printf("=== 1. TEST: Nice Function ===\n");
	res = sandbox(good_func, 2, true);
	printf("Result: %d (Beklenen: 1)\n\n", res);

	printf("=== 2. TEST: Bad Function (Segfault) ===\n");
	res = sandbox(segfault_func, 2, true);
	printf("Result: %d (Beklenen: 0)\n\n", res);

	printf("=== 3. TEST: Bad Function (Timeout) ===\n");
	res = sandbox(timeout_func, 2, true);
	printf("Result: %d (Beklenen: 0)\n\n", res);

	return (0);
}