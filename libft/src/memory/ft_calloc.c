/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:12:50 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/05/10 08:40:32 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stdlib.h
**
** The calloc() function contiguously allocates enough space
** for count objects that are size bytes of memory each and
** returns a pointer to the allocated memory.
** The allocated memory is filled with bytes of value zero.
**
** Allowed functions malloc(3)
*/

#include "../../inc/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (size && (size_t)-1 / size < count)
		return (NULL);
	res = (void *)malloc(size * count);
	if (!res)
		return (NULL);
	ft_bzero(res, size * count);
	return (res);
}

/*
** previous solution for overflow
** total_size = count + size;
** if (total_size < count || total_size < size)
** 	return (NULL);
*/

/*
** int	main(void)
** {
** 	printf("%s\n", ft_calloc(2, sizeof(char)));
** 	printf("%s\n", ft_calloc(__INT_MAX__, __INT_MAX__));
** 	return (0);
** }
*/
