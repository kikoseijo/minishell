/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:11:59 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:27 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** string.h
**
** The strlcpy() and strlcat() functions copy and concatenate strings
** with the same input parameters and output result as snprintf(3).
** They are designed to be safer, more consistent, and less error prone
** replacements for the easily misused functions strncpy(3) and strncat(3).
**
** strlcpy() and strlcat() take the full size of the
** destination buffer and guarantee NUL-termination if there is room.
** Note that room for the NUL should be included in dstsize.
**
** strlcpy() copies up to dstsize - 1 characters from the string src to dst,
** NUL-terminating the result if dstsize is not 0.
**
** strlcat() appends string src to the end of dst.
** It will append at most dstsize - strlen(dst) - 1 characters.
** It will then NUL-terminate, unless dstsize is 0 or
** the original dst string was longer than dstsize
** (in practice this should not happen as it means that either
** dstsize is incorrect or that dst is not a proper string).
**
** If the src and dst strings overlap, the behavior is undefined.
*/

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_count;
	size_t	i;

	dest_count = ft_strlen(dst);
	i = 0;
	if (dstsize > dest_count)
	{
		while (i < (dstsize - dest_count) - 1 && src[i] != '\0')
		{
			dst[dest_count + i] = src[i];
			i++;
		}
		if (i <= dstsize - dest_count)
			dst[dest_count + i] = '\0';
		return (dest_count + ft_strlen(src));
	}
	return (dstsize + ft_strlen(src));
}
