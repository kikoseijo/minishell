/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:11:53 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:45:55 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** string.h
**
** DESCRIPTION
** The	memset(void) function writes len bytes
** of value c(converted to an unsigned char) to the string b.
**
** RETURN VALUES
** The memset() function returns its first argument.
*/

#include "../../inc/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len-- > 0)
		*ptr++ = (unsigned char)c;
	return (b);
}
