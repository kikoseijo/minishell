/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:12:09 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:34 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** string.h
**
** The strnstr() function locates the first occurrence of the
** null-terminated string needle in the string haystack,
** where not more than len characters are searched.
** Characters that appear after a `\0' character are not searched.
** Since the strnstr() function is a FreeBSD specific API,
** it should only be used when portability is not a concern.
*/

#include "../../inc/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && i + j < len)
	{
		if (haystack[i + j] == needle[j])
		{
			if (!needle[++j])
				return ((char *)(&haystack[i]));
		}
		else
		{
			j = 0;
			i++;
		}
	}
	return (NULL);
}
