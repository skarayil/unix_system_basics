/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:41:52 by skarayil          #+#    #+#             */
/*   Updated: 2026/06/07 14:40:28 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_popen.h"

int	ft_popen(const char *f, char *const av[], char t)
{
	int fd[2];
	pid_t p;

	if (!f || !av || (t != 'r' && t != 'w'))
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	p = fork();
	if (p == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (p == 0)
	{
		if (t == 'r')
			dup2(fd[1], STDOUT_FILENO);
		else
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execvp(f, av);
		exit(1);
	}
	if (t == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		close(fd[0]);
		return (fd[1]);
	}
}