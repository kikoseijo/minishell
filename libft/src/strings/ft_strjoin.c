/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:15:24 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:26 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a new
** string, which is the result of the concatenation
** of ’s1’ and ’s2’.
*/

#include "../../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	i = 0;
	len = (int)ft_strlen(s1) + (int)ft_strlen(s2) + 1;
	res = ft_calloc(len, sizeof(char));
	if (!res)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		res[i] = (char)s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
	{
		res[i + j] = (char)s2[j];
		j++;
	}
	return (res);
}
