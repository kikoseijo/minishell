/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:13:31 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:46:22 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** string.h
**
** DESCRIPTION
** The strdup() function allocates sufficient memory for a copy
** of the string s1, does the copy, and returns a pointer to it.
** The pointer may subsequently be used as an argument to the function free(3).
**
** Allowed functions mallow(3)
*/

#include "../../inc/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;

	res = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, ft_strlen(s1) + 1);
	return (res);
}
