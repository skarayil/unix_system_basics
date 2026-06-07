/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:45:26 by skarayil          #+#    #+#             */
/*   Updated: 2026/06/07 14:45:53 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "picoshell.h"
#include <stdio.h>

int	main(void)
{
	char *cmd1[] = {"ls", "-la", NULL};
	char *cmd2[] = {"grep", "main", NULL};
	char *cmd3[] = {"wc", "-l", NULL};
	char **cmds[] = {cmd1, cmd2, cmd3, NULL};
	int result;

	printf("--- Picoshell Pipeline Testi Baslatiliyor ---\n");
	printf("Calistirilacak Komut: ls -la | grep main | wc -l\n\n");
	printf("Cikti:\n");

	result = picoshell(cmds);

	printf("\nPicoshell geri donus degeri: %d (Beklenen: 0)\n", result);
	return (0);
}
