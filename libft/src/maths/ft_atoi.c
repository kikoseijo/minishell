/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:11:32 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/15 11:44:50 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** stdlib.h
** The atoi() function converts the initial
** portion of the string pointed
** to by str to int representation.
*/

static int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	is_neg;

	i = 0;
	is_neg = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		is_neg = -1;
	if (is_neg == -1 || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	res *= is_neg;
	if (is_neg == 1 && res < 0)
		return (-1);
	if (is_neg == -1 && res > 0)
		return (0);
	return (res);
}
