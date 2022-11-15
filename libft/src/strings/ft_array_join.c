/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmac <cmac@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:51:37 by cmac              #+#    #+#             */
/*   Updated: 2022/11/01 18:25:05 by cmac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	**ft_array_join(char **array, char **array_b)
{
	int		size;
	char	**res;
	int		i;
	int		j;

	size = ft_array_len(array) + ft_array_len(array_b) + 1;
	res = (char **)ft_calloc(size, sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (array && array[i])
	{
		res[i] = ft_strdup(array[i]);
		i++;
	}
	j = 0;
	while (array_b && array_b[j])
	{
		res[i] = ft_strdup(array_b[j]);
		i++;
		j++;
	}
	return (res);
}
