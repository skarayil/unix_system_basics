/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarayil <skarayil@student.42kocaeli>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 12:41:48 by skarayil          #+#    #+#             */
/*   Updated: 2026/06/07 14:41:45 by skarayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_POPEN_H
# define FT_POPEN_H

# include <stdlib.h>
# include <unistd.h>

int	ft_popen(const char *f, char *const av[], char t);

#endif