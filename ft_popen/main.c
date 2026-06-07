/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:42:08 by skarayil          #+#    #+#             */
/*   Updated: 2026/06/07 14:42:12 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_popen.h"
#include <stdio.h>
#include <sys/wait.h>

void	test_read_mode(void)
{
	char	*cmd;
	char	*argv[] = {"ls", "-la", NULL};
	int		fd;
	char	buffer[1024];
	ssize_t	bytes_read;

	cmd = "ls";
	printf("--- Test 1: Okuma Modu ('r') [ls -la] ---\n");
	fd = ft_popen(cmd, argv, 'r');
	if (fd == -1)
	{
		printf("ft_popen basarisiz oldu.\n");
		return ;
	}
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		printf("%s", buffer);
		bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	}
	close(fd);
	wait(NULL);
}

void	test_write_mode(void)
{
	char	*cmd;
	char	*argv[] = {"wc", "-w", NULL};
	int		fd;
	char	*str;

	cmd = "wc";
	str = "42 Istanbul Exam Rank 04\n";
	printf("\n--- Test 2: Yazma Modu ('w') [wc -w] ---\n");
	fd = ft_popen(cmd, argv, 'w');
	if (fd == -1)
	{
		printf("ft_popen basarisiz oldu.\n");
		return ;
	}
	if (write(fd, str, 25) == -1)
		printf("Yazma hatasi\n");
	close(fd);
	wait(NULL);
}

int	main(void)
{
	test_read_mode();
	test_write_mode();
	return (0);
}