/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 17:58:22 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/06/07 10:50:11 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static void	ft_print_uint_recursive(t_print *model, unsigned int nb)
{
	unsigned int	n;

	n = nb;
	if (n < 0)
		n *= -1;
	if (n > 9)
		ft_print_uint_recursive(model, n / 10);
	n = n % 10;
	model->str_len += 1;
	ft_putchar_fd(n + '0', 1);
}

void	ft_print_uint(t_print *model, unsigned int nb)
{
	ft_print_uint_recursive(model, nb);
	model->str++;
}
