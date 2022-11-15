/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:18:04 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:42:47 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates (with malloc(3)) and returns a string
** representing the integer received as an argument.
** Negative numbers must be handled.
*/

#include "../../inc/libft.h"

static int	ft_nbrlen(long long int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	nb;
	int		len;
	int		sign;

	sign = 1;
	len = ft_nbrlen(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	res[len] = '\0';
	if (!res)
		return (0);
	if (n < 0)
		sign = -1;
	nb = ((long)n) * sign;
	while (len--)
	{
		res[len] = nb % 10 + '0';
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
