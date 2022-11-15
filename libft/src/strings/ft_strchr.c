/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:11:56 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:20 by jseijo-p         ###   ########.fr       */
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

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
