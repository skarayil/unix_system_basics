/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 14:48:47 by skarayil          #+#    #+#             */
/*   Updated: 2026/06/07 14:51:15 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SANDBOX_H
# define SANDBOX_H

# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

int	sandbox(void (*f)(void), unsigned int timeout, bool verbose);

#endif