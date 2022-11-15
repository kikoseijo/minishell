/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:16:13 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/05/10 08:51:30 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a copy of
** ’s1’ with the characters specified in ’set’ removed
** from the beginning and the end of the string.
*/

#include "../../inc/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*char_set;

	char_set = (char *)set;
	if (!s1 || !char_set)
		return (0);
	while (*s1 && ft_strchr(char_set, *s1))
		s1++;
	i = ft_strlen(s1);
	while (i && ft_strchr(char_set, s1[i]))
		i--;
	return (ft_substr(s1, 0, i + 1));
}
