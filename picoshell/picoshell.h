/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:45:15 by skarayil          #+#    #+#             */
/*   Updated: 2026/06/07 14:45:17 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PICOSHELL_H
# define PICOSHELL_H

# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

int	picoshell(char **cmds[]);

#endif