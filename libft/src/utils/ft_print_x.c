/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:09:28 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/07 10:50:43 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static void	ft_print_x_recursive(t_print *m, unsigned int nb, char *base)
{
	unsigned int	base_len;

	base_len = ft_strlen(base);
	if (base_len > 1)
	{
		if (nb >= base_len)
			ft_print_x_recursive(m, nb / base_len, base);
		m->str_len++;
		ft_putchar_fd(base[nb % base_len], 1);
	}
}

void	ft_print_x(t_print *m, unsigned int nb)
{
	if (*m->str == 'X')
		ft_print_x_recursive(m, nb, "0123456789ABCDEF");
	else
		ft_print_x_recursive(m, nb, "0123456789abcdef");
	m->str++;
}
