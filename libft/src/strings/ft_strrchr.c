/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:12:12 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:35 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** string.h
**
** DESCRIPTION
** The strchr() function locates the first occurrence of
** c (converted to a char) in the string pointed to by s.
** The terminating null character is considered to be part of the string;
** therefore if c is `\0', the functions locate the terminating `\0'.
** The strrchr() function is identical to strchr(),
** except it locates the last occurrence of c.
**
** RETURN VALUES
** The functions strchr() and strrchr() return a pointer
** to the located character, or NULL if the character
** does not appear in the string.
*/

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (0);
}
