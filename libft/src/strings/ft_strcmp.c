/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:35:02 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/11/14 11:35:19 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				diff;
	int				i;
	int				j;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	diff = *str1 - *str2;
	i = 0;
	j = 0;
	while (diff == 0)
	{
		diff += str1[i] - str2[j];
		if (diff != 0 || (str1[i] == '\0' && str2[j] == '\0'))
			return (diff);
		if (str1[i] != '\0')
			i++;
		if (str2[j] != '\0')
			j++;
	}
	return (diff);
}
