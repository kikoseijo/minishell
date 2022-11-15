/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:21:52 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:02 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Outputs the string ’s’ to the given file descriptor
** followed by a newline.
** CHECK: when no string we write a new line allways.
*/

#include "../../inc/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
		ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
