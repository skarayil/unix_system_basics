/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:43:31 by skarayil          #+#    #+#             */
/*   Updated: 2026/06/07 14:48:32 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "picoshell.h"

int	picoshell(char **cmds[])
{
	int p[2];
	int in;
	int i;
	pid_t pid;

	in = -1;
	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(p) == -1)
			return (1);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			if (in != -1)
			{
				if (dup2(in, STDIN_FILENO) == -1)
					exit(1);
				close(in);
			}
			if (cmds[i + 1])
			{
				close(p[0]);
				if (dup2(p[1], STDOUT_FILENO) == -1)
					exit(1);
				close(p[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if (in != -1)
			close(in);
		if (cmds[i + 1])
		{
			close(p[1]);
			in = p[0];
		}
		i++;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
