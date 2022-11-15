/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:11:47 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:45:51 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** string.h
**
** DESCRIPTION
** The memcpy() function copies n bytes from memory area src to memory area dst.
** If dst and src overlap, behavior is undefined.  Applications in which dst and
** src might overlap should use memmove(3) instead.
**
** RETURN VALUES
** The memcpy() function returns the original value of dst.
*/

#include "../../inc/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}
