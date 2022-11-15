/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:11:44 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:45:45 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** string.h
**
** The memcmp() function compares byte string s1 against byte string s2.
** Both strings are assumed to be n bytes long.
**
** RETURN VALUES
** The memcmp() function returns zero if the two strings are identical,
** otherwise returns the difference between the first two differing bytes
** (treated as unsigned char values, so that `\200' is greater
** than `\0', for example).  Zero-length strings are always identical.
** This behavior is not required by C and portable code should only
** depend on the sign of the returned value.
*/

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
